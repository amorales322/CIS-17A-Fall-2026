#ifndef PIECE_H
#define PIECE_H

#include "Array.h"
#include "PieceID.h"
#include "PlyrClr.h"

#include <iostream>

using namespace std;

struct Piece {
    PieceID pieceID;
    bool empty;
    PlyrClr pceClr;
    bool fstMove;
    bool enPasnt; // For pawns if they can be captured via 'en passant'
    bool inCheck;
    Array *vldMove; // Valid moves. For the king, this is any safe position it can move to.
    Array *capPth; // Paths capture pieces has to king
};

Piece *newPce(PlyrClr = PlyrClr::NONE, PieceID = PieceID::EMPTY);

void mvePce(const Piece *, const Piece *);

void pmtePce(Piece *);

void dealloc(Piece *);

#endif
