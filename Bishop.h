#ifndef BISHOP_H
#define BISHOP_H

#include "SlidingPieces.h"

class Bishop : public SlidingPieces {
public:
    /*
    Note: We set the range as 4-7
    */
    Bishop(Board* owner, int pos, char type, bool isWhite, int value): SlidingPieces{owner, pos, type, isWhite, value, 4, 7} {};
    virtual void generateAttacks();
    virtual void getMoves(std::vector<Move>& moves);
};

#endif
