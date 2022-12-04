#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"

class Knight : public Piece {
private:
    static const int KnightDirection(int index) {
        static const int dir[] = {-17, -15, -10, -6, 6, 10, 15, 17};
        return dir[index];
    };
public:
    Knight(Board* owner, int pos, char type, bool isWhite, int value): Piece{owner, pos, type, isWhite, value} {}; // type should be 'N' or 'n'
    virtual void generateAttacks();
    virtual void getMoves(std::vector<Move>& moves);
};

#endif
