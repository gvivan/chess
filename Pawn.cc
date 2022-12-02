#include "Pawn.h"

using namespace std;

Pawn::Pawn(Board* owner, int pos, char type){
    if(type == 'P'){
        isWhite = true;
    }else{
        isWhite = false;
    }
    value = 1; // this might be changed later depending how we evaluate things

    // the king can never be captured or pinned
    isCaptured = false;
    thePin = nullptr;
}

void Pawn::generateAttacks(){

        // do nothing if the piece is captured
        if(isCaptured){
                return;
        }

        int target;
    for(int i = 0; i < 8; i++){
        target = getPos() + direction(i);
        if(0 <= target && target > 64){
            setAttack(target);
        }
    }
}

void Pawn::getMoves(vector<Move>& moves){

    Move move;
    move.start = getPos();
    move.captured = nullptr;

    if(castleRights(isWhite, true)){ // checking kingside castle
        if(getAttack[move.start] == noAttack && getAttack[move.start + 1] == noAttack && getAttack[move.start + 2] == noAttack){
            move.end = getPos() + 2;
            move.type = castling;
            moves.push_back(move)
        }
    }

    if(castleRights(isWhite, false)){ // checking queenside castle
        if(getAttack[move.start] == noAttack && getAttack[move.start - 1] == noAttack && getAttack[move.start - 2] == noAttack){
            move.end = getPos() - 2;
            move.type = castling;
            moves.push_back(move)
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

                if(capture->getTeam() != this->getTeam()){
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
                                                                               83,1          Bot
