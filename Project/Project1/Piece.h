/*
* File:   Piece.h
 * Author: Anthony Morales
 * Created on October 24, 2026, 1:54 PM
 * Purpose:  Project 1 - Chess
 */

#ifndef PIECE_H
#define PIECE_H

#include "PieceID.h"
#include "PlyrClr.h"

struct Piece {
    PieceID pieceID;
    bool empty;
    PlyrClr pceClr;
    bool fstMove;
    bool inCheck;
};

Piece *newPce(PlyrClr = PlyrClr::NONE, PieceID = PieceID::EMPTY);

Piece *newPce(fstream &);

void toFile(fstream &file, Piece *);

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
