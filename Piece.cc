#include "Piece.h"

bool Piece::castleRights(bool team, bool side){
    if(team && side){
        return owner->WKcastle;
    }else if(team && !side){
        return owner->WQcastle;
    }else if(!team && side){
        return owner->BKcastle;
    }else if(!team && !side){
        return owner->BQcastle;
    }
}

bool Piece::isPin(int pos){
    for(auto k : pinSquares){
        if(k == pos){
            return true;
        }
    }
    return false;
}
