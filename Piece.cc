#include "Piece.h"
#include <cctype>

using namespace std;

Piece* Piece::CreateUniquePiece(Board* owner, int pos, char type){
    bool team = isupper(type);
    switch (tolower(type)) {
        case 'k':
            return make_unique<King>(owner, pos, type, team, 100); // 100 is arbitrary, idk yet
            break;
        case 'q':
            return make_unique<Queen>(owner, pos, type, team, 9); 
            break;
        case 'r':
            return make_unique<Rook>(owner, pos, type, team, 5); 
            break;
        case 'b':
            return make_unique<Bishop>(owner, pos, type, team, 3); 
            break;
        case 'n':
            return make_unique<Knight>(owner, pos, type, team, 3); 
            break;
        case 'p':
            return make_unique<Pawn>(owner, pos, type, team, 1); 
            break;
        default:
            return nullptr;
            break;
    }
}

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
