// gcc X.c circle.c -o X -lX11 -lm

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "circle.h"

#define MAX_FLOWERS 100

static unsigned long colors[7];
static const char* color_names[] = {
    "white", "blue", "hot pink", "violet", "orange", "yellow", "green"
};

Display *dis;
int screen;
Window win;
GC gc;
Colormap colormap;

typedef struct {
    int x, y;
    int diameter;
    int petals;
    int color_idx;
} Flower;


Flower flowers[MAX_FLOWERS];
int flower_count = 0;

void get_colors() {
    XColor tmp;
    for (int i = 0; i < 7; i++) {
        if (!XParseColor(dis, colormap, color_names[i], &tmp)) {
            fprintf(stderr, "Failed to parse color %s\n", color_names[i]);
            continue;
        }
        if (!XAllocColor(dis, colormap, &tmp)) {
            fprintf(stderr, "Failed to allocate color %s\n", color_names[i]);
            continue;
        }
        colors[i] = tmp.pixel;
    }
}

bool flowers_intersect(Flower f1, Flower f2) {
    int dx = f1.x - f2.x;
    int dy = f1.y - f2.y;
    int distance = sqrt(dx*dx + dy*dy);
    int min_distance = (f1.diameter + f2.diameter) / 2;
    return distance < min_distance;
}

bool can_place_flower(Flower new_flower) {
    for (int i = 0; i < flower_count; i++) {
        if (flowers_intersect(new_flower, flowers[i])) {
            return false;
        }
    }
    return true;
}

void draw_filled_circle(int x0, int y0, int radius) {
	
    if (radius <= 0) return;
    rasterCircle(dis, win, gc, x0, y0, radius);
    for (int r = radius-1; r > 0; r--) {
        rasterCircle(dis, win, gc, x0, y0, r);
    }
}

void draw_flower(Flower flower) {
    int radius = flower.diameter / 2;
    int center_radius = radius / 4;
    
    if (flower.color_idx < 0 || flower.color_idx >= 5) {
        flower.color_idx = 0;
    }
    
    XSetForeground(dis, gc, colors[flower.color_idx]);
    for (int i = 0; i < flower.petals; i++) {
        double angle = 2 * M_PI * i / flower.petals;
        int petal_x = flower.x + radius * cos(angle);
        int petal_y = flower.y + radius * sin(angle);
        draw_filled_circle(petal_x, petal_y, radius / 3);
    }
    
    XSetForeground(dis, gc, colors[5]); // yellow
    draw_filled_circle(flower.x, flower.y, center_radius);
}

void add_random_flower() {
    if (flower_count >= MAX_FLOWERS) {
        for (int i = 0; i < flower_count - 2; i++) {
            flowers[i] = flowers[i + 2];
        }
        flower_count -= 2;
    }

    Flower new_flower;
    int attempts = 0;
    const int max_attempts = 100;
    
    do {
        new_flower.diameter = 20 + rand() % 41; // 20-60
        new_flower.petals = 4 + rand() % 12;   // 4-15
        new_flower.x = new_flower.diameter + rand() % (800 - 2 * new_flower.diameter);
        new_flower.y = new_flower.diameter + rand() % (800 - 2 * new_flower.diameter);
        new_flower.color_idx = rand() % 5; // 0-4 (white, blue, pink, violet, orange)
        
        attempts++;
    } while (!can_place_flower(new_flower) && attempts < max_attempts);
    
    if (attempts < max_attempts) {
        flowers[flower_count++] = new_flower;
        draw_flower(new_flower);
        XFlush(dis);
    }
}

void init_x() {
    unsigned long black, white;
    
    srand(time(NULL));
    
    dis = XOpenDisplay(NULL);
    if (!dis) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }
    
    screen = DefaultScreen(dis);
    black = BlackPixel(dis, screen);
    white = WhitePixel(dis, screen);
    colormap = DefaultColormap(dis, screen);
    
    win = XCreateSimpleWindow(dis, DefaultRootWindow(dis), 0, 0, 
        800, 800, 5, black, white);
    
    XSetStandardProperties(dis, win, "Flowers", "Romashka", None, NULL, 0, NULL);
    XSelectInput(dis, win, ExposureMask | ButtonPressMask | KeyPressMask);
    
    gc = XCreateGC(dis, win, 0, 0);
    if (!gc) {
        fprintf(stderr, "Failed to create GC\n");
        exit(1);
    }
    
    XSetBackground(dis, gc, black);
    XSetForeground(dis, gc, white);
    
    get_colors();
    
    XSetForeground(dis, gc, colors[6]);
    XFillRectangle(dis, win, gc, 0, 0, 800, 800);
    
    XClearWindow(dis, win);
    XMapRaised(dis, win);
    XFlush(dis);
}

void close_x() {
    if (gc) XFreeGC(dis, gc);
    if (win) XDestroyWindow(dis, win);
    if (dis) XCloseDisplay(dis);
    exit(0);
}

void redraw() {
    XSetForeground(dis, gc, colors[6])
    XFillRectangle(dis, win, gc, 0, 0, 800, 800);
    
    for (int i = 0; i < flower_count; i++) {
        draw_flower(flowers[i]);
    }
    XFlush(dis);
}

int main() {
    XEvent event;
    fd_set in_fds;
    struct timeval tv;
    
    init_x();
    
    for (int i = 0; i < 5; i++) {
        add_random_flower();
    }
    
    while (1) {
        FD_ZERO(&in_fds);
        FD_SET(ConnectionNumber(dis), &in_fds);
        tv.tv_sec = 0;
        tv.tv_usec = 100000; // 100ms
        
        int num_ready = select(ConnectionNumber(dis)+1, &in_fds, NULL, NULL, &tv);
        
        if (num_ready > 0) {
            while (XPending(dis)) {
                XNextEvent(dis, &event);
                
                switch (event.type) {
                    case Expose:
                        if (event.xexpose.count == 0) {
                            redraw();
                        }
                        break;
                        
                    case KeyPress: {
                        char text[255];
                        KeySym key;
                        if (XLookupString(&event.xkey, text, 255, &key, 0) == 1) {
                            if (text[0] == 'q') {
                                close_x();
                            } else if (text[0] == 'a') {
                                add_random_flower();
                            }
                        }
                        break;
                    }
                        
                    case ButtonPress:
                        if (event.xbutton.button == 1) {
                            add_random_flower();
                        }
                        break;
                }
            }
        }
        
        static time_t last_add = 0;
        time_t now = time(NULL);
        if (now - last_add >= 1) {
            add_random_flower();
            last_add = now;
        }
    }
    
    return 0;
}
