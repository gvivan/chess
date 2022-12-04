#include "Piece.h"
#include <cctype>
#include <memory>

using namespace std;

Piece* Piece::pieceAt(int location) {
    return owner->board[location];
}

void Piece::addCheckCount(){
    owner->checkCount++;
}

int Piece::getCheckCount(){
    return owner->checkCount;
}

void Piece::setAttack(int pos){
    owner->attacks[pos] = attack;
}

void Piece::setKingAttack (int pos){
    owner->attacks[pos] = kingAttack;
}

attackType Piece::getAttack(int pos){
    return owner->attacks[pos];
}

bool Piece::isPinned(){
    return !pinSquares.empty();
}

void Piece::addPin(int square){
    pinSquares.push_back(square);
}

void Piece::setAttackingPiece(int square){
    owner->attackingPiece = square;
}

int Piece::getAttackingPiece(){
    return owner->attackingPiece;
}

int Piece::getEnPassant(){
    return owner->enPassantSquare;
}

char Piece::getPiece(){
    return type;
}

bool Piece::getTeam(){
    return isWhite;
}

void Piece::setCapture(bool set){
    isCaptured = set;  
}

int Piece::getPos(){
    return pos;
}

void Piece::setPos(int set){
    pos = set;
}

void Piece::clearPins(){
    pinSquares.clear();
}

static unique_ptr<Piece> Piece::CreateUniquePiece(Board* owner, int pos, char type){
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

bool Piece::isPin(int square){
    for(auto k : pinSquares){
        if(k == square){
            return true;
        }
    }
    return false;
}

bool Piece::checkEnPassant(Move move){
    bool out;

    owner->makeMove(move);
    if(owner->whiteTurn){
        out = !(owner->WKing->inCheck());
    }else{
        out = !(owner->BKing->inCheck());
    }
    owner->unmakeMove();
    
    return out;
}

