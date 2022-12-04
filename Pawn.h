#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(Board* owner, int pos, char type, bool isWhite, int value): Piece{owner, pos, type, isWhite, value} {}; // type should be 'P' or 'p'
    virtual void generateAttacks();
    virtual void getMoves(std::vector<Move>& moves);
};

#endif
