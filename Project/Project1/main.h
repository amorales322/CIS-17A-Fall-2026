#ifndef MAIN_H
#define MAIN_H

/*
 *  Piece Enum
 */
enum PieceID { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };

/*
 *  Game Structs
 */


struct Coord {
    char row;
    char col;
};

struct Array {
    Coord **data;
    unsigned int size;
    unsigned int utilSze;
};

struct Player {
    unsigned short nWins;
    unsigned short nLoss;
    string name;
};

struct Piece {
    PieceID pieceID;
    bool empty;
    bool isWhite;
    bool fstMove;
    bool enPasnt; // For pawns if they can be captured via 'en passant'
    Array *vldMove; // Valid moves. For the king, this is any safe position it can move to.
    bool inCheck;
    Array *capPth; // Paths capture pieces has to king
};

struct Board {
    const unsigned int VERTSZE{10};
    const unsigned int HORZNSZ{10};
    // Two-dimensional array of pointers to piece structures (heap-allocated/dynamic)
    Piece ***board;

    Player *white;
    Player *black;
    unsigned char wFleLoc;
    unsigned char bFleLoc;
    bool wFstMve;
    bool bFstMve;

    bool chkmte;
    bool stlemte;
    bool deadBrd;
};


/*
 *  Calculation Functions
 */
bool deadBrd(const Board *);
bool pceIntr(const Board *, const Coord *, const Coord *, Array *);

bool sfeSpce(const Board *, const Coord *, bool, Array *);
bool sfeSpce(const Board *, const Coord *);

Array *calcPth(const Board *, const Coord *, const Coord *);
bool unObPth(const Board *, const Coord *, const Coord *);

// Move Calculation Functions
void kingMov(const Board *, bool, bool, const Coord *, Array *);
void lineMov(const Board *, bool, bool, const Coord *, Array *);
void diagMov(const Board *, bool, bool, const Coord *, Array *);
void knitMov(const Board *, bool, bool, const Coord *, Array *);
void pawnMov(const Board *, bool, bool, const Coord *, Array *);
// Target mode not needed, castling only works with kings
void castle(const Board *, const Coord *, Array *);

/*
 *  User Input & Input/Move Validation
 */
Coord *getInpt();
bool vldMove(const Coord *, const Array *);
bool vldPcMv(const Board *, const Coord *, const Coord *);

bool isOOB(const Coord *);

/*
 *  Other Game Functions
 */
void mvePce(Board *, const Coord *, const Coord *);
void pmtePce(Board *, const Coord *);

/*
 *  Screen Drawing/Clearing
 */
void drawBrd(const Board *);
void clrScrn();

/*
 *  Allocators
 */
Array *newArry(size_t);
Board *newBord();
Player *newPlyr();
Coord *newCord(unsigned char, unsigned char);

/*
 *  Array Methods
 */
// Append
void appDta(Array *, const Coord *);
void appDta(Array *, const Array *);

// Capacity Modifiers
void resize(Array *, size_t = 0);
void clear(Array *);
void shrink(Array *);

/*
 *  Deallocators
 */
void dealloc(Array *);
void dealloc(const Coord *);
void dealloc(Board *);
void dealloc(Player *);
void dealloc(Piece *);

// Miscellaneous Functions
void incCord(Coord *, const Coord *);
void incCord(Coord *, unsigned char, unsigned char);
Coord *clcCord(unsigned char, int = 0);
Coord *copyCord(const Coord *);

Coord *walkPth(const Board *, const Coord *, bool, unsigned char, unsigned char, Array *);
bool tgtChk(bool, bool, const Piece *, const Piece *);
int search(const Array *, const Coord *);

/*
 *  Comparison Functions
 */
bool lessThn(const Coord *, const Coord *);
bool lessThn(const Coord*, unsigned char, unsigned char);
bool lessEq(const Coord *, const Coord *);
bool lessEq(const Coord *, unsigned char, unsigned char);
bool isEqual(const Coord *, const Coord *);
bool isEqual(const Coord *, unsigned char, unsigned char);
#endif //MAIN_H
