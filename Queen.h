#ifndef QUEEN_H
#define QUEEN_H

class Queen : public Piece {
public:
    Queen(Board* owner, int pos, char type): Piece{owner, pos, type} {}; // type should be 'K' or 'k'
    virtual void generateAttacks();
    virtual void getMoves(std::vector<Move>& moves);
}

#endif
