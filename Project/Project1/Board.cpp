#include "Board.h"

Board *newBord(fstream &gmeFile, fstream &plyr1, fstream &plyr2, bool frmFile) {
    gmeFile.seekg(0, ios::beg);
    Board *board = new Board;
    cin.ignore();
    board->white = newPlyr(plyr1, frmFile);
    board->black = newPlyr(plyr2, frmFile);

    if (frmFile) {
        read(gmeFile, board->wFstMve);
        read(gmeFile, board->bFstMve);
        read(gmeFile, board->whoTurn);
        read(gmeFile, board->check);
        read(gmeFile, board->chkmte);
        read(gmeFile, board->stlemte);
        read(gmeFile, board->surndr);
        read(gmeFile, board->deadPos);
        read(gmeFile, board->exitGme);
        board->board = new Piece **[board->VERTSZE];
        for (int row{0}; row < board->VERTSZE; row++) {
            board->board[row] = new Piece *[board->HORZNSZ];
            for (int col{0}; col < board->HORZNSZ; col++) {
                board->board[row][col] = newPce(gmeFile);
            }
        }
        board->wKngPos = newCord(gmeFile);
        board->bKngPos = newCord(gmeFile);
    } else {
        alocPce(board);
        board->wFstMve = true;
        board->bFstMve = true;
        board->whoTurn = PlyrClr::WHITE;
        board->check = PlyrClr::NONE;
        board->chkmte = PlyrClr::NONE;
        board->surndr = PlyrClr::NONE;
        board->exitGme = PlyrClr::NONE;
        board->stlemte = false;
        board->deadPos = false;
        board->wKngPos = newCord(8, 5);
        board->bKngPos = newCord(1, 5);
    }


    return board;
}

void toFile(fstream &gmeFile, fstream &plyr1, fstream &plyr2, Board *const board) {
    // Save Player Data
    toFile(plyr1, board->white);
    toFile(plyr2, board->black);

    // Save Game Data
    gmeFile.seekp(0, ios::beg);
    write(gmeFile, board->wFstMve);
    write(gmeFile, board->bFstMve);
    write(gmeFile, board->whoTurn);
    write(gmeFile, board->check);
    write(gmeFile, board->chkmte);
    write(gmeFile, board->surndr);
    write(gmeFile, board->stlemte);
    write(gmeFile, board->deadPos);

    for (int row{0}; row < board->VERTSZE; row++)
        for (int col{0}; col < board->VERTSZE; col++)
            toFile(gmeFile, board->board[row][col]);

    toFile(gmeFile, board->wKngPos);
    toFile(gmeFile, board->bKngPos);
}

void rstBrd(Board *const board) {
    dealloc(board->wKngPos);
    dealloc(board->bKngPos);
    dealloc(board->board, board->VERTSZE, board->HORZNSZ);

    alocPce(board);
    board->wKngPos = newCord(8, 5);
    board->bKngPos = newCord(1, 5);

    board->wFstMve = true;
    board->bFstMve = true;
    board->whoTurn = PlyrClr::WHITE;
    board->check = PlyrClr::NONE;
    board->chkmte = PlyrClr::NONE;
    board->surndr = PlyrClr::NONE;
    board->exitGme = PlyrClr::NONE;
    board->stlemte = false;
    board->deadPos = false;
}

void alocPce(Board *const board) {
    board->board = new Piece **[board->VERTSZE];

    // Piece Initialization
    for (int row{0}; row < board->VERTSZE; row++) {
        board->board[row] = new Piece *[board->HORZNSZ];
        for (int col{0}; col < board->HORZNSZ; col++)
            board->board[row][col] = nullptr;
    }

    /*
     *  Pawn Initialization
     */
    for (int col{1}; col < 9; col++) {
        board->board[2][col] = newPce(PlyrClr::BLACK, PieceID::PAWN);
        board->board[7][col] = newPce(PlyrClr::WHITE, PieceID::PAWN);
    }

    /*
    *  King Initialization
    */
    board->board[1][5] = newPce(PlyrClr::BLACK, PieceID::KING);
    board->board[8][5] = newPce(PlyrClr::WHITE, PieceID::KING);

    /*
    *  Queen Initialization
    */
    board->board[1][4] = newPce(PlyrClr::BLACK, PieceID::QUEEN);
    board->board[8][4] = newPce(PlyrClr::WHITE, PieceID::QUEEN);

    /*
    *  Rook Initialization
    */
    board->board[1][1] = newPce(PlyrClr::BLACK, PieceID::ROOK);
    board->board[1][8] = newPce(PlyrClr::BLACK, PieceID::ROOK);

    board->board[8][1] = newPce(PlyrClr::WHITE, PieceID::ROOK);
    board->board[8][8] = newPce(PlyrClr::WHITE, PieceID::ROOK);

    /*
    *  Bishop Initialization
    */
    board->board[1][3] = newPce(PlyrClr::BLACK, PieceID::BISHOP);
    board->board[1][6] = newPce(PlyrClr::BLACK, PieceID::BISHOP);

    board->board[8][3] = newPce(PlyrClr::WHITE, PieceID::BISHOP);
    board->board[8][6] = newPce(PlyrClr::WHITE, PieceID::BISHOP);


    /*
    *  Knight Initialization
    */
    board->board[1][2] = newPce(PlyrClr::BLACK, PieceID::KNIGHT);
    board->board[1][7] = newPce(PlyrClr::BLACK, PieceID::KNIGHT);

    board->board[8][2] = newPce(PlyrClr::WHITE, PieceID::KNIGHT);
    board->board[8][7] = newPce(PlyrClr::WHITE, PieceID::KNIGHT);

    // Allocate remaining if empty
    for (int row{0}; row < board->VERTSZE; row++) {
        for (int col{0}; col < board->HORZNSZ; col++)
            if (board->board[row][col] == nullptr)
                board->board[row][col] = newPce();
    }
}

bool deadPos(const Board *const board) {
    // Condition 1: Checks if only kings remain
    for (int row{1}; row < board->VERTSZE - 1; row++) {
        for (int col{1}; col < board->HORZNSZ - 1; col++)
            if (getPce(board, row, col)->pieceID != PieceID::KING)
                return false;
    }

    // Todo: King + Bishop vs King
    // Todo: King + Knight vs King
    // Todo: King + Bishop vs King + Bishop
    // Todo: King + Knight vs King + Knight
    return true;
}

void drawBrd(const Board *const board) {
    static const size_t width{23};
    Piece *curPce;
    bool lghtCel;


    cout << "\n\n" << board->black->name << "\n\n";
    for (int cellRow{3}; cellRow < 9; cellRow++) {
        for (int col{0}; col < board->HORZNSZ - 1; col++) {
            switch (col) {
                case 1:
                    drawA(cellRow);
                    break;
                case 2:
                    drawB(cellRow);
                    break;
                case 3:
                    drawC(cellRow);
                    break;
                case 4:
                    drawD(cellRow);
                    break;
                case 5:
                    drawE(cellRow);
                    break;
                case 6:
                    drawF(cellRow);
                    break;
                case 7:
                    drawG(cellRow);
                    break;
                case 8:
                    drawH(cellRow);
                    break;
                default:
                    cout << getBlnk(24, false);
            }
        }
        cout << "\n";
    }

    for (int row{1}; row < board->VERTSZE - 1; row++) {
        // Draw top of cell
        cout << getBlnk(24, false);
        for (int col{1}; col < board->HORZNSZ - 1; col++)
            cout << '+' << string(width, '-');
        cout << "+\n";
        for (int cellRow{0}; cellRow < 11; cellRow++) {
            for (int col{0}; col < board->HORZNSZ - 1; col++) {
                if (col == 0) {
                    switch (row) {
                        case 1:
                            draw1(cellRow);
                            break;
                        case 2:
                            draw2(cellRow);
                            break;
                        case 3:
                            draw3(cellRow);
                            break;
                        case 4:
                            draw4(cellRow);
                            break;
                        case 5:
                            draw5(cellRow);
                            break;
                        case 6:
                            draw6(cellRow);
                            break;
                        case 7:
                            draw7(cellRow);
                            break;
                        case 8:
                            draw8(cellRow);
                            break;
                        default:
                            cout << getBlnk(24, false);
                    }
                } else {
                    curPce = getPce(board, row, col);
                    lghtCel = (col + row - 1) % 2 != 0;
                    if (!curPce->empty) {
                        switch (curPce->pieceID) {
                            case PieceID::KING:
                                drwKing(lghtCel, cellRow, curPce->pceClr);
                                break;
                            case PieceID::QUEEN:
                                drwQuen(lghtCel, cellRow, curPce->pceClr);
                                break;
                            case PieceID::ROOK:
                                drwRook(lghtCel, cellRow, curPce->pceClr);
                                break;
                            case PieceID::BISHOP:
                                drwBshp(lghtCel, cellRow, curPce->pceClr);
                                break;
                            case PieceID::KNIGHT:
                                drwKnit(lghtCel, cellRow, curPce->pceClr);
                                break;
                            case PieceID::PAWN:
                                drwPawn(lghtCel, cellRow, curPce->pceClr);
                                break;
                            default:
                                drwBlRw(lghtCel);
                        }
                    } else
                        drwBlRw(lghtCel);
                }
            }
            cout << "|\n";
        }
    }
    // Draw bottom of board
    cout << getBlnk(24, false);
    for (int col{1}; col < board->HORZNSZ - 1; col++)
        cout << '+' << string(width, '-');
    cout << "+\n\n" << board->white->name << "\n\n";
}

void dealloc(Board *board) {
    dealloc(board->board, board->VERTSZE, board->HORZNSZ);

    delete board->wKngPos;
    delete board->bKngPos;
    dealloc(board->white);
    dealloc(board->black);

    delete board;
    board = nullptr;
}

void dealloc(Piece ***pceArry, const size_t vertSze, const size_t horzSze) {
    if (pceArry != nullptr) {
        for (size_t row{0}; row < vertSze; row++) {
            for (size_t col{0}; col < horzSze; col++)
                dealloc(pceArry[row][col]);
            delete []pceArry[row];
        }
        delete []pceArry;
        pceArry = nullptr;
    }
}

Coord *getInpt() {
    string input{};
    cin >> input;

    if (input == "-1")
        return newCord(-1, -1);
    if (input == "-2")
        return newCord(-2, -2);
    if (input.length() == 2 && toupper(input[0]) <= 'H' && toupper(input[0]) >= 'A' && input[1] <= '8' && input[1] >= '1')
        return fmChsNt(input);

    cout << "Invalid board coordinate. Enter new board coordinate: ";
    return getInpt();
}

bool getOpt() {
    char opt;
    cin >> opt;
    opt = static_cast<char>(toupper(opt));
    if (opt == 'Y' || opt == 'N')
        return opt == 'Y';

    cout << "Invalid option, enter new option: ";
    return getOpt();
}

Piece *getPce(const Board *const board, const Coord *const coord) {
    return board->board[coord->row][coord->col];
}

void mvePce(Board *const board, const Coord *const a, const Coord *const b) {
    Piece *pceA{getPce(board, a)};
    Piece *pceB{getPce(board, b)};
    Piece *tmp{pceA};

    if (!getPce(board, b)->empty) {
        if (pceA->pceClr == PlyrClr::WHITE)
            cout << board->white->name << " has captured " << board->black->name << "'s " << getName(board, b) << "!\n";
        else
            cout << board->black->name << " has captured " << board->white->name << "'s " << getName(board, b) << "!\n";

        dealloc(board->board[b->row][b->col]);
        board->board[b->row][b->col] = newPce();
        pceB = getPce(board, b);
    }
    board->board[a->row][a->col] = pceB;
    board->board[b->row][b->col] = tmp;
}

Piece *getPce(const Board *const board, const size_t row, const size_t col) {
    return board->board[row][col];
}

const char *getName(const Board *const board, const Coord *const coord, const bool captlze) {
    return getName(board, coord->row, coord->col, captlze);
}

const char *getName(const Board *const board, const size_t row, const size_t col, const bool captlze) {
    static const char *PCENME_U[7] = {"N/A", "King", "Queen", "Rook", "Bishop", "Knighxt", "Pawn"};
    static const char *PCENME_L[7] = {"N/A", "king", "queen", "rook", "bishop", "knight", "pawn"};
    if (captlze)
        return PCENME_U[static_cast<size_t>(board->board[row][col]->pieceID)];
    return PCENME_L[static_cast<size_t>(board->board[row][col]->pieceID)];
}

bool isOOB(const Coord *const coord) {
    return isOOB(coord->row, coord->col);
}

bool isOOB(const size_t row, const size_t col) {
    return row < 1 || row > 8 || col < 1 || col > 8;
}

void clrScrn() {
    cout << "\033[H\033[2J";
}
