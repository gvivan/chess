#ifndef COMPUTER_H
#define COMPUTER_H

#include "Move.h"
#include "Player.h"

class Game;
class Board;

class Computer : public Player {
    Board* const board;
    int level;
    public:
    virtual Move getMove();
    Computer(Game* owner, bool team, Board* board, int level): Player{owner, team}, board{board}, level{level} {};
};

#endif
