#include "King.h"

using namespace std;

Queen::Queen(Board* owner, int pos, char type){
    if(type == 'Q'){
        isWhite = true;
    }else{
        isWhite = false;
    }
    value = 9; // this might be changed later depending how we evaluate things

    // the king can never be captured or pinned
    isCaptured = false;
    thePin = nullptr;
}

void Queen::generateAttacks(){
    
    // do nothing if the piece is captured
    if(isCaptured){
        return;
    }

    char enemyKing;
    // set enemy king char depending on our team
    if(this->getTeam()){
        enemyKing = 'k';
     }else{
        enemyKing = 'K';
     }

    for(int i = 0; i < 8; i++){
        for(int target = getPos() + direction(i); 0 <= target && target < 64; target += direction(i)){
            setAttack(target);

            // if there is a piece at the square
            if(pieceAt(target) != nullptr){
                if(pieceAt(target)->getTeam() == this->getTeam()){
                    break;
                }else if(pieceAt(target)->getPiece() == enemyKing){

                    /* 
                    if the attacked piece is the king, set the previous squares to kingAttack, increase the check counter,
                    and continue the loop.
                    ...
                    Notice that we set getPos() to be a kingAttack square for capturing purposes
                    */
                    addCheckCount();
                    setAttackingPiece(getPos());
                    for(int back = target; back != getPos() - direction(i); back -= direction(i)){
                        setKingAttack(back);
                    }
                }else{

                    /*
                    Here, we check for pins by 
                    */
                    

                    for(int king = target + direction(i); 0 <= king && king < 64; king += direction(i)){

                        if(pieceAt(king) != nullptr){
                            if(pieceAt(king)->getPiece == enemyKing){
                                /*
                                Here, we add the squares on the ray to the pin vector of the target piece, restricting its movement
                                */
                                for(int back = king - direction(i); back != getPos() - direction(i); back -= direction(i)){
                                    pieceAt(target)->addPin(back);
                                }
                            }
                        }else{
                            break;
                        }
                    }
                }
                /*
                If the king is not found on the ray, then no pin is generated. 
                */
            }
        }
    }
    /*
    To recap, we found every piece this piece attacks and marked it. If we get to one of our pieces,
    we mark that square then proceed to next direction. If we found the enemy king on one of those squares,
    we marked the ray as kingAttack, and updated the check counter. Finally, if we find an enemy piece, we continue
    and add pin squares if we find the king, nothing otherwise.
    */

}


// plz account for check and stuff

void getMoves(std::vector<Move>& moves){

    // do nothing if the piece is captured
    if(isCaptured){
        return;
    }else if(getCheckCount() > 1){
        return;
    }
    
    Move move;
    move.start = getPos();
    bool check = (getCheckCount() == 1);

    for(int i = 0; i < 8; i++){

        /*
        We check whether the direction aligns with the pin. Note we only need to check this once per direction, since
        the pin is always in a ray.
        */
        if(isPinned){
            if(!isPin(target + direction(i))){
                continue;
            }
        }


        for(int target = getPos() + direction(i); 0 <= target && target < 64; target += direction(i)){
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
