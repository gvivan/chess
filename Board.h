#ifndef BOARD_H
#define BOARD_H

enum moveType {undef=0, regular, capture, pawnDouble, castling, enPassant, promotion};

enum attackType {noAttack=0, attack, kingAttack};


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


    
    
    bool whiteTurn; // TRUE if white's turn, FALSE if black's turn

    /*
    The computer's representation of the board is an array of 64 pointers. This is better than an 8x8 matrix because it
    makes it simpler to check for bounds.
    */
    Piece* board[64];
    attackType attacks[64];

    // The position of the attacking piece if checkCount==1 (set to -1 otherwise)
    int attackingPiece;

    /*
    Here, we keep track of which pieces are pinned to clear the pins before updating.
    */
    std::vector<Piece*> pins;

    /*
    We keep track of the moves played in a vector to allow for undos
    */
    std::vector<Move> movePlayed;

    /*
    We save the moves generated for this turn (this is only beneficial for human moves)
    */
    std::vector<Move> movesGenerated;

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


    int checkCount; // the number of pieces that are checking the king

    bool WQcastle; // TRUE if white has castling rights on queenside
    bool WKcastle; // ...
    bool BQcastle;
    bool BKcastle;
    
public:
    void makeMove(Move move);
    void importFEN(std::string FEN);

    // this function updates the attacks map as well as the check count and pins
    void updateAttacks();


    std::vector<Move> generateMoves();




};


#endif
