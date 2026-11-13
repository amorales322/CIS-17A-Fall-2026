#include "Piece.h"

Piece *newPce(const PlyrClr pceClr, const PieceID pieceID) {
    Piece *piece = new Piece;
    if (pceClr == PlyrClr::NONE) {
        piece->empty = true;
        piece->pceClr = PlyrClr::NONE;
        piece->pieceID = PieceID::EMPTY;
        piece->fstMove = false;
        piece->inCheck = false;
    } else {
        piece->empty = false;
        piece->pceClr = pceClr;
        piece->pieceID = pieceID;
        piece->fstMove = true;
        piece->inCheck = false;
    }

    return piece;
}

Piece *newPce(fstream &file) {
    Piece *piece = new Piece;
    file.read(reinterpret_cast<char *>(piece), sizeof(Piece));
    return piece;
}

void toFile(fstream &gmeFile, Piece *piece) {
    gmeFile.write(reinterpret_cast<char *>(piece), sizeof(Piece));
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
    if (piece != nullptr)
        delete piece;
    piece = nullptr;
}

void drwKing(const bool light, const size_t row, const PlyrClr &player) {
    switch (row) {
        case 0:
            drClmRw(".::.", light);
            break;
        case 1:
            drClmRw("_::_", light);
            break;
        case 2:
            drClmRw("/", "\\", 4, light, '_');
            break;
        case 3:
            drClmRw("\\", "/", 6, light, player);
            break;
        case 4:
            drClmRw("\\", "/", 4, light, player, '_');
            break;
        case 5:
            drClmRw("(", ")", 4, light, '_');
            break;
        case 6:
            drClmRw("|", "|", 2, light, player);
            break;
        case 7:
            drClmRw("(", ")", 2, light, player, '_');
            break;
        case 8:
            drClmRw("/", "\\", 4, light, player);
            break;
        case 9:
            drClmRw("(", ")", 6, light, player, '_');
            break;
        case 10:
            drClmRw("(", ")", 8, light, player, '_');
            break;
        case 11:
            drClmRw("/", "\\", 8, light, player, '_');
            break;
        default:
            drwBlRw(light);
    }
}

void drwQuen(const bool light, const size_t row, const PlyrClr &player) {
    switch (row) {
        case 1:
            drClmRw("_()_", light);
            break;
        case 2:
            drClmRw("_/____\\_", light);
            break;
        case 3:
            drClmRw("\\", "/", 6, light, player);
            break;
        case 4:
            drClmRw("\\", "/", 4, light, player, '_');
            break;
        case 5:
            drClmRw("(", ")", 4, light, '_');
            break;
        case 6:
            drClmRw("|", "|", 2, light, player);
            break;
        case 7:
            drClmRw("(", ")", 2, light, player, '_');
            break;
        case 8:
            drClmRw("/", "\\", 4, light, player);
            break;
        case 9:
            drClmRw("(", ")", 6, light, player, '_');
            break;
        case 10:
            drClmRw("(", ")", 8, light, player, '_');
            break;
        case 11:
            drClmRw("/", "\\", 6, light, player, '_');
            break;
        default:
            drwBlRw(light);
    }
}

void drwRook(const bool light, const size_t row, const PlyrClr &player) {
    switch (row) {
        case 3:
            drClmRw("_  _  _", light);
            break;
        case 4: //
            drClmRw(player == PlyrClr::WHITE ? "|#||#||#|" : "| || || |", light);
            break;
        case 5:
            drClmRw("|", "|", 7, light, player, '_');
            break;
        case 6:
            drClmRw(player == PlyrClr::WHITE ? "\\## " : "\\__ ", " /", 3, light, player, '_');
            break;
        case 7:
        case 9:
            drClmRw("|", player == PlyrClr::WHITE ? "|#|" : "| |", 3, light, player, '_');
            break;
        case 8:
            drClmRw(player == PlyrClr::WHITE ? "|#|" : "| |", "|", 3, light, player, '_');
            break;
        case 10: //
            drClmRw("(", ")", 7, light, player, '_');
            break;
        case 11: //
            drClmRw("/", "\\", 7, light, player, '_');
            break;
        default:
            drwBlRw(light);
    }
}

void drwBshp(const bool light, const size_t row, const PlyrClr &player) {
    switch (row) {
        case 2:
            drClmRw("_O", light);
            break;
        case 3:
            drClmRw("/", "//\\", 1, light, player);
            break;
        case 4:
            drClmRw("{", "}", 5, light, player, '_');
            break;
        case 5:
            drClmRw("\\", "/", 3, light, '_');
            break;
        case 6:
            drClmRw("(", ")", 3, light, player, '_');
            break;
        case 7:
            drClmRw("|", "|", 1, light, player);
            break;
        case 8:
            drClmRw("/", "\\", 3, light, player);
            break;
        case 9:
            drClmRw("(", ")", 5, light, player, '_');
            break;
        case 10:
            drClmRw("(", ")", 7, light, player, '_');
            break;
        case 11:
            drClmRw("/", "\\", 7, light, player, '_');
            break;
        default:
            drwBlRw(light);
    }
}

void drwKnit(const bool light, const size_t row, const PlyrClr &player) {
    switch (row) {
        case 3:
            drClmRw("^^__", light);
            break;
        case 4:
            drClmRw(" /", " _ \\_", 1, light, player);
            break;
        case 5: //
            drClmRw("<|", "__<", 4, light, player);
            break;
        case 6:
            drClmRw("<|", "\\  ", 4, light, player);
            break;
        case 7:
            drClmRw("<|", "\\ ", 5, light, player);
            break;
        case 8:
            drClmRw("<|", "\\ ", 6, light, player);
            break;
        case 9:
            drClmRw("_|", "|_", 4, light, player, '_');
            break;
        case 10:
            drClmRw("(", ")", 8, light, player, '_');
            break;
        case 11:
            drClmRw("/", "\\", 8, light, player, '_');
            break;
        default:
            drwBlRw(light);
    }
}

void drwPawn(const bool light, const size_t row, const PlyrClr &player) {
    switch (row) {
        case 6:
            drClmRw("_", light);
            break;
        case 7:
            drClmRw("(", ")", 1, light, player, '_');
            break;
        case 8:
            drClmRw("(", ")", 3, light, player, '_');
            break;
        case 9:
            drClmRw("_|", "|_", 1, light, player, '_');
            break;
        case 10:
            drClmRw("(", ")", 5, light, player, '_');
            break;
        case 11:
            drClmRw("/", "\\", 5, light, player, '_');
            break;
        default:
            drwBlRw(light);
    }
}
