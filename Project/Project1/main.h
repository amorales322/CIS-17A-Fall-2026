#ifndef MAIN_H
#define MAIN_H

#include <string>

enum PieceID { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };

struct Array {
    unsigned int size;
    unsigned int utilSze;
    unsigned char *data;
};

struct Player {
    unsigned short nWins;
    unsigned short nLoss;
    string name;
};

struct Piece {
    bool empty;
    bool isWhite;
    PieceID pieceID;
    // Used for pawns - To determine if they can move two spaces or not
    bool fstMove;
    // For pawns, if they meet the requirements to capture a piece 'En passant'
    bool enPasnt;
    // Valid moves. For the king, this is any safe position it can move to.
    Array *vldMove;

    // King Variables
    bool inCheck;
    // Paths capture pieces has to king
    Array *capPth;
};

struct Board {
    const unsigned int VERTSZE{10};
    const unsigned int HORZNSZ{10};
    Piece **board;

    Player *white;
    unsigned char wFleLoc;
    Player *black;
    unsigned char bFleLoc;

    bool wFstMve;
    bool bFstMve;

    bool chkmte;
    bool stlemte;
    bool deadBrd;
};

// Move Calculation Functions
void kingMov(const Board *, bool, unsigned char, Array *);
void lineMov(const Board *,bool, unsigned char, Array *);
void diagMov(const Board *,bool, unsigned char, Array *);
void knitMov(const Board *,bool, unsigned char, Array *);
void pawnMov(const Board *,bool, bool, bool, unsigned char, Array *);
void castle(const Board *,bool, unsigned char, Array *);

// User Input & Input Validation
unsigned char getInpt();
bool vldMove(unsigned char, const Array *);
bool isOOB(unsigned char);

// Other Functions
void mvePce(Board *, unsigned char, unsigned char);
void pmtePce(Board *, unsigned char);

// Screen Drawing/Clearing
void drawBrd(const Board *);
void clrScrn();

// Allocators
Array *alloc(unsigned int);
Player *newPlyr();

// Append Functions
void appDta(Array *, unsigned char);
void appDta(Array *, Array *, bool = true);

// Resize function
void resize(Array *, int = -1);

// Deallocators
void dealloc(Array *);
void dealloc(Board *);
void dealloc(Player *);
void dealloc(Piece *);

unsigned char postDec(unsigned char &, int);

unsigned char postInc(unsigned char &, int);
#endif //MAIN_H
