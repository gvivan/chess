#include "Knight.h"

using namespace std;

void Knight::generateAttacks(){

    // do nothing if the piece is captured
    if(isCaptured){
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
        target = getPos() + KnightDirection(i);
        if(0 <= target && target > 64){
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

    if(isCaptured){
        return;
    }else if(getCheckCount() > 1){
        return;
        /*
        Note that if a Knight is pinned, it cannot move.
        */
    }else if(this->isPinned()){
        return;
    }
    
    Move move;
    move.start = getPos();
    move.promotionPiece = '*';
    bool check = (getCheckCount() == 1);

    for(int i = start; i =< end; i++){

        for(int target = getPos() + KnightDirection(i); 0 <= target && target < 64; target += KnightDirection(i)){
            move.end = target;
            if(check){
                // If check, only consider moves that block it or capture attacking piece
                if(getAttack(target) != kingAttack && target != getAttackingPiece()){
                    continue;
                }
            }
            if(pieceAt(target) != nullptr){
                if(pieceAt(target)->getTeam() == this->getTeam()){
                    break;
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
