#include "Piece.h"
#include <cctype>
#include <memory>
#include "Board.h"
#include "Move.h"
#include "King.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"
#include "SlidingPieces.h"
#include <iostream>

using namespace std;


int Piece::moveData[64][8];

int min(int a, int b){
    if(a < b){
        return a;
    }else{
        return b;
    }
}

void Piece::initializeData(){

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            // Bounds for axis moves
            moveData[i * 8 + j][0] = 56 + j + direction(0); // 7*8 + j
            moveData[i * 8 + j][1] = i * 8 + 7 + direction(1);
            moveData[i * 8 + j][2] = j + direction(2);
            moveData[i * 8 + j][3] = i * 8 + direction(3);

            // Bounds for diagonal moves
            moveData[i * 8 + j][4] = (i + min(7 - i, 7 - j)) * 8 + j + min(7 - i, 7 - j) + direction(4);
            moveData[i * 8 + j][5] = (i + min(7 - i, j)) * 8 + j - min(7 - i, j) + direction(5);
            moveData[i * 8 + j][6] = (i - min(i, j)) * 8 + j - min(i, j) + direction(6);
            moveData[i * 8 + j][7] = (i - min(i, 7 - j)) * 8 + j + min(i, 7 - j) + direction(7);

        }
    }

    
}

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

bool Piece::getIsCaptured(){
	return isCaptured;
}

void Piece::clearPins(){
    pinSquares.clear();
}

unique_ptr<King> Piece::CreateUniqueKing(Board* owner, int pos, char type){
    bool team = isupper(type);
    switch (tolower(type)) {
        case 'k':
            return make_unique<King>(owner, pos, type, team, 100); // 100 is arbitrary, idk yet
            break;
        default:
            return nullptr;
            break;
    }
}

unique_ptr<Piece> Piece::CreateUniquePiece(Board* owner, int pos, char type){
    bool team = isupper(type);
    switch (tolower(type)) {
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
    }else{
        return false;
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

    owner->board[move.end] = owner->board[move.start];
    owner->board[move.start] = nullptr;
    owner->board[move.captured->getPos()] = nullptr;
    if(owner->whiteTurn){
        out = owner->WKing->inCheck();
    }else{
        out = owner->BKing->inCheck();
    }
    owner->board[move.captured->getPos()] = move.captured;
    owner->board[move.start] = owner->board[move.end];
    owner->board[move.end] = nullptr;
    
    return !out;
}


