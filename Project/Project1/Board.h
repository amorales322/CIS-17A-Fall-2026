#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include "Player.h"
#include "PlyrClr.h"

struct Board {
    const unsigned char VERTSZE{10};
    const unsigned char HORZNSZ{10};
    // Two-dimensional array of pointers to piece structures (heap-allocated/dynamic)
    Piece ***board;

    Player *white;
    Coord *wKngPos;
    Player *black;
    Coord *bKngPos;

    unsigned char wFleLoc{0};
    unsigned char bFleLoc{0};
    bool wFstMve{true};
    bool bFstMve{true};
    PlyrClr whoTurn{PlyrClr::WHITE};
    PlyrClr check{PlyrClr::NONE};
    PlyrClr chkmte{PlyrClr::NONE};

    bool stlemte{false};
    bool deadBrd{false};
};

Board *newBord();

bool deadBrd(const Board *);

void drawBrd(const Board *);

void dealloc(Board *);

Coord *getInpt();

Piece *getPce(const Board *, const Coord *);

Piece *getPce(const Board *, size_t, size_t);

const char *getName(const Board *, const Coord *, bool = false);

const char *getName(const Board *, size_t, size_t, bool = false);

bool isOOB(const Coord *);

bool isOOB(size_t, size_t);

void clrScrn();

#endif
