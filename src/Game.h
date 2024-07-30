#ifndef GAME_H
#define GAME_H
#include <memory>
#include "Player.h"
#include "Move.h"
#include "Board.h"


enum winner {stalemate=0, whiteWins, blackWins};


class Game {
private:

    std::unique_ptr<Player> white;
    std::unique_ptr<Player> black;


    std::unique_ptr<Board> theBoard;

    

    // checkmove should also modify the move to match the corresponding move if found
    bool checkMove(Move& move);
    void makeMove(Move move);
    void unmakeMove();

public:
    Game(int W, int B); // 0 = human, 1, 2, 3+... computer levels
    void endGame();
    void endGame(winner state);
    // start at initial position
    void initial();
    void requestMove();

    // enter setup mode
    void setup();
    bool GameEnded;
    winner Winner; 

};

#endif
