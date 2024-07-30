#include "Knight.h"
#include <iostream>

using namespace std;

int Knight::KnightMoveData[64][8];

void Knight::initializeKnightData(){
    int x[8] = {-1, 1, -2, 2, -2, 2, -1, 1}; // i
    int y[8] = {-2, -2, -1, -1, 1, 1, 2, 2}; // j
    int target_x;
    int target_y;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            for(int k = 0; k < 8; k++){
                target_x = i + x[k];
                target_y = j + y[k];
                if(0 <= target_x && target_x < 8 && 0 <= target_y && target_y < 8){
                    KnightMoveData[i * 8 + j][k] = target_x * 8 + target_y;
                }else{
                    KnightMoveData[i * 8 + j][k] = -1;
                }
            }
        }
    }
}

void Knight::generateAttacks(){

    // do nothing if the piece is captured
    if(this->getIsCaptured()){
         return;
    }

    int target;

    char enemyKing;
    // set enemy king char depending on our team
    if(this->getTeam()){
        enemyKing = 'k';
    }else{
        enemyKing = 'K';
    }
    for(int i = 0; i < 8; i++){
        target = KnightMoveData[getPos()][i];
        if(target != -1){
            setAttack(target);

            if(pieceAt(target) != nullptr){
                if(pieceAt(target)->getPiece() == enemyKing){

                    /* 
                    If the Piece attacks the king, increase checkCount and set attcking piece to current position.
                    */
                    addCheckCount();
                    setAttackingPiece(getPos());
                }
            }
        }
    }
    

}

void Knight::getMoves(vector<Move>& moves){

    if(this->getIsCaptured()){
        return;
    }else if(this->isPinned()){
        return;
    }
    
    Move move;
    move.start = getPos();
    move.promotionPiece = '*';
    bool check = (getCheckCount() == 1);
    int target;

    for(int i = 0; i < 8; i++){

        target = KnightMoveData[getPos()][i];

        if(target != -1){ // if its a valid move

            move.end = target;
            if(check){
                // If check, only consider moves that block it or capture attacking piece
                if(getAttack(target) != kingAttack && target != getAttackingPiece()){
                    continue;
                }
            }

            if(pieceAt(target) != nullptr){
                if(pieceAt(target)->getTeam() == this->getTeam()){
                    continue;
                }else{
                    // In the future, we can guess the value of this move based on the capture
                    move.type = capture;
                    move.captured = pieceAt(target);
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

        