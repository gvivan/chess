
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

    board.importFEN("n1n5/PPPk4/8/8/8/8/4Kppp/5N1N b");


    // std::cout << "in check? " << board.isCheck() << std::endl;

    // board.perftBranches(2);

    int perftnum = board.perft(2);

    cout << "Actual Total:  " << perftnum << endl;

    cout << "Captures: " << captureCount << endl;

    cout << "castlingCount: " << castlingCount << endl;

    cout << "EPs: " << EPcount << endl;


    return 0;
}
