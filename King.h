#ifndef KING_H
#define KING_H

class King : public Piece {
public:
    King(Board* owner, int pos, char type): Piece{owner, pos, type} {}; // type should be 'K' or 'k'
    virtual void generateAttacks();
    virtual void getMoves(std::vector<Move>& moves);
}

#endif
