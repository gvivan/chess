#include <iostream>
#include <string>
#include <sstream>

#include "Board.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Piece.h"
#include "Queen.h"
#include "Rook.h"
#include "SlidingPieces.h"
#include "Game.h"


using namespace std;

int main(){

    cout << "Welcome to Chess!"  << endl;
    int player1;
    int player2;
    float whitePoints;
    float blackPoints;
    string input;

    do{
    
    
    
    
    cout << "To start a game, please type \"game (human or computer[1-4]) (human or computer[1-4])\" or \"setup\"" << endl;

    cin >> input;
    cin >> input;
    if(input == "human"){
        player1 = 0;
    }else{
        player1 = input[9] - '0';
    }
    cin >> input;
    if(input == "human"){
        player2 = 0;
    }else{
        player2 = input[9] - '0';
    }

    Game game{player1, player2};

    while(!game.GameEnded){
        game.requestMove();
    }

    if(game.Winner == whiteWins){
        cout << "White wins!" << endl;
        whitePoints += 1;
    }else if(game.Winner == blackWins){
        blackPoints += 1;
        cout << "Black wins!" << endl;
    }else{
        cout << "Its a draw!" << endl;
        whitePoints += 0.5;
        blackPoints += 0.5;
    }

    cout << "continue? (y or n)" << endl;

    cin >> input;


    }while(input == "y");
    
    cout << "white points: " << whitePoints << endl;
    cout << "black points: " << blackPoints << endl;


    
}
