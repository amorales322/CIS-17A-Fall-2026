#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include "Player.h"
#include "PlyrClr.h"
#include "fileUtil.h"

#include <fstream>
using namespace std;


struct Board {
    const unsigned char VERTSZE{10};
    const unsigned char HORZNSZ{10};
    bool wFstMve;
    bool bFstMve;
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

Board *newBord(fstream &, fstream &, fstream &, bool);

void toFile(fstream &, fstream &, fstream &, Board *);

void rstBrd(Board *);

void alocPce(Board *);

bool deadPos(const Board *);

void drawBrd(const Board *);

void dealloc(Board *);

void dealloc(Piece ***, size_t, size_t);

Coord *getInpt();

bool getOpt();

Piece *getPce(const Board *, const Coord *);

Piece *getPce(const Board *, size_t, size_t);

void mvePce(Board *, const Coord *, const Coord *);

const char *getName(const Board *, const Coord *, bool = false);

const char *getName(const Board *, size_t, size_t, bool = false);

bool isOOB(const Coord *);

bool isOOB(size_t, size_t);

void clrScrn();

#endif
