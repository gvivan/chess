#ifndef PAWN_H
#define PAWN_H

class Pawn : public Piece {
public:
    Pawn(Board* owner, int pos, char type): Piece{owner, pos, type} {}; // type should be 'P' or 'p'
    virtual void generateAttacks();
    virtual void getMoves(std::vector<Move>& moves);
}

#endif
