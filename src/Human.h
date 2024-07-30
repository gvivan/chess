#ifndef HUMAN_H
#define HUMAN_H

#include "Move.h"
#include "Player.h"
class Game;

class Human : public Player {
    virtual Move getMove();
    public:
    Human(Game* owner, bool team): Player{owner, team} {};
};

#endif
