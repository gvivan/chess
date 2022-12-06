#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <sstream>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height) {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[10][10]={"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 10; ++i) {
      XParseColor(d,cmap,color_vals[i],&xcolour);
      XAllocColor(d,cmap,&xcolour);
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  //usleep(1000);

  // Make sure we don't race against the Window being shown
  XSelectInput(d, w, ExposureMask);
  XFlush(d);
  XEvent ev;
  XNextEvent(d, &ev);
  XSelectInput(d, w, 0);
  /*while(1) {
    XNextEvent(d, &ev);
    if(ev.type == Expose) break;
  }*/
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawStringFont(int x, int y, string msg, string font, int colour) {
  XFontStruct *f = XLoadQueryFont(d, font.c_str());
  if(f == nullptr) {
	  f = XLoadQueryFont(d, "6x13");
  }
  printMessage(x, y, msg, colour, *f);
  delete f;
}

void Xwindow::printMessage(int x, int y, const string& msg, int colour, XFontStruct& f){
  XSetForeground(d, gc, colours[colour]);
  XTextItem textitem;
  textitem.chars = const_cast<char*>(msg.c_str());
  textitem.nchars = msg.length();
  textitem.delta = 0;
  textitem.font = f.fid;
  XDrawText(d, w, gc, x, y, &textitem, 1);
  XSetForeground(d, gc, colours[Black]);
  XFlush(d);
}

void Xwindow::drawBigString(int x, int y, string msg, int colour) {
  ostringstream name;
  name << "-*-helvetica-bold-r-*-*-*-240-" << width/5 << "-" << height/5 << "-*-*-*-*";
  drawStringFont(x, y, msg, name.str(), colour);
}

void Xwindow::drawString(int x, int y, string msg, int colour) {
  XFontStruct * f = XLoadQueryFont(d, "6x13");	
	printMessage(x, y, msg, colour, *f); 
	delete f;
}

