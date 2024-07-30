#include "Board.h"
#include <sstream>
#include <cctype>
#include <string>
#include <iostream>
#include <algorithm>

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
                WPieces[i]->getMoves(moves);
                
            }
        }
        WKing->getMoves(moves);
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
    

    board[move.end] = board[move.start];
    board[move.start] = nullptr;
    // cout << "set Pos (line 102)" << endl;
    board[move.end]->setPos(move.end);
    // cout << "Pos setted (line 102)" << endl;
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
        board[move.start + 1] = board[move.start + 3];
        board[move.start + 1]->setPos(move.start + 1);
        board[move.start + 3] = nullptr;
    }else if(move.type == Qcastling){
        castlingCount++;
        board[move.start - 1] = board[move.start - 4];
        board[move.start - 1]->setPos(move.start - 1);
        board[move.start - 4] = nullptr;
    }else if(move.type == enPassant){
        EPcount++;
        captureCount++;
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
        if(move.captured != nullptr){
            captureCount++;
            move.captured->setCapture(true);
        }
    }
    movesPlayed.push_back(move);
    
    whiteTurn = !whiteTurn;
    updateAttacks();
}

void Board::unmakeMove(){
    Move move = movesPlayed.back();
    enPassantSquare = -1;
    movesPlayed.pop_back();

    // checking castling rights...
    if(!whiteTurn){
        for(int i : {0, 4, 7}){
            if(move.start == i){
                if(i == 0){
                    WQcastle = true;
                }else if(i == 4){
                    WQcastle = true;
                    WKcastle = true;
                }else{
                    WKcastle = true;
                }
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

                if(i == 56){
                    BQcastle = true;
                }else if(i == 60){
                    BQcastle = true;
                    BKcastle = true;
                }else{
                    BKcastle = true;
                }

                for(auto p : movesPlayed){
                    if(p.start == i || p.end == i){
                        if(i == 56){
                            BQcastle = false;
                        }else if(i == 60){
                            BQcastle = false;
                            BKcastle = false;
                        }else{
                            BKcastle = false;
                        }
                        
                        break;
                    }
                }
            }
        }
    }
    
    board[move.start] = board[move.end];
    // cout << "set Pos (line 208)" << endl;
    board[move.start]->setPos(move.start);
    // cout << "Pos Setted (line 208)" << endl;
    if(move.type == regular || move.type == pawnDouble){
        board[move.end] = nullptr;
    }else if(move.type == capture){
        board[move.end] = move.captured;
        move.captured->setCapture(false);
    }else if(move.type == Kcastling){
        board[move.start + 3] = board[move.start + 1];
        board[move.start + 3]->setPos(move.start + 3);
        board[move.start + 1] = nullptr;
        board[move.end] = nullptr;
    }else if(move.type == Qcastling){
        board[move.start - 4] = board[move.start - 1];
        board[move.start - 4]->setPos(move.start - 4);
        board[move.start - 1] = nullptr;
        board[move.end] = nullptr;
    }else if(move.type == enPassant){
        board[move.end] = nullptr;
        board[move.captured->getPos()] = move.captured;
        move.captured->setCapture(false);
    }else if(move.type == promotion){
        board[move.end] = move.captured;
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
        if(move.captured != nullptr){
            board[move.end] = move.captured;
            move.captured->setCapture(false);
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
            s >> input;
            if(input == '/'){
                s >> input;
            }
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
        cout << i + 1 << " ";
        for(int j = 0; j < 8; j++){
            if(board[i * 8 + j] == nullptr){
                cout << '-';
            }else{
                cout << board[i * 8 + j]->getPiece();
            }
        }
        cout << endl;
    }
    char out;
    cout << "  " << endl;
    for(int j = 0; j < 8; j++){
        out = j + 'a' - 1;
        cout << out;
    }
    cout << endl;

    if(isCheck()){
        if(whiteTurn){
            cout << "White is in check" << endl;
        }else{
            cout << "Black is in check" << endl;
        }
    }
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

string Board::exportFEN(){
    int skip = 0;
    string out = "";
    for(int i = 7; i >= 0; i--){
        for(int j = 0; j < 8; j++){
            if(board[i * 8 + j] == nullptr){
                skip++;
            }else{
                if(skip > 0){
                    out = out + to_string(skip);
                    skip = 0;
                }
                out = out + board[i * 8 + j]->getPiece();
            }
        }
        if(skip > 0){
            out = out + to_string(skip);
            skip = 0;
        }
        out = out + '/';
    }
    if(whiteTurn){
        out = out + " w ";
    }else{
        out = out + " b ";
    }

    if(WKcastle){
        out = out + 'K';
    }
    if(WQcastle){
        out = out + 'Q';
    }
    if(BKcastle){
        out = out + 'k';
    }
    if(BQcastle){
        out = out + 'q';
    }

    return out;
}

bool Board::getTurn(){
    return whiteTurn;
}

bool Board::checkBoard(){
    bool out;
    if(WKing.get() == nullptr || BKing.get()){
        return false;
    }
    updateAttacks();
    out = !isCheck();
    whiteTurn = !whiteTurn;
    updateAttacks();
    out = out && !isCheck();
    return out;
}



void Board::setup(){
    if(initialized){
        cout << "Board already initialized, sorry!" << endl;
        return;
    }
    string input;
    string word;
    char piece;
    bool valid = true;
    int pos;
    
    do{
        getline(cin, input);
        if(input == "done"){
            for(int i = 0; i < 8; i++){
                if(board[i] != nullptr && (board[i]->getPiece() == 'p' || board[i]->getPiece() == 'P')){
                    valid = false;
                    cout << "No pawns on first or last row!" << endl;
                    break;
                }
            }
            for(int i = 56; i < 64; i++){
                if(board[i] != nullptr && (board[i]->getPiece() == 'p' || board[i]->getPiece() == 'P')){
                    valid = false;
                    cout << "No pawns on first or last row!" << endl;
                    break;
                }
            }
            if(valid){
                valid = checkBoard();
            }
            if(valid){
                cout << "setup complete!" << endl;
                initialized = true;
                whiteTurn = true;
                attackingPiece = -1;
                enPassantSquare = -1;

                break;
            }else{
                cout << "Please enter valid board" << endl;
            }

        }
        stringstream s{input};
        if(s >> word){
            if(word == "+"){
                s >> piece;
                s >> word;
                pos = coordinateToInt(word);
                if(board[pos] != nullptr){
                    cout << "There is already a piece here!" << endl;
                }else{

                    if(isupper(piece)){
                if(piece == 'K'){
                    WKing = Piece::CreateUniqueKing(this, pos, piece);
                    board[pos] = WKing.get();
                }else{
                    WPieces[numW] = Piece::CreateUniquePiece(this, pos, piece);
                    board[pos] = WPieces[numW].get();
                    numW++;
                }
                }else{
                if(piece == 'k'){
                    BKing = Piece::CreateUniqueKing(this, pos, piece);
                    board[pos] = BKing.get();
                }else{
                    BPieces[numB] = Piece::CreateUniquePiece(this, pos, piece);
                    board[pos] = BPieces[numB].get();
                    numB++;
                }
                }
                }

            }else if(word == "-"){
                s >> word;
                pos = coordinateToInt(word);
                if(board[pos]->getTeam()){
                    if(board[pos]->getPiece() == 'K'){
                        WKing.reset();
                    }else{
                        for(int i = 0; i < numW; i++){
                            if(board[pos] == WPieces[i].get()){
                                WPieces[i].reset();
                                swap(WPieces[i], WPieces[numW - 1]);
                                break;
                            }
                        }
                    }
                }else{
                    if(board[pos]->getPiece() == 'k'){
                        BKing.reset();
                    }else{
                        for(int i = 0; i < numB; i++){
                            if(board[pos] == BPieces[i].get()){
                                BPieces[i].reset();
                                swap(BPieces[i], BPieces[numW - 1]);
                                break;
                            }
                        }
                    }
                }
                board[pos] = nullptr;

            }else if(word == "="){
                s >> word;
                if(word == "white" || word == "White" ){
                    whiteTurn = true;
                }else{
                    whiteTurn = false;
                }
            }
        }
        print();

    }while(true);
}

attackType Board::getAttack(int in){
    return attacks[in];
}

