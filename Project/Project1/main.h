#ifndef MAIN_H
#define MAIN_H

/*
 *  Piece Enum
 */
enum PieceID { KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN };

/*
 *  Game Structs
 */
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


/*
 *  Calculation Functions
 */
bool deadBrd(const Board *);
bool pceIntr(const Board *, unsigned char, unsigned char);

bool sfeSpce(const Board *, unsigned char, bool, Array *);
// This overload has interpose mode disabled and does not return an array, it only checks if the space is safe
bool sfeSpce(const Board *, unsigned char);

Array *calcPth(const Board *, unsigned char, unsigned char);
// Calculates if the path between two points is unobstructed. Must be a straight vertical, horizontal, or diagonal line
bool unObPth(const Board *, unsigned char, unsigned char);

// Move Calculation Functions
void kingMov(const Board *, bool, bool, unsigned char, Array *);
void lineMov(const Board *, bool, bool, unsigned char, Array *);
void diagMov(const Board *, bool, bool, unsigned char, Array *);
void knitMov(const Board *, bool, bool, unsigned char, Array *);
void pawnMov(const Board *, bool, bool, unsigned char, Array *);
// Target mode not needed, castling only works with kings
void castle(const Board *, unsigned char, Array *);

/*
 *  User Input & Input/Move Validation
 */
unsigned char getInpt();
bool vldMove(unsigned char, const Array *);
bool vldPcMv(const Board *, unsigned char, unsigned char);

bool isOOB(unsigned char);

/*
 *  Other Game Functions
 */
void mvePce(Board *, unsigned char, unsigned char);
void pmtePce(Board *, unsigned char);

/*
 *  Screen Drawing/Clearing
 */
void drawBrd(const Board *);
void clrScrn();

/*
 *  Allocators
 */
Array *alloc(unsigned int);
Player *newPlyr();

/*
 *  Array Methods
 */
// Append
void appDta(Array *, unsigned char);
void appDta(Array *, Array *, bool = true);

// Capacity Modifiers
void resize(Array *, int = -1);
void clear(Array *);
void shrink(Array *);

/*
 *  Deallocators
 */
void dealloc(Array *);
void dealloc(Board *);
void dealloc(Player *);
void dealloc(Piece *);

// Miscellaneous Functions
unsigned char preInc(unsigned char &, int);
unsigned char postInc(unsigned char &, int);
#endif //MAIN_H
