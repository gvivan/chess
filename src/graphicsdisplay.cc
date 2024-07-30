#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "graphicsdisplay.h"

using namespace std;

graphicsDisplay::graphicsDisplay() :
	window{470, 470}, size{50} {

		for(int i = 8; i > 0; i--) {
			window.drawBigString(30, (8-i)*50+45, to_string(i), 1);
		}

		for(char c = 'a'; c <= 'h'; c++) {
			string tmp = "t";
			tmp[0] = c;
			window.drawBigString(50+50*(c-'a')+20, 440, tmp, 1);
		}

		for(int i = 0; i < 8; i++) {
			for(int j = 0; j < 8; j++) {
				if((i+j)%2 == 0) {
					window.fillRectangle((50*i)+50,(50*j)+10,50,50,0);
				} else {
					window.fillRectangle((50*i)+50,(50*j)+10,50,50,1);
				}
			}
		}
	}


void graphicsDisplay::printBoard(const string fen) {
        vector<char> v(fen.begin(), fen.end());
        int row = 0;
        int col = 0;
        for(long unsigned int i = 0; i < v.size(); i++) {
                char piece = v.at(i);
		string tmp = "t";
		tmp[0] = piece;

                if(piece >= '1' && piece <= '8') {
                        int num = piece - '0';
                        for (int j = 0; j < num; j++) {
                                if((row+col)%2 == 0) {
                                        window.fillRectangle((50*col)+50,(50*row)+10,50,50,0);
                                } else {
                                        window.fillRectangle((50*col)+50,(50*row)+10,50,50,1);
                                }
                                col++;
                        }
                } else if (piece == '/') {
                        row++;
                        col = 0;
                } else {
			 if((row+col)%2 == 0) {
				 window.fillRectangle((50*col)+50,(50*row)+10,50,50,0);
				 window.drawBigString((50*col)+70,(row*50)+40,tmp,1);
			 } else {
				 window.fillRectangle((50*col)+50,(50*row)+10,50,50,1);
				 window.drawBigString((50*col)+70,(50*row)+40,tmp,0);
                                }
			//window.fillRectangle(col * 50 + 40 + 30, row * 50 + 10 + 10, 10, 30, 6);
			//window.fillRectangle(col * 50 + 30 + 30, row * 50 + 20 + 10, 30, 10, 6);
			col++;
		}
        }
}


graphicsDisplay::~graphicsDisplay() {}

int main() {
	graphicsDisplay g;
	g.printBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
}

