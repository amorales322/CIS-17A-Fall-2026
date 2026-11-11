#ifndef PIECE_H
#define PIECE_H

#include "Array.h"
#include "PieceID.h"
#include "PlyrClr.h"
#include "ASCII.h"

#include <iostream>
#include <fstream>

using namespace std;

struct Piece {
    PieceID pieceID;
    bool empty;
    PlyrClr pceClr;
    bool fstMove;
    bool enPasnt; // For pawns if they can be captured via 'en passant'
    bool inCheck;
    // Array *vldMove; // Valid moves. For the king, this is any safe position it can move to.
    // Array *capPth; // Paths capture pieces has to king
};

Piece *newPce(PlyrClr = PlyrClr::NONE, PieceID = PieceID::EMPTY);

Piece *newPce(fstream &);

void toFile(fstream &file, Piece *);

void mvePce(const Piece *, const Piece *);

void pmtePce(Piece *);

void dealloc(Piece *);


/*
 * Piece Drawing Functions
 */

void drwKing(bool, size_t, const PlyrClr &);
void drwQuen(bool, size_t, const PlyrClr &);
void drwRook(bool, size_t, const PlyrClr &);
void drwBshp(bool, size_t, const PlyrClr &);
void drwKnit(bool, size_t, const PlyrClr &);
void drwPawn(bool, size_t, const PlyrClr &);

#endif
