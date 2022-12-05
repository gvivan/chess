#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>

#include "King.h"

#include "Move.h"

class Board {
private:
    
    bool initialized; // FALSE until importFEN or setup is run
    bool whiteTurn; // TRUE if white's turn, FALSE if black's turn

    /*
    The computer's representation of the board is an array of 64 pointers. This is better than an 8x8 matrix because it
    makes it simpler to check for bounds.
    */
    Piece* board[64];
    attackType attacks[64];

    // The position of the attacking piece if checkCount==1 (it doesn't matter otherwise)
    int attackingPiece;

    // Current enPassant Square (set to -1 if no enPassant)
    int enPassantSquare;

    /*
    We keep track of the moves played in a vector to allow for undos
    */
    std::vector<Move> movesPlayed;

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
    std::unique_ptr<King> WKing;

    int numB;
    std::unique_ptr<Piece> BPieces[63];
    std::unique_ptr<King> BKing;


    int checkCount; // the number of pieces that are checking the king

    bool WQcastle; // TRUE if white has castling rights on queenside
    bool WKcastle; // ...
    bool BQcastle;
    bool BKcastle;

    // this function updates the attacks map as well as the check count and pins
    void updateAttacks();

    friend class Piece;
    
public:
    Board();
    // The move given to makeMove should be legal, except for enPassant checking.
    void makeMove(Move move);
    void unmakeMove();
    void importFEN(std::string FEN);
    void generateMoves(std::vector<Move> &moves);
    int perft(int depth);
    void print();
    int moveNum();

};


#endif
