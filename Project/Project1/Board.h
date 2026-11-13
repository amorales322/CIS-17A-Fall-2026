/*
* File:   Board.h
 * Author: Anthony Morales
 * Created on October 24, 2026, 1:54 PM
 * Purpose:  Project 1 - Chess
 */

#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include "Player.h"
#include "PlyrClr.h"

struct Board {
    const unsigned char VERTSZE{10};
    const unsigned char HORZNSZ{10};
    PlyrClr whoTurn;
    PlyrClr check;
    PlyrClr chkmte;
    PlyrClr surndr;
    PlyrClr exitGme;

    bool stlemte;
    bool deadPos;

    // Two-dimensional array of pointers to piece structures (heap-allocated/dynamic)
    Piece ***board;

    Player *white;
    Coord *wKngPos;
    Player *black;
    Coord *bKngPos;
};

/*
 * Allocators
 */
Board *newBord(fstream &, bool);

void rstBrd(Board *);

void alocPce(Board *);

// File Writer
void toFile(fstream &, fstream &, fstream &, Board *);


/*
 * Printing
 */
void drawBrd(const Board *);

void clrScrn();

/*
 * Move validation functions
 */
bool isOOB(const Coord *);
bool isOOB(size_t, size_t);

/*
 * Deallocators
 */
void dealloc(Board *);

void dealloc(Piece ***, size_t, size_t);

/*
 * Input Functions
 */
Coord *getInpt();

bool getOpt();


/*
 * Utility Functions
 */
Piece *getPce(const Board *, const Coord *);

Piece *getPce(const Board *, size_t, size_t);

void mvePce(Board *, const Coord *, const Coord *);

// Checks the board for a dead position, which means that it is impossible for a check, checkmate, or stalemate to occur
bool deadPos(const Board *);

// Returns the name of a piece
const char *getName(const Board *, const Coord *, bool = false);
const char *getName(const Board *, size_t, size_t, bool = false);

#endif
