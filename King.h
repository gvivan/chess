#ifndef KING_H
#define KING_H

class King : public Piece {
public:
    King(Board* owner, int pos, char type, bool team): Piece{owner, pos, type, team} {}; // type should be 'K' or 'k'
    virtual std::vector<Move> getMoves();
}

#endif
