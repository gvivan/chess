#include "Board.h"
#include <sstream>
#include <cctype>
#include <string>
#include <iostream>

#include "Piece.h"
#include "Knight.h"

using namespace std;

int captureCount = 0;
int EPcount = 0;
int castlingCount = 0;

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

    WQcastle = false;
    WKcastle = false;
    BQcastle = false;
    BKcastle = false;
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
        WKing->generateAttacks();
    }else{
        for(int i = 0; i < numB; i++){
            BPieces[i]->clearPins();
            BPieces[i]->generateAttacks();
        }
        BKing->generateAttacks();
    }
    // printAttacks();
}

void Board::generateMoves(std::vector<Move> &moves){
    if(whiteTurn){
        if(checkCount < 2){
            for(int i = 0; i < numW; i++){
                cout << "generating for: " << WPieces[i]->getPiece() << endl;
                WPieces[i]->getMoves(moves);
                
            }
        }
        WKing->getMoves(moves);
        cout << "generating for: " << WKing->getPiece() << endl;
    }else{
        if(checkCount < 2){
            for(int i = 0; i < numB; i++){
                BPieces[i]->getMoves(moves);
            }
        }
        BKing->getMoves(moves);
    }
}

void Board::makeMove(const Move move){
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
        }else if(move.start == 60){
            BQcastle = false;
            BKcastle = false;
        }if(move.start == 56 || move.end == 56){
            BQcastle = false;
        }else if(move.start == 63 || move.end == 63){
            BKcastle = false;
        }
    }
    

    board[move.end] = board[move.start];
    board[move.start] = nullptr;
    board[move.end]->setPos(move.end);
    if(move.type == regular){
        // do nothing
    }else if(move.type == capture){
        captureCount++;
        move.captured->setCapture(true);
    }else if(move.type == pawnDouble){
        if(whiteTurn){
            enPassantSquare = move.end - 8;
        }else{
            enPassantSquare = move.end + 8;
        }
    }else if(move.type == Kcastling){
        castlingCount++;
        cout << board[move.end]->getPiece();
        cout << board[move.start + 2]->getPiece();
        board[move.start + 1] = board[move.start + 3];
        board[move.start + 3] = nullptr;
    }else if(move.type == Qcastling){
        castlingCount++;
        board[move.start - 1] = board[move.start - 4];
        board[move.start - 4] = nullptr;
    }else if(move.type == enPassant){
        captureCount++;
        EPcount++;
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
    board[move.start]->setPos(move.start);
    if(move.type == regular || move.type == pawnDouble){
        board[move.end] = nullptr;
    }else if(move.type == capture){
        board[move.end] = move.captured;
        move.captured->setCapture(false);
    }else if(move.type == Kcastling){
        board[move.start + 3] = board[move.start + 1];
        board[move.start + 1] = nullptr;
        board[move.end] = nullptr;
    }else if(move.type == Qcastling){
        board[move.start - 4] = board[move.start - 1];
        board[move.start - 1] = nullptr;
        board[move.end] = nullptr;
    }else if(move.type == enPassant){
        board[move.captured->getPos()] = move.captured;
        move.captured->setCapture(false);
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
    for(int i = 7; i >= 0; --i){
        for(int j = 0; j < 8; j++){
            cout << "x: " << i << endl;
            cout << "y: " << j << endl;
            cout << "Square: " << i * 8 + j <<  endl;
            s >> input;
            if(input == '/'){
                s >> input;
            }
            cout << "Input: " << input << endl;
            if(isdigit(input)){
                int k = j + todigit(input);
                while(j < k - 1){
                    board[i * 8 + j] = nullptr;
                    ++j;
                }
                board[i * 8 + j] = nullptr;
            }else if(isupper(input)){
                if(input == 'K'){
                    WKing = Piece::CreateUniqueKing(this, i * 8 + j, input);
                    board[i * 8 + j] = WKing.get();
                }else{
                    WPieces[numW] = Piece::CreateUniquePiece(this, i * 8 + j, input);
                    board[i * 8 + j] = WPieces[numW].get();
                    numW++;
                }
            }else{
                if(input == 'k'){
                    BKing = Piece::CreateUniqueKing(this, i * 8 + j, input);
                    board[i * 8 + j] = BKing.get();
                }else{
                    BPieces[numB] = Piece::CreateUniquePiece(this, i * 8 + j, input);
                    board[i * 8 + j] = BPieces[numB].get();
                    numB++;
                }
            }
        }
    }
    s >> input;
    if(input == 'b'){
        whiteTurn = !whiteTurn;
    }
    int k = 0;
    while(s >> input && k < 4){
        if(input == 'K'){
            WKcastle = true;
        }else if(input == 'Q'){
            WQcastle = true;
        }else if(input == 'k'){
            BKcastle = true;
        }else if(input == 'q'){
            BQcastle = true;
        }
        k++;
    }
    
    updateAttacks();
    initialized = true;
    print();
}

bool Board::isCheck(){
    return checkCount > 0;
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
        if(move.type == capture){
            move.print();
            print();
        }
        numPos += perft(depth - 1);
        unmakeMove();
    }
    // cout << "checks: " << checkNum << endl;
    return numPos;
}

void Board::perftBranches(int depth){
    std::vector<Move> moves;
    int numPos = 0;
    int perftTotal = 0;
    generateMoves(moves);
    for(auto move : moves){
        move.print();
        makeMove(move);
        numPos = perft(depth - 1);
        perftTotal += numPos;
        unmakeMove();
        cout << "count: " << numPos << endl;
    }
    cout << "Total: " << perftTotal << endl;
}

void Board::print() {
    cout << endl;
    for(int i = 7; i >= 0; i--){
        for(int j = 0; j < 8; j++){
            if(board[i * 8 + j] == nullptr){
                cout << '-';
            }else{
                cout << board[i * 8 + j]->getPiece();
            }
        }
        cout << endl;
    }
    cout << endl;
}

void Board::printAttacks() {
    cout << endl;
    for(int i = 7; i >= 0; i--){
        for(int j = 0; j < 8; j++){
            cout << static_cast<int>(attacks[i * 8 + j]);
        }
        cout << endl;
    }
    cout << endl;
}

int Board::moveNum(){
    return movesPlayed.size();
}

Piece* Board::pieceAt(int num){
    return board[num];
}


