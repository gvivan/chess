#include "King.h"
#include "Move.h"
#include <cctype>
#include "Piece.h"

using namespace std;



void King::generateAttacks(){
    int target;
    for(int i = 0; i < 8; i++){
        target = getPos() + direction(i);
        if(target != moveData[getPos()][i]){
            setAttack(target);
        }
    }
}

void King::getMoves(vector<Move>& moves){

    /*
    if(this->getTeam()){
        cout << "getting white King moves..." << endl;
    }else{
        cout << "getting black King moves..." << endl;
    }
    */
    Move move;
    cout << "King pos: " << getPos() << endl;
    move.start = getPos();
    move.promotionPiece = '*';
    move.captured = nullptr;

    if(castleRights(this->getTeam(), true)){ // checking kingside castle
        /*
        cout << "checking castle for: " << this->getTeam() << endl;
        cout << "attack status: ";
        cout << static_cast<int>(getAttack(move.start)) << static_cast<int>(getAttack(move.start + 1)) << static_cast<int>(getAttack(move.start + 2)) << endl;

        cout << "space status: " << (pieceAt(move.start + 1) == nullptr) << (pieceAt(move.start + 2) == nullptr) << endl;
        */

        if(getAttack(move.start) == noAttack && getAttack(move.start + 1) == noAttack && getAttack(move.start + 2) == noAttack
        && pieceAt(move.start + 1) == nullptr && pieceAt(move.start + 2) == nullptr){
            cout << "castling..." << endl;
            cout << move.start << endl;
            move.end = getPos() + 2;
            move.type = Kcastling;
            moves.push_back(move);
        }
    }

    if(castleRights(this->getTeam(), false)){ // checking queenside castle
        if(getAttack(move.start) == noAttack && getAttack(move.start - 1) == noAttack && getAttack(move.start - 2) == noAttack
        && pieceAt(move.start - 1) == nullptr && pieceAt(move.start - 2) == nullptr && pieceAt(move.start - 3) == nullptr){
            move.end = getPos() - 2;
            move.type = Qcastling;
            moves.push_back(move);
        }
    }
    
    int target;

    for(int i = 0; i < 8; i++){

        target = getPos() + direction(i);

        if(target != moveData[getPos()][i] && getAttack(target) == noAttack){
            move.end = target;

            if(pieceAt(target) != nullptr){

                if(pieceAt(target)->getTeam() != this->getTeam()){
                    move.captured = pieceAt(target);
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
        for(int target = getPos() + direction(i); target != moveData[getPos()][i]; target += direction(i)){
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
        for(int target = getPos() + direction(i); target != moveData[getPos()][i]; target += direction(i)){
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



