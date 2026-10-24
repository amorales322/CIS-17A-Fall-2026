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
    const unsigned int VERTSZE{8};
    const unsigned int HORZNSZ{8};
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

Array *alloc(unsigned int);
Player *newPlyr();

void appDta(Array *, unsigned char);
void appDta(Array *, Array *, bool = true);

void resize(Array *, int = -1);

void dealloc(Array *);
void dealloc(Board *);
void dealloc(Player *);
void dealloc(Piece *);

#endif //MAIN_H
