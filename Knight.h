#ifndef KNIGHT_H
#define KNIGHT_H

class Knight : public Piece {
public:
    Knight(Board* owner, int pos, char type): Piece{owner, pos, type} {}; // type should be 'N' or 'n'
    virtual void generateAttacks();
    virtual void getMoves(std::vector<Move>& moves);
}

#endif
