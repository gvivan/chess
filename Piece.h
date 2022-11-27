#ifndef PIECE_H
#define PIECE_H

class Piece {
private:
    const Board* owner;
    int pos;
    char type;
    bool isCaptured;
protected:
    int getPos() {return pos;};
    Piece* pieceAt(int location) {return owner->board[location];};
    



    // the directions starting from bottom left to top right
    static const int direction(int index) {
        static const int dir[] = {-9, -8, -7, -1, 1, 7, 8, 9};
    };

public:
    Piece(Board* owner, int pos, char type, Team team): owner{owner}, pos{pos}, type{type}, team{team} {};
    virtual int getVal() {return value;};

    // checkMove return 0 if move is valid, 1 if move leaves King exposed, 2 if move is invalid, 3 if move is blocked
    virtual int checkMove(Move& move) = 0;

    virtual std::vector<Move> getMoves() = 0; // generate a vector of all legal moves for this piece
    virtual char getPiece() {return type;};

}

#endif
