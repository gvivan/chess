#ifndef _GRAPHICSDISPLAY_H_
#define _GRAPHICSDISPLAY_H_

#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include "window.h"

class graphicsDisplay {
	Xwindow window;
	int size;

	public:
	graphicsDisplay();
	void printBoard(const std::string fen);
	~graphicsDisplay();
};
#endif
