#ifndef ROOK_H
#define ROOK_H

class Rook : public SlidingPieces {
public:
    /*
    Note: We set the range as 0-3
    */
    Rook(Board* owner, int pos, char type, bool isWhite, int value): SlidingPieces{owner, pos, type, isWhite, value, 0, 3} {};
};

#endif
