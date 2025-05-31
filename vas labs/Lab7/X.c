/* 
	Remember to compile try:
		1) gcc X.c -o X -lX11
*/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <stdlib.h>
// Ïàëèòðà öâåòîâ
static unsigned long red,blue,green,yellow,orange,darkblue,violet, *pal=&red;
int indx=0; 
/* here are our X variables */
Display *dis;
int screen;
Window win;
GC gc;
Visual vis;

//   Ôóíêöèÿ çàïîëíåíèÿ ïàëèòðû 
void get_colors() {
	XColor tmp;

	XParseColor(dis, DefaultColormap(dis,screen), "indian red", &tmp);
	XAllocColor(dis,DefaultColormap(dis,screen),&tmp);
	red=tmp.pixel;
	XParseColor(dis, DefaultColormap(dis,screen), "orange", &tmp);
	XAllocColor(dis,DefaultColormap(dis,screen),&tmp);
	orange=tmp.pixel;
	XParseColor(dis, DefaultColormap(dis,screen), "dark green", &tmp);
	XAllocColor(dis,DefaultColormap(dis,screen),&tmp);
	green=tmp.pixel;
	XParseColor(dis, DefaultColormap(dis,screen), "green yellow", &tmp);
	XAllocColor(dis,DefaultColormap(dis,screen),&tmp);
	yellow=tmp.pixel;
	XParseColor(dis, DefaultColormap(dis,screen), "blue", &tmp);
	XAllocColor(dis,DefaultColormap(dis,screen),&tmp);
	blue=tmp.pixel;
	XParseColor(dis, DefaultColormap(dis,screen), "dark blue", &tmp);
	XAllocColor(dis,DefaultColormap(dis,screen),&tmp);
	darkblue=tmp.pixel;
	XParseColor(dis, DefaultColormap(dis,screen), "violet", &tmp);
	XAllocColor(dis,DefaultColormap(dis,screen),&tmp);
	violet=tmp.pixel;
}
			int x,
			    y;
                        static int xn=0, yn=0, x0, y0, first=1;
/* here are our X routines declared! */
void init_x();
void init2_x();
void close_x();
void redraw();
	Colormap cmap;
#include "circle.c"

int main () {
	XEvent event;		/* the XEvent declaration !!! */
	KeySym key;		/* a dealie-bob to handle KeyPress Events */	
	char text[255];		/* a char buffer for KeyPress Events */

	init_x();
	while(1) {		
		XNextEvent(dis, &event);
	
		if (event.type==Expose && event.xexpose.count==0) {
			redraw();
		}
		if (event.type==KeyPress&&
		    XLookupString(&event.xkey,text,255,&key,0)==1) {
			if (text[0]=='q') {
				close_x();
			}
			printf("You pressed the %c key!\n",text[0]);
		}
		if (event.type==ButtonPress) {
			    x=event.xbutton.x,
			    y=event.xbutton.y;

              if (event.xbutton.button==1) { 
              if (first) {
                  XSetForeground(dis,gc,pal[indx++]); indx%=7; 
                        XDrawPoint(dis,win,gc,x,y); first=0;
                         x0=xn=x; y0=yn=y;
                        } 
                else {  
                        XDrawLine(dis,win,gc, xn,yn, x,y); 
                        xn=x; yn=y;
                     }
		} else
              if (event.xbutton.button==3)  
                  {
                        XDrawLine(dis,win,gc, x0,y0, xn,yn); 
                        first=1;
                      rasterCircle(x0,y0,50);
                  }
            }
	}
}

void init_x() {
/* get the colors black and white (see section for details) */        
	unsigned long black,white;

	dis=XOpenDisplay((char *)0);
   	screen=DefaultScreen(dis);
	black=BlackPixel(dis,screen),
	white=WhitePixel(dis, screen);
   	win=XCreateSimpleWindow(dis,DefaultRootWindow(dis),0,0,	
		800, 800, 5,black, white);
	XSetStandardProperties(dis,win," F L O W E R S ! ! ","Romashka",None,NULL,0,NULL);
	XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);
        gc=XCreateGC(dis, win, 0,0);        
	XSetBackground(dis,gc,black);
	XSetForeground(dis,gc,white);
	XClearWindow(dis, win);
	XMapRaised(dis, win);
//** ok  - 7 colors
   get_colors();
init2_x();
}

void close_x() {
	XFreeGC(dis, gc);
	XDestroyWindow(dis,win);
	XCloseDisplay(dis);	
	exit(1);				
}

void redraw() {
	XClearWindow(dis, win);
}

XColor color;
  Colormap colormap;
  char Green[] = "#00FF00";

void init2_x() {   // Îêíî ñ çåëåíûì ôîíîì - ×ÖØÒ
  colormap = DefaultColormap(dis, 0);
  XParseColor(dis, colormap, Green, &color);
  XAllocColor(dis, colormap, &color);


  Window xwin = XCreateSimpleWindow(dis, 
                   DefaultRootWindow(dis), 
                   0, 0, 
                   500, 300, 
                   0,
                   WhitePixel(dis, 0),
                   color.pixel);

XMapWindow(dis, xwin);
XFlush(dis);
}
// gcc X.c -o program -lX11
