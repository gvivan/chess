#include "Board.h"
#include <sstream>
#include <cctype>
#include <string>
#include <iostream>

#include "Piece.h"
#include "Knight.h"

using namespace std;

Board::Board(){
    
    Piece::initializeData();
    Knight::initializeKnightData();

    initialized = false;
    whiteTurn = true;
    attackingPiece = -1;
    enPassantSquare = -1;
    numW = 0;
    numB = 0;
    checkCount = 0;
    WQcastle = true;
    WKcastle = true;
    BQcastle = true;
    BKcastle = true;
}

void Board::updateAttacks(){
    checkCount = 0;
    for(int i = 0; i < 64; i++){
        attacks[i] = noAttack;
    }
    attackingPiece = -1;
    if(!whiteTurn){
        for(int i = 0; i < numW; i++){
            WPieces[i]->clearPins();
            WPieces[i]->generateAttacks();
        }
    }else{
        for(int i = 0; i < numB; i++){
            BPieces[i]->clearPins();
            BPieces[i]->generateAttacks();
        }
    }
}

void Board::generateMoves(std::vector<Move> &moves){
    if(whiteTurn){
        for(int i = 0; i < numW; i++){
            WPieces[i]->getMoves(moves);
        }
    }else{
        for(int i = 0; i < numB; i++){
            BPieces[i]->getMoves(moves);
        }
    }
}

void Board::makeMove(Move move){
    enPassantSquare = -1;

    // editing castle rights
    if(whiteTurn){
        if(move.start == 4){
            WQcastle = false;
            WKcastle = false;
        }if(move.start == 0 || move.end == 0){
            WQcastle = false;
        }else if(move.start == 7 || move.end == 7){
            WKcastle = false;
        }
    }else{
        if(move.start == 60){
            WQcastle = false;
            WKcastle = false;
        }if(move.start == 56 || move.end == 56){
            WQcastle = false;
        }else if(move.start == 63 || move.end == 63){
            WKcastle = false;
        }
    }
    

    board[move.end] = board[move.start];
    board[move.start] = nullptr;
    board[move.end]->setPos(move.end);
    if(move.type == regular){
        // do nothing
    }else if(move.type == capture){
        move.captured->setCapture(true);
    }else if(move.type == pawnDouble){
        if(whiteTurn){
            enPassantSquare = move.end - 8;
        }else{
            enPassantSquare = move.end + 8;
        }
    }else if(move.type == Kcastling){
        board[move.start + 1] = board[move.start + 3];
        board[move.start + 3] = nullptr;
    }else if(move.type == Qcastling){
        board[move.start - 1] = board[move.start - 4];
        board[move.start - 4] = nullptr;
    }else if(move.type == enPassant){
        move.captured->setCapture(true);
        board[move.captured->getPos()] = nullptr;
    }else if(move.type == promotion){
        if(whiteTurn){
            for(int i = 0; i < numW; i++){
                if(board[move.end] == WPieces[i].get()){
                    WPieces[i].reset();
                    WPieces[i] = Piece::CreateUniquePiece(this, move.end, move.promotionPiece);
                    board[move.end] = WPieces[i].get();
                    break;
                }
            }
        }else{
            for(int i = 0; i < numB; i++){
                if(board[move.end] == BPieces[i].get()){
                    BPieces[i].reset();
                    BPieces[i] = Piece::CreateUniquePiece(this, move.end, move.promotionPiece);
                    board[move.end] = BPieces[i].get();
                    break;
                }
            }
        }
    }
    movesPlayed.push_back(move);
    
    whiteTurn = !whiteTurn;

    updateAttacks();
    // print();
}

void Board::unmakeMove(){
    Move move = movesPlayed.back();
    enPassantSquare = -1;
    movesPlayed.pop_back();

    // checking castling rights...
    if(!whiteTurn){
        for(int i : {0, 4, 7}){
            if(move.start == i){
                for(auto p : movesPlayed){
                    if(p.start == i){
                        if(i == 0){
                            WQcastle = false;
                        }else if(i == 4){
                            WQcastle = false;
                            WKcastle = false;
                        }else{
                            WKcastle = false;
                        }
                        
                        break;
                    }
                }
            }
        }
    }else{
        for(int i : {56, 60, 63}){
            if(move.start == i){
                for(auto p : movesPlayed){
                    if(p.start == i || p.end == i){
                        if(i == 56){
                            WQcastle = false;
                        }else if(i == 60){
                            WQcastle = false;
                            WKcastle = false;
                        }else{
                            WKcastle = false;
                        }
                        
                        break;
                    }
                }
            }
        }
    }
    
    board[move.start] = board[move.end];
    board[move.end]->setPos(move.start);
    if(move.type == regular || move.type == pawnDouble){
        board[move.end] = nullptr;
    }else if(move.type == capture){
        board[move.end] = move.captured;
        move.captured->setCapture(false);
    }else if(move.type == Kcastling){
        board[move.start + 3] = board[move.start + 1];
        board[move.start + 1] = nullptr;
    }else if(move.type == Qcastling){
        board[move.start - 4] = board[move.start - 1];
        board[move.start - 1] = nullptr;
    }else if(move.type == enPassant){
        board[move.captured->getPos()] = move.captured;
    }else if(move.type == promotion){
        if(whiteTurn){
            for(int i = 0; i < numW; i++){
                if(board[move.start] == WPieces[i].get()){
                    WPieces[i].reset();
                    WPieces[i] = Piece::CreateUniquePiece(this, move.start, 'P');
                    board[move.start] = WPieces[i].get();
                    break;
                }
            }
        }else{
            for(int i = 0; i < numB; i++){
                if(board[move.start] == BPieces[i].get()){
                    BPieces[i].reset();
                    BPieces[i] = Piece::CreateUniquePiece(this, move.start, 'p');
                    board[move.start] = BPieces[i].get();
                    break;
                }
            }
        }
    }
    
    if(!movesPlayed.empty()){
        if(movesPlayed.back().type == pawnDouble){
            if(whiteTurn){
                enPassantSquare = movesPlayed.back().end - 8;
            }else{
                enPassantSquare = movesPlayed.back().end + 8;
            }
        }
    }
    whiteTurn = !whiteTurn;
    updateAttacks();
     // print();
}

int todigit(char c){
  return c - '0';
}

void Board::importFEN(std::string FEN){
    std::stringstream s(FEN);
    char input;
    for(int i = 63; i >= 0; --i){
        s >> input;
        if(input == '/'){
            s >> input;
        }
        if(isdigit(input)){
            int k = i - todigit(input);
            while(i > k + 1){
                board[i] = nullptr;
                --i;
            }
            board[i] = nullptr;
            
        }else if(isupper(input)){
            if(input == 'K'){
                WKing = Piece::CreateUniqueKing(this, i, input);
                board[i] = WKing.get();
            }else{
                WPieces[numW] = Piece::CreateUniquePiece(this, i, input);
                board[i] = WPieces[numW].get();
                numW++;
            }
        }else{
            if(input == 'k'){
                BKing = Piece::CreateUniqueKing(this, i, input);
                board[i] = BKing.get();
            }else{
                BPieces[numB] = Piece::CreateUniquePiece(this, i, input);
                board[i] = BPieces[numB].get();
                numB++;
            }
        }
    }
    initialized = true;
    print();
}

int Board::perft(int depth){
    if(depth == 0){
        return 1;
    }
    std::vector<Move> moves;
    int numPos = 0;
    generateMoves(moves);
    for(auto move : moves){
        makeMove(move);
        numPos += perft(depth - 1);
        unmakeMove();
    }
    return numPos;
}

void Board::print() {
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i * 8 + j] == nullptr){
                cout << '-';
            }else{
                cout << board[i * 8 + j]->getPiece();
            }
        }
        cout << endl;
    }
}

int Board::moveNum(){
    return movesPlayed.size();
}


