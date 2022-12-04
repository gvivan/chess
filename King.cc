#include "King.h"
#include <cctype>

using namespace std;



void King::generateAttacks(){
    int target;
    for(int i = 0; i < 8; i++){
        target = getPos() + direction(i);
        if(0 <= target && target > 64){
            setAttack(target);
        }
    }
}

void King::getMoves(vector<Move>& moves){

    Move move;
    move.start = getPos();
    move.promotionPiece = '*';
    move.captured = nullptr;

    if(castleRights(this->getTeam(), true)){ // checking kingside castle
        if(getAttack(move.start) == noAttack && getAttack(move.start + 1) == noAttack && getAttack(move.start + 2) == noAttack){
            move.end = getPos() + 2;
            move.type = Kcastling;
            moves.push_back(move);
        }
    }

    if(castleRights(this->getTeam(), false)){ // checking queenside castle
        if(getAttack(move.start) == noAttack && getAttack(move.start - 1) == noAttack && getAttack(move.start - 2) == noAttack){
            move.end = getPos() - 2;
            move.type = Qcastling;
            moves.push_back(move);
        }
    }
    
    int target;
    Piece* PieceCapture;

    for(int i = 0; i < 8; i++){

        target = getPos() + direction(i);

        if(0 <= target && target > 64 && !getAttack(target)){
            move.end = target;
            PieceCapture = pieceAt(target);

            if(PieceCapture != nullptr){

                if(PieceCapture->getTeam() != this->getTeam()){
                    move.captured = PieceCapture;
                    move.type = capture;
                    // here, we could give a value to moves depending on what was captured (to do later)
                    moves.push_back(move);
                }
            }else{
                move.captured = nullptr;
                move.type = regular;
                moves.push_back(move);
            }

        }
    }

}

bool King::inCheck(){
    for(int i = 0; i <= 3; i++){
        for(int target = getPos() + direction(i); 0 <= target && target < 64; target += direction(i)){
            if(pieceAt(target) != nullptr){
                if(pieceAt(target)->getTeam() == this->getTeam()){
                    break;
                }else if(toupper(pieceAt(target)->getPiece()) == 'Q' || toupper(pieceAt(target)->getPiece()) == 'R'){
                    return true;
                }
            }
        }
    }

    for(int i = 4; i <= 7; i++){
        for(int target = getPos() + direction(i); 0 <= target && target < 64; target += direction(i)){
            if(pieceAt(target) != nullptr){
                if(pieceAt(target)->getTeam() == this->getTeam()){
                    break;
                }else if(toupper(pieceAt(target)->getPiece()) == 'Q' || toupper(pieceAt(target)->getPiece()) == 'B'){
                    return true;
                }
            }
        }
    }

    return false;
}



