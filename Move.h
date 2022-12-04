#ifndef MOVE_H
#define MOVE_H

enum moveType {undef=0, regular, capture, pawnDouble, Qcastling, Kcastling, enPassant, promotion};

enum attackType {noAttack=0, attack, kingAttack};

class Piece;

class Move {
public:
    int start;
    int end;
    Piece* captured;
    moveType type;
    char promotionPiece;
};

#endif
