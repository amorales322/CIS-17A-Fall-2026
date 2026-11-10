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

    // /*
    //  *  Pawn Initialization
    //  */
    // for (int i{21}; i < 29; i++) {
    //     Coord *coord = clcCord(i);
    //     Coord *coord2 = clcCord(i, 50);
    //     newPce(board, PAWN, false, coord->row, coord->col);
    //     newPce(board, PAWN, true, coord2->row, coord2->col);
    //     dealloc(coord);
    //     dealloc(coord2);
    // }

    /*
     *  Test Piece Initialization
     */
    board->board[5][8] = newPce(PlyrClr::BLACK, PieceID::BISHOP);
    board->board[7][4] = newPce(PlyrClr::BLACK, PieceID::BISHOP);
    // board->board[7][7] = newPce(BLACK, ROOK);
    board->board[7][5] = newPce(PlyrClr::BLACK, PieceID::QUEEN);
    // board->board[7][6] = newPce(BLACK, PAWN);
    // board->board[6][7] = newPce(BLACK, PAWN);
    board->board[7][6]->fstMove = false;


    /*
    *  King Initialization
    */
    board->board[1][5] = newPce(PlyrClr::BLACK, PieceID::KING);
    board->board[8][5] = newPce(PlyrClr::WHITE, PieceID::KING);

    /*
    *  Queen Initialization
    */
    board->board[8][4] = newPce(PlyrClr::WHITE, PieceID::QUEEN);

    // /*
    // *  Rook Initialization
    // */
    // newPce(board, ROOK, false, 1, 1);
    // newPce(board, ROOK, false, 1, 8);
    // newPce(board, ROOK, true, 8, 1);
    // newPce(board, ROOK, true, 8, 8);
    //
    // /*
    // *  Bishop Initialization
    // */
    // newPce(board, BISHOP, false, 1, 3);
    // newPce(board, BISHOP, false, 1, 6);
    // newPce(board, BISHOP, true, 8, 3);
    // newPce(board, BISHOP, true, 8, 6);
    //
    // /*
    // *  Knight Initialization
    // */
    // newPce(board, KNIGHT, false, 1, 2);
    // newPce(board, KNIGHT, false, 1, 7);
    // newPce(board, KNIGHT, true, 8, 2);
    // newPce(board, KNIGHT, true, 8, 7);

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
    Piece *curPce;
    cout << "     a   b   c   d   e   f   g   h\n";
    for (int row{1}; row < board->VERTSZE - 1; row++) {
        cout << "   +---+---+---+---+---+---+---+---+\n";
        cout << " " << row << " |";
        for (int col{1}; col < board->HORZNSZ - 1; col++) {
            curPce = getPce(board, row, col);
            if (!curPce->empty) {
                cout << ' ';
                switch (curPce->pieceID) {
                    case PieceID::KING:
                        cout << (curPce->pceClr == PlyrClr::WHITE ? 'K' : 'k');
                        break;
                    case PieceID::QUEEN:
                        cout << (curPce->pceClr == PlyrClr::WHITE ? 'Q' : 'q');
                        break;
                    case PieceID::ROOK:
                        cout << (curPce->pceClr == PlyrClr::WHITE ? 'R' : 'r');
                        break;
                    case PieceID::BISHOP:
                        cout << (curPce->pceClr == PlyrClr::WHITE ? 'B' : 'b');
                        break;
                    case PieceID::KNIGHT:
                        cout << (curPce->pceClr == PlyrClr::WHITE ? 'N' : 'n');
                        break;
                    case PieceID::PAWN:
                        cout << (curPce->pceClr == PlyrClr::WHITE ? 'P' : 'p');
                        break;
                    default:
                        cout << ' ';
                }
                cout << " |";
            } else
                cout << " * |";
        }
        cout << '\n';
    }
    cout << "   +---+---+---+---+---+---+---+---+\n\n";
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
        return newCord(input[1] - 48, toupper(input[0]) - 64);

    cout << "Invalid board coordinate. Enter new board coordinate: ";
    return getInpt();
}

Piece *getPce(const Board *const board, const Coord *const coord) {
    return board->board[coord->row][coord->col];
}

Piece *getPce(const Board *const board, const size_t row, const size_t col) {
    return board->board[row][col];
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
