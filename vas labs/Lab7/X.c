// gcc X.c -o X -lX11 -lm

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

// Палитра цветов
static unsigned long colors[7];
static const char* color_names[] = {
    "white", "blue", "hot pink", "violet", "orange", "yellow", "green"
};

Display *dis;
int screen;
Window win;
GC gc;
Colormap colormap;

// Структура для хранения информации о цветке
typedef struct {
    int x, y;       // Центр цветка
    int diameter;   // Диаметр цветка
    int petals;     // Количество лепестков
    int color_idx;  // Индекс цвета лепестков
} Flower;

#define MAX_FLOWERS 100
Flower flowers[MAX_FLOWERS];
int flower_count = 0;

// Функция заполнения палитры 
void get_colors() {
    XColor tmp;
    for (int i = 0; i < 7; i++) {
        XParseColor(dis, colormap, color_names[i], &tmp);
        XAllocColor(dis, colormap, &tmp);
        colors[i] = tmp.pixel;
    }
}

// Функция проверки пересечения двух цветков
bool flowers_intersect(Flower f1, Flower f2) {
    int dx = f1.x - f2.x;
    int dy = f1.y - f2.y;
    int distance = sqrt(dx*dx + dy*dy);
    int min_distance = (f1.diameter + f2.diameter) / 2;
    return distance < min_distance;
}

// Функция проверки, можно ли разместить новый цветок
bool can_place_flower(Flower new_flower) {
    for (int i = 0; i < flower_count; i++) {
        if (flowers_intersect(new_flower, flowers[i])) {
            return false;
        }
    }
    return true;
}

// Алгоритм построчной закраски (заливка)
void flood_fill(int x, int y, unsigned long fill_color) {
    unsigned long current_color;
    XImage *image = XGetImage(dis, win, 0, 0, 800, 800, AllPlanes, ZPixmap);
    
    // Получаем цвет начальной точки
    current_color = XGetPixel(image, x, y);
    
    // Если цвет уже совпадает с fill_color, выходим
    if (current_color == fill_color) {
        XDestroyImage(image);
        return;
    }
    
    // Стек для хранения точек
    int stack[800*800][2];
    int stack_size = 0;
    
    // Добавляем начальную точку в стек
    stack[stack_size][0] = x;
    stack[stack_size][1] = y;
    stack_size++;
    
    while (stack_size > 0) {
        // Извлекаем точку из стека
        stack_size--;
        int cx = stack[stack_size][0];
        int cy = stack[stack_size][1];
        
        // Если цвет точки не совпадает с исходным, пропускаем
        if (XGetPixel(image, cx, cy) != current_color) {
            continue;
        }
        
        // Находим левую границу
        int left = cx;
        while (left >= 0 && XGetPixel(image, left, cy) == current_color) {
            left--;
        }
        left++;
        
        // Находим правую границу
        int right = cx;
        while (right < 800 && XGetPixel(image, right, cy) == current_color) {
            right++;
        }
        right--;
        
        // Закрашиваем линию
        for (int i = left; i <= right; i++) {
            XDrawPoint(dis, win, gc, i, cy);
        }
        
        // Проверяем строку выше
        if (cy > 0) {
            bool in_span = false;
            for (int i = left; i <= right; i++) {
                if (XGetPixel(image, i, cy-1) == current_color) {
                    if (!in_span) {
                        stack[stack_size][0] = i;
                        stack[stack_size][1] = cy-1;
                        stack_size++;
                        in_span = true;
                    }
                } else {
                    in_span = false;
                }
            }
        }
        
        // Проверяем строку ниже
        if (cy < 799) {
            bool in_span = false;
            for (int i = left; i <= right; i++) {
                if (XGetPixel(image, i, cy+1) == current_color) {
                    if (!in_span) {
                        stack[stack_size][0] = i;
                        stack[stack_size][1] = cy+1;
                        stack_size++;
                        in_span = true;
                    }
                } else {
                    in_span = false;
                }
            }
        }
    }
    
    XDestroyImage(image);
}

// Функция рисования круга (аналог rasterCircle из circle.c)
void draw_circle(int x0, int y0, int radius) {
    int f = 1 - radius;
    int ddF_x = 1;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;
 
    XDrawPoint(dis, win, gc, x0, y0 + radius);
    XDrawPoint(dis, win, gc, x0, y0 - radius);
    XDrawPoint(dis, win, gc, x0 + radius, y0);
    XDrawPoint(dis, win, gc, x0 - radius, y0);
 
    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        
        XDrawPoint(dis, win, gc, x0 + x, y0 + y);
        XDrawPoint(dis, win, gc, x0 - x, y0 + y);
        XDrawPoint(dis, win, gc, x0 + x, y0 - y);
        XDrawPoint(dis, win, gc, x0 - x, y0 - y);
        XDrawPoint(dis, win, gc, x0 + y, y0 + x);
        XDrawPoint(dis, win, gc, x0 - y, y0 + x);
        XDrawPoint(dis, win, gc, x0 + y, y0 - x);
        XDrawPoint(dis, win, gc, x0 - y, y0 - x);
    }
}

// Функция рисования цветка
void draw_flower(Flower flower) {
    int radius = flower.diameter / 2;
    int center_radius = radius / 4; // 0.25 от диаметра
    
    // Рисуем лепестки
    XSetForeground(dis, gc, colors[flower.color_idx]);
    for (int i = 0; i < flower.petals; i++) {
        double angle = 2 * M_PI * i / flower.petals;
        int petal_x = flower.x + radius * cos(angle);
        int petal_y = flower.y + radius * sin(angle);
        draw_circle(petal_x, petal_y, radius / 3);
    }
    
    // Рисуем центр цветка (желтый)
    XSetForeground(dis, gc, colors[5]); // yellow
    draw_circle(flower.x, flower.y, center_radius);
    flood_fill(flower.x, flower.y, colors[5]);
}

// Функция добавления нового цветка
void add_random_flower() {
    Flower new_flower;
    int attempts = 0;
    
    do {
        // Генерируем случайные параметры
        new_flower.diameter = 20 + rand() % 41; // 20-60
        new_flower.petals = 4 + rand() % 12;   // 4-15
        new_flower.x = new_flower.diameter + rand() % (800 - 2 * new_flower.diameter);
        new_flower.y = new_flower.diameter + rand() % (800 - 2 * new_flower.diameter);
        
        // Выбираем случайный цвет (кроме зеленого и черного)
        do {
            new_flower.color_idx = rand() % 5; // 0-4 (white, blue, pink, violet, orange)
        } while (new_flower.color_idx == 6); // skip green
        
        attempts++;
        
        // Если долго не можем найти место, удаляем первые два цветка
        if (attempts > 100 && flower_count > 2) {
            for (int i = 0; i < flower_count - 2; i++) {
                flowers[i] = flowers[i + 2];
            }
            flower_count -= 2;
            attempts = 0;
        }
    } while (!can_place_flower(new_flower) && attempts < 200);
    
    if (attempts < 200) {
        flowers[flower_count++] = new_flower;
        draw_flower(new_flower);
    }
}

// Инициализация X Window
void init_x() {
    unsigned long black, white;
    
    srand(time(NULL));
    
    dis = XOpenDisplay(NULL);
    screen = DefaultScreen(dis);
    black = BlackPixel(dis, screen);
    white = WhitePixel(dis, screen);
    
    win = XCreateSimpleWindow(dis, DefaultRootWindow(dis), 0, 0, 
        800, 800, 5, black, white);
    
    XSetStandardProperties(dis, win, "Flowers", "Romashka", None, NULL, 0, NULL);
    XSelectInput(dis, win, ExposureMask | ButtonPressMask | KeyPressMask);
    
    gc = XCreateGC(dis, win, 0, 0);
    XSetBackground(dis, gc, black);
    XSetForeground(dis, gc, white);
    
    colormap = DefaultColormap(dis, screen);
    get_colors();
    
    // Заливаем окно зеленым цветом
    XSetForeground(dis, gc, colors[6]); // green
    XFillRectangle(dis, win, gc, 0, 0, 800, 800);
    
    XClearWindow(dis, win);
    XMapRaised(dis, win);
}

// Закрытие X Window
void close_x() {
    XFreeGC(dis, gc);
    XDestroyWindow(dis, win);
    XCloseDisplay(dis);
    exit(0);
}

// Перерисовка окна
void redraw() {
    XSetForeground(dis, gc, colors[6]); // green
    XFillRectangle(dis, win, gc, 0, 0, 800, 800);
    
    for (int i = 0; i < flower_count; i++) {
        draw_flower(flowers[i]);
    }
}

int main(int argc, char *argv[]) {
    XEvent event;
    KeySym key;
    char text[255];
    
    init_x();
    
    // Добавляем 10 случайных цветков при запуске
    for (int i = 0; i < 10; i++) {
        add_random_flower();
    }
    
    while (1) {
        XNextEvent(dis, &event);
        
        if (event.type == Expose && event.xexpose.count == 0) {
            redraw();
        }
        if (event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key, 0) == 1) {
            if (text[0] == 'q') {
                close_x();
            } else if (text[0] == 'a') {
                add_random_flower();
            }
        }
        if (event.type == ButtonPress) {
            if (event.xbutton.button == 1) {
                add_random_flower();
            }
        }
    }
    
    return 0;
}
