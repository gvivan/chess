#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_

#include <iostream>
#include <string>
#include <vector>

class textDisplay {
    public:
    std::vector<std::vector<char>> board;
    
    textDisplay();
    void printBoard(const std::string fen);

};

std::ostream &operator<<(std::ostream &out, const textDisplay &t);

#endif
