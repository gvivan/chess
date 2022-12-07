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
    }else{
        return moves[0];
    }
}
