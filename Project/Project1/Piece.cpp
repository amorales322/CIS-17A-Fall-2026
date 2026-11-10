#include "Piece.h"

Piece *newPce(const PlyrClr pceClr, const PieceID pieceID) {
    Piece *piece = new Piece;
    if (pceClr == PlyrClr::NONE) {
        piece->empty = true;
        piece->pceClr = PlyrClr::NONE;
        piece->pieceID = PieceID::EMPTY;
        piece->fstMove = false;
        piece->enPasnt = false;
        piece->inCheck = false;
    } else {
        piece->empty = false;
        piece->pceClr = pceClr;
        piece->pieceID = pieceID;
        piece->fstMove = true;
        piece->enPasnt = false;
        piece->inCheck = false;
    }

    return piece;
}


void mvePce(const Piece *a, const Piece *b) {
    const Piece *tmp{a};
    a = b;
    b = tmp;
}

void pmtePce(Piece *const piece) {
    string usrChce;
    cout << "Your pawn is able to promote! Which piece would you like to promote it with: ";
    cout << "1. Queen\n";
    cout << "2. Rook\n";
    cout << "3. Knight\n";
    cout << "4. Bishop\n";

    cout << "Enter Option: ";
    cin >> usrChce;
    while (usrChce != "Queen" && usrChce != "Rook" && usrChce != "Knight" && usrChce != "Bishop") {
        cout << "Invalid choice, enter new choice: ";
        cin >> usrChce;
    }

    piece->enPasnt = false;
    piece->fstMove = false;
    if (usrChce == "Queen")
        piece->pieceID = PieceID::QUEEN;
    else if (usrChce == "Rook")
        piece->pieceID = PieceID::ROOK;
    else if (usrChce == "Knight")
        piece->pieceID = PieceID::KNIGHT;
    else if (usrChce == "Bishop")
        piece->pieceID = PieceID::BISHOP;
}

void dealloc(Piece *piece) {
    if (piece->vldMove != nullptr)
        dealloc(piece->vldMove);
    if (piece->capPth != nullptr)
        dealloc(piece->capPth);
    delete piece;
}
