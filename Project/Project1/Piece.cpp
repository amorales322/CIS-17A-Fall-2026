#include "Piece.h"

Piece *newPce(const PieceID pieceID, const bool isWhite) {
    Piece *piece = new Piece;
    piece->empty = false;
    piece->isWhite = isWhite;
    piece->pieceID = pieceID;
    piece->fstMove = true;
    piece->enPasnt = false;
    piece->inCheck = false;

    return piece;
}



void mvePce(const Piece *a, const Piece *b) {
    const Piece *tmp{a};
    a = b;
    b = tmp;
}

void pmtePce(Piece * const piece) {
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
        piece->pieceID = QUEEN;
    else if (usrChce == "Rook")
        piece->pieceID = ROOK;
    else if (usrChce == "Knight")
        piece->pieceID = KNIGHT;
    else if (usrChce == "Bishop")
        piece->pieceID = BISHOP;
}

void dealloc(Piece *piece) {
    if (piece->vldMove != nullptr)
        dealloc(piece->vldMove);
    if (piece->capPth != nullptr)
        dealloc(piece->capPth);
    delete piece;
}
