#include "Game.h"
#include <vector>
#include <iostream>
#include <memory>
#include "Player.h"
#include "Board.h"
#include "Human.h"
#include "Computer.h"

using namespace std;

Game::Game(int W, int B){
    cout << "creating game..." << endl;
    GameEnded = false;
    theBoard = make_unique<Board>();
    cout << W << endl << B << endl;
    if(W == 0){
        white = make_unique<Human>(this, true);
    }else{
        white = make_unique<Computer>(this, true, theBoard.get(), W);

        cout << "computer created!" << endl;
    }
    if(B == 0){
        black = make_unique<Human>(this, false);
    }else{
        black = make_unique<Computer>(this, false, theBoard.get(), B);
        cout << "computer created!" << endl;
    }
    string input;

    cout << "default or setup?" << endl;
    if(cin >> input){
        if(input == "default"){
            initial();
        }else{
            setup();
        }
    }
    
}

void Game::setup(){
    theBoard->setup();
}

void Game::initial(){
    theBoard->importFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
}

void Game::requestMove(){
    cout << "requesting move..." << endl;
    Move move;
    if(theBoard->getTurn()){
        cout << "hello?" << endl;
        move = white->getMove();
        cout << "hello?" << endl;
        
    }else {
        move = black->getMove();
    }
    if(move.start == -10){
        unmakeMove();
        return;
    }
    if(checkMove(move)){
        makeMove(move);
    }else{
        cout << "Please enter a valid move" << endl;
    }
}

void Game::unmakeMove(){
    if(theBoard->moveNum() >= 2){
        theBoard->unmakeMove();
        theBoard->unmakeMove();
    }else{
        cout << "There are no moves to undo" << endl;
    }
}

bool Game::checkMove(Move& move){
    vector<Move> moves;
    theBoard->generateMoves(moves);
    if(moves.empty()){
        if(theBoard->isCheck()){
            if(theBoard->getTurn()){
                endGame(blackWins);
            }else{
                endGame(whiteWins);
            }
        }else{
            endGame(stalemate);
        }
    }
    for(auto a : moves){
        if(a == move){
            move.type = a.type;
            move.captured = a.captured;
            return true;
        }
    }
    return false;
}

void Game::makeMove(Move move){
    theBoard->makeMove(move);
}

void Game::endGame(){
            if(theBoard->getTurn()){
                endGame(blackWins);
            }else{
                endGame(whiteWins);
            }
    
}

void Game::endGame(winner state){
    Winner = state;
    GameEnded = true;
}

