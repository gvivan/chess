#include "Computer.h"
#include "Move.h"
#include "Player.h"
#include "Board.h"
#include "Game.h"

#include <vector>
#include <algorithm>
#include <random>

using namespace std;



Move Computer::getMove(){
    vector<Move> moves;
    Move move;
    board->generateMoves(moves);
    if(level == 1){
        if(moves.size() == 0){
            return endGame();
        }
        cout << moves.size() << endl;
        int index = rand() % moves.size();
        return moves[index];
    }else if(level == 2){
        for(auto a : moves){
            a.value = 0;
            if(a.type == capture){
                a.value += 2;
            }
            board->makeMove(a);
            if(board->isCheck()){
                a.value += 2;
            }
            board->unmakeMove();
        }
        sort(moves.begin(), moves.end());
        return moves.back();
    }else if(level == 3){
        for(auto a : moves){
            a.value = 0;
            if(a.type == capture){
                a.value += 2;
            }
            if(board->getAttack(a.end) == attack){
                a.value -= 1;
            }
            board->makeMove(a);
            if(board->isCheck()){
                a.value += 2;
            }
            
            board->unmakeMove();
        }
    }else{
        return endGame();
    }
    return endGame();
}
