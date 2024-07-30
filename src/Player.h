#ifndef PLAYER_H
#define PLAYER_H
#include "Move.h"

class Game;

class Player {
    private:
    Game* const owner;
    bool whiteTeam;
    protected:
    virtual Move endGame();
    public:
    virtual Move getMove() = 0;
    
    virtual ~Player() {};
    Player(Game* owner, bool team): owner{owner}, whiteTeam{team} {};
};

#endif
