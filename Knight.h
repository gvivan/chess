#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"

class Knight : public Piece {
private:
    // This holds every legal move for Knights, -1 if not legal
    static int KnightMoveData[64][8];


public:
    Knight(Board* owner, int pos, char type, bool isWhite, int value): Piece{owner, pos, type, isWhite, value} {}; // type should be 'N' or 'n'
    virtual void generateAttacks();
    virtual void getMoves(std::vector<Move>& moves);

    // Also call this plz
    static void initializeKnightData();
};

#endif
