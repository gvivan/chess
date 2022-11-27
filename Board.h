#ifndef BOARD_H
#define BOARD_H

enum moveType {undef=0, regular, capture, castling, pawnD, pawnU, pawnP, kingDanger};


class Move {
public:
    int start;
    int end;
    Piece* captured;
    moveType type;
};

class Board {
private:
    friend class Piece;
    
    bool whiteToPlay; // TRUE if white to play, FALSE if black to play

    /*
    The computer's representation of the board is an array of 64 pointers. This is better than an 8x8 matrix because it
    makes it simpler to check for bounds.
    */
    Piece* board[64];

    bool attacks[64];

    /*
    To keep track of pieces, we have to arrays of length 63 for each side. This takes advantage
    of the fact that there cannot be more than 16 pieces on each side in a game of chess, making it more efficient than a vector.
    ...
    The first numW elements of the array should have been on the board at the beginning.
    ...
    The Kings are stored seperately to check for checks (since they will never be captured)
    */
    int numW;
    std::unique_ptr<Piece> WPieces[63];
    std::unique_ptr<Piece> WKing;

    int numB;
    std::unique_ptr<Piece> BPieces[63];
    std::unique_ptr<Piece> BKing;


    bool whiteCheck; // TRUE if it's white to play and white king is checked
    bool whiteMate; // TRUE if it's white to play and white king is checked with no moves
    bool blackCheck; // ...
    bool blackMate;

    bool WQcastle; // TRUE if white has castling rights on queenside
    bool WKcastle; // ...
    bool BQcastle;
    bool BKcastle;
    
public:
    void makeMove(Move move);
    void importFEN(std::string FEN);
    std::vector<Move> generateWhite();
    std::vector<Move> generateBlack();




};


#endif
