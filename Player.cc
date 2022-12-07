#include "Player.h"
#include "Game.h"
#include "Move.h"

Move Player::endGame(){
    owner->endGame();
    Move move{-1, -1, -1, nullptr, undef, '*'};
    return move;
}
