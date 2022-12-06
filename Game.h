#ifndef GAME_H
#define GAME_H


class Game {
private:
    Player white;
    Player black;

    Board the_board;

    void requestMove();
    void makeMove(Move move);



}
