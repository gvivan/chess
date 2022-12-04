#ifndef KING_H
#define KING_H


class King : public Piece {
public:
    King(Board* owner, int pos, char type, bool isWhite, int value): Piece{owner, pos, type, isWhite, value} {}; // type should be 'K' or 'k'
    virtual void generateAttacks();
    virtual void getMoves(std::vector<Move>& moves);

    // This function should only be run if an enPassant move has been played.
    bool inCheck();
};

#endif
