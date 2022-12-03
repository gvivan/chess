#ifndef KNIGHT_H
#define KNIGHT_H

class Knight : public Piece {
private:
    static const int KnightDirection(int index) {
        static const int dir[] = {-8, -1, 1, 8, -9, -7, 7, 9};
    };
public:
    Knight(Board* owner, int pos, char type, bool isWhite, int value): Piece{owner, pos, type, isWhite, value} {}; // type should be 'N' or 'n'
    virtual void generateAttacks();
    virtual void getMoves(std::vector<Move>& moves);
}

#endif
