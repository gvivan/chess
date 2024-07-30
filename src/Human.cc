#include "Human.h"
#include <iostream>
#include <sstream>
#include <string>
#include "Move.h"
#include "Player.h"

using namespace std;

Move Human::getMove(){
    Move move;
    move.captured = nullptr;
    move.type = undef;
    string input;
    string word = "";
    bool success;

    do{
        success = false;
        getline(cin, input);
        stringstream s{input};
        s >> word;
        if(word == "resign"){
            return endGame();
        }
        if(word == "undo"){
            move.start = -10;
            move.end = -10;
            move.promotionPiece = '*';
            return move;

        }else if(word != "move"){
            cout << "Please input a move" << endl;
            continue;
        }
        s >> word;
        if(word.length() != 2){
            cout << "Please input a move" << endl;
            continue;
        }else{
            move.start = coordinateToInt(word);
        }
        word = "";
        s >> word;
        if(word.length() != 2){
            cout << "Please input a move" << endl;
            continue;
        }else{
            move.end = coordinateToInt(word);
        }
        if(s >> word){
            move.promotionPiece = word[0];
        }else{
            move.promotionPiece = '*';
        }
        success = true;

    }while(!success);
    return move;
}
