
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

extern int captureCount;
extern int EPcount;
extern int castlingCount;

using namespace std;

int main(){


    Board board;

    board.importFEN("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ");

    // std::cout << "in check? " << board.isCheck() << std::endl;

    board.perftBranches(1);

    // int perftnum = board.perft(1);

    // cout << "Actual Total:  " << perftnum << endl;

    cout << "Captures: " << captureCount << endl;

    cout << "castlingCount: " << castlingCount << endl;

    cout << "EPs: " << EPcount << endl;


    return 0;
}
