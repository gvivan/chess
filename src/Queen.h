#ifndef QUEEN_H
#define QUEEN_H

class Queen : public SlidingPieces {
public:
    /*
    Note: We set the range as 0-7
    */
    Queen(Board* owner, int pos, char type, bool isWhite, int value): SlidingPieces{owner, pos, type, isWhite, value, 0, 7} {};
};

#endif
