#include "Pawn.h"
#include <vector>

using namespace std;

void Pawn::generateAttacks(){

    // do nothing if the piece is captured
    if(this->getIsCaptured()){
            return;
    }

    int target;
    int offset;
    char enemyKing;
    // set enemy king char depending on our team and setting offset.
    if(this->getTeam()){
        enemyKing = 'k';
        offset = 0;
    }else{
        enemyKing = 'K';
        offset = 2;
    }

    for(int i = 4; i <= 5; i++){
        target = getPos()+ direction(i + offset);
        if(target != moveData[getPos()][i + offset]){ // this checks whether the pawn is at the edge of the board
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

    // write stuff
    
}

void Pawn::getMoves(vector<Move>& moves){

    if(this->getIsCaptured()){
        return;
    }

    Move move;
    move.start = getPos();
    move.captured = nullptr;
    move.promotionPiece = '*';
    int target;
    int offset;
    if(this->getTeam()){
        offset = 0;
    }else{
        offset = 2;
    }

    bool check = (getCheckCount() == 1);

    // Generate attacking moves
    for(int i = 4; i <= 5; i++){
        target = getPos()+ direction(i + offset);
        if(target != moveData[getPos()][i + offset]){
            if(check && getAttack(target) != kingAttack){
                continue;
            }
            if(isPinned() && !(isPin(target))){
                continue;
            }
            if(pieceAt(target) != nullptr){
                if(pieceAt(target)->getTeam() == this->getTeam()){
                    continue;
                }else{
                    move.end = target;
                    move.type = capture;
                    move.captured = pieceAt(target);
                    if(target > 55 || target < 8){
                        move.type = promotion;
                        if(this->getTeam()){
                            for(char p : {'Q', 'R', 'B', 'N'}){
                                move.promotionPiece = p;
                                moves.push_back(move);
                            }
                        }else{
                            for(char p : {'q', 'r', 'b', 'n'}){
                                move.promotionPiece = p;
                                cout << p << endl;
                                moves.push_back(move);
                            }
                        }  
                    }else{
                        moves.push_back(move);
                    }  
                }
            }else if(target == getEnPassant()){
                move.end = target;
                move.type = enPassant;
                move.captured = pieceAt(target + direction(2 - offset));
                if(checkEnPassant(move)){
                    moves.push_back(move);
                }
            }
        }
    }

    

    // Generate 1 up move
    target = getPos() + direction(offset);
    if(target != moveData[getPos()][offset]){
        if( !((isPinned() && !(isPin(target))) || pieceAt(target) != nullptr) ){
            if(!check || getAttack(target) == kingAttack){
                move.end = target;
                if(target > 55 || target < 8){
                    move.type = promotion;
                    if(this->getTeam()){
                        for(char p : {'Q', 'R', 'B', 'N'}){
                            move.promotionPiece = p;
                            moves.push_back(move);
                        }
                    }else{
                        for(char p : {'q', 'r', 'b', 'n'}){
                            move.promotionPiece = p;
                            moves.push_back(move);
                        }
                    }
                        
                }else{
                    move.type = regular;
                    moves.push_back(move);
                }
            }
            
            // Generate double up move
            target += direction(offset);
            if(!check || getAttack(target) == kingAttack){
                if((getTeam() && move.start < 16) || (!getTeam() && move.start > 40)){
                    if(pieceAt(target) == nullptr){
                        move.end = target;
                        move.type = pawnDouble;
                        moves.push_back(move);
                    }
                }
            }
        }
    }
}
