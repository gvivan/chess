#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];
  int width;
  int height;
  void printMessage(int x, int y, const std::string& msg, int colour, XFontStruct& f);

 public:
  Xwindow(int width=500, int height=500);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.
  //Xwindow(const Xwindow&) = delete;
  //Xwindow &operator=(const Xwindow&) = delete;

  // Available colours.
  enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown};

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg, int colour = Black);
  void drawBigString(int x, int y, std::string msg, int colour = Black);

  void drawStringFont(int x, int y, std::string msg, std::string font, int colour = Black);

  void fillArc(int x, int y, int width, int height, int angle1, int angle2, int colour);
  void fillCircle(int x, int y, int d, int colour = Black);

};

#endif
