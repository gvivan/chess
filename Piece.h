#ifndef PIECE_H
#define PIECE_H

class Piece {
private:
    const Board* owner;
    int pos;
    char type;
    std::vector<Int> pinSquares;
protected:

    bool isWhite; // this is just so we don't have to check upper or lower case everytime
    int value;
    bool isCaptured;
    

    int getPos() {return pos;};
    Piece* pieceAt(int location) {return owner->board[location];};
    // the directions starting from bottom left to top right
    static const int direction(int index) {
        static const int dir[] = {-9, -8, -7, -1, 1, 7, 8, 9};
    };

    void addCheckCount() {owner->checkCount++};
    int getCheckCount() {return owner->checkCount;};

    // 0 <= pos < 64
    attackType setAttack(int pos) {owner->attacks[pos] = attack;}; 
    attackType setKingAttack (int pos) {owner->attacks[pos] = kingAttack};
    attackType getAttack(int pos) {return owner->attacks[pos];};

    // side==true ==> can kingside castle, ...
    bool castleRights(bool team, bool side);

    bool isPinned() {return !pinSquares.empty()};

    // check if pos is a Pin square
    bool isPin(int pos);

    // add pin square
    void addPin(int pos);

    void setAttackingPiece(int pos) {owner->attackingPiece = pos;};

    int getAttackingPiece() {return owner->attackingPiece;};


public:
    Piece(Board* owner, int pos, char type): owner{owner}, pos{pos}, type{type} {};

    // Set all the squares this piece is attacking to TRUE
    virtual void generateAttacks() = 0;

    // push moves into a given vector
    virtual void getMoves(std::vector<Move>& moves) = 0; 
    
    virtual char getPiece() {return type;};
    virtual bool getTeam() {return isWhite;};

}

#endif
