#ifndef PIECE_H
#define PIECE_H

#include <memory>
#include <vector>
#include "Move.h"

class Board;
class King;

class Piece {
private:
    Board* const owner;
    int pos;
    char type;
    bool isWhite; // this is just so we don't have to check upper or lower case everytime
    int value;
    bool isCaptured;
    std::vector<int> pinSquares;
protected:

        // This holds the limit square in each direction from every square.
    static int moveData[64][8];

    Piece* pieceAt(int location);
    // the directions, 0-3 are Rook directions, 4-7 are Bishop directions. Pawn moves are [0] (move up), [4] and [5] (attack), offset by 2 for black.
    static const int direction(int index) {
        static const int dir[] = { 8, 1, -8, -1, 9, 7, -9, -7};
        return dir[index];
    };

    void addCheckCount();
    int getCheckCount();

    // 0 <= pos < 64
    void setAttack(int pos); 
    void setKingAttack (int pos);
    attackType getAttack(int pos);

    // side==true ==> can kingside castle, ...
    bool castleRights(bool team, bool side);

    // TRUE if piece is pinned
    bool isPinned();

    // check if pos is a Pin square
    bool isPin(int square);


    void setAttackingPiece(int square);

    int getAttackingPiece();

    int getEnPassant();

    // This checks the legality of a enPassant move.
    bool checkEnPassant(Move move);



public:

    virtual ~Piece() {};
    Piece(Board* owner, int pos, char type, bool isWhite, int value): owner{owner}, pos{pos}, type{type}, isWhite{isWhite}, value{value}, isCaptured{false} {};

    // Virtual Constructor, call this on board to return a unique pointer
    static std::unique_ptr<King> CreateUniqueKing(Board* owner, int pos, char type);
    static std::unique_ptr<Piece> CreateUniquePiece(Board* owner, int pos, char type);

    // Set all the squares this piece is attacking to TRUE
    virtual void generateAttacks() = 0;

    // push moves into a given vector
    virtual void getMoves(std::vector<Move>& moves) = 0; 
    
    char getPiece();
    bool getTeam();

    void setCapture(bool set);

    int getPos();
    void setPos(int set);

    bool getIsCaptured();

    void clearPins();

    // add pin square
    void addPin(int square);

    // Call this before anything!!
    static void initializeData();



};


#endif
