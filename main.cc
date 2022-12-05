
#include <iostream>

#include "Board.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Piece.h"
#include "Queen.h"
#include "Rook.h"
#include "SlidingPieces.h"

int main(){

    int perftNum = 0;

    Board board;

    board.importFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R");

    perftNum = board.perft(1);

    std::cout << "Nodes: " << perftNum << std::endl;

    return 0;
}
