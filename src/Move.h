#ifndef MOVE_H
#define MOVE_H

#include <iostream>

enum moveType {undef=0, regular, capture, pawnDouble, Qcastling, Kcastling, enPassant, promotion};

enum attackType {noAttack=0, attack, kingAttack};

class Piece;

int coordinateToInt(std::string coordinate);

class Move {
private:
    char toChar(int a) const{
    return a + 'a' - 1;
    }
public:
    int value = 0;
    int start;
    int end;
    Piece* captured;
    moveType type;
    char promotionPiece;
    void print() const {
        int start_x = start / 8;
        int start_y = start - (start_x * 8) + 1;
        int end_x = end / 8;
        int end_y = end - (end_x * 8) + 1;
        std::cout << toChar(start_y) << start_x + 1 << toChar(end_y) << end_x + 1 << std::endl;
        if(type == promotion){
            std::cout << "promoted to: " << promotionPiece << std::endl;
        }
    }

    bool operator==(Move move){
        return this->start == move.start && this->end == move.end && this->promotionPiece == move.promotionPiece;
    }

    bool operator<(Move move){
        return this->value < move.value;
    }

};

#endif
