#ifndef PIECE_H
#define PIECE_H

#include "Array.h"
#include "PieceID.h"
#include "PlyrClr.h"


// enum class PieceID : unsigned char { EMPTY, KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };

#include <iostream>
#include <cstring>

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


/*
 * Piece Drawing Functions
 */
size_t clcLftW(size_t);
size_t clcRgtW(size_t);

string getBlnk(size_t, bool);
string getBlnk(size_t, char);

void drwBlRw(bool);

void drClmRw(const char *, bool);
void drClmRw(const char *, const char *, size_t, bool, char);
void drClmRw(const char *, const char *, size_t, bool, const PlyrClr &);
void drClmRw(const char *, const char *, size_t, bool, const PlyrClr &, char);

void drwKing(bool, size_t, const PlyrClr &);
void drwQuen(bool, size_t, const PlyrClr &);
void drwRook(bool, size_t, const PlyrClr &);
void drwBshp(bool, size_t, const PlyrClr &);
void drwKnit(bool, size_t, const PlyrClr &);
void drwPawn(bool, size_t, const PlyrClr &);

#endif
