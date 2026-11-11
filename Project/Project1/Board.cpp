#include "Board.h"

Board *newBord() {
    // Todo: Restore game board from file
    Board *board = new Board;
    board->board = new Piece **[board->VERTSZE];
    board->wKngPos = newCord(8, 5);
    board->bKngPos = newCord(1, 5);

    // Piece Initialization
    for (int row{0}; row < board->VERTSZE; row++) {
        board->board[row] = new Piece *[board->HORZNSZ];
        for (int col{0}; col < board->HORZNSZ; col++)
            board->board[row][col] = newPce();
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

    return board;
}

bool deadBrd(const Board *const board) {
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
    for (int row{1}; row < board->VERTSZE - 1; row++) {
        // Draw top of cell
        for (int col{1}; col < board->HORZNSZ - 1; col++)
            cout << '+' << string(width, '-');
        cout << "+\n";
        for (int cellRow{0}; cellRow < 11; cellRow++) {
            for (int col{1}; col < board->HORZNSZ - 1; col++) {
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
            cout << "|\n";
        }
    }
    // Draw bottom of board
    for (int col{1}; col < board->HORZNSZ - 1; col++)
        cout << '+' << string(width, '-');
    cout << "+\n";
}

void dealloc(Board *board) {
    for (size_t row{0}; row < board->VERTSZE; row++) {
        for (size_t col{0}; col < board->VERTSZE; col++)
            dealloc(getPce(board, row, col));
        delete []board->board[row];
    }
    delete []board->board;

    delete board->wKngPos;
    delete board->bKngPos;
    dealloc(board->white);
    dealloc(board->black);

    delete board;
}

Coord *getInpt() {
    string input{};
    cin >> input;

    if (input.length() == 2 && toupper(input[0]) <= 'H' && toupper(input[0]) >= 'A' && input[1] <= '8' && input[1] >= '1')
        return fmChsNt(input);

    cout << "Invalid board coordinate. Enter new board coordinate: ";
    return getInpt();
}

Piece *getPce(const Board *const board, const Coord *const coord) {
    return board->board[coord->row][coord->col];
}

Piece *getPce(const Board *const board, const size_t row, const size_t col) {
    return board->board[row][col];
}

const char *getName(const Board *const board, const Coord *const coord, const bool captlze) {
    static const char *PCENME_U[7] = {"N/A", "King", "Queen", "Rook", "Bishop", "Knight", "Pawn"};
    static const char *PCENME_L[7] = {"N/A", "king", "queen", "rook", "bishop", "knight", "pawn"};
    if (captlze)
        return PCENME_U[static_cast<size_t>(board->board[coord->row][coord->col]->pieceID)];
    return PCENME_L[static_cast<size_t>(board->board[coord->row][coord->col]->pieceID)];
}

const char *getName(const Board *const board, const size_t row, const size_t col, const bool captlze) {
    Coord *tgt{newCord(row, col)};
    const char *name{getName(board, tgt, captlze)};
    dealloc(tgt);
    return name;
}

bool isOOB(const Coord *const coord) {
    return coord->row < 1 || coord->row > 8 || coord->col < 1 || coord->col > 8;
}

bool isOOB(const size_t row, const size_t col) {
    return row < 1 || row > 8 || col < 1 || col > 8;
}

void clrScrn() {
    cout << "\033[H\033[2J";
}
