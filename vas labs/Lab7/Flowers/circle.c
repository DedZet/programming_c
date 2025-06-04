#include <X11/Xlib.h>

void rasterCircle(Display *dis, Window win, GC gc, int x0, int y0, int radius)
{
    if (!dis || !win) return;

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
