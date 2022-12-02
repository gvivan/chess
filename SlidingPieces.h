#ifndef SLIDINGPIECES_H
#define SLIDINGPIECES_H

class SlidingPieces : public Piece {
private:
    /*
    This serves to define the subset of the directions the piece can go. This requires the directions to be ordered such that
    0 - 3 is Rook and 4 - 8 is Bishop.
    */ 
    int start;
    int end;
public:
    virtual void generateAttacks();
    virtual void getMoves();
}



#endif
