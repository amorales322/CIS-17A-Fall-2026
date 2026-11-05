/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 24, 2026, 1:54 PM
 * Purpose:  Project 1 - Chess
 */

// System Libraries
#include <iostream> // Input Output Library
using namespace std;

// User Libraries
#include "main.h" // Contains function prototypes - will be removed and included here for my final submission

// Global Constants not Variables
// Science, Math, Conversions, Dimensions

// Function Prototypes

// Execution begins here at main
int main(int argc, char **argv) {
    // Set random number seed

    // Declare Variables

    // Initialize Variables

    // Map/Process the Inputs -> Outputs

    // Display Inputs/Outputs

    // Clean up memory and files

    // Exit the Program
    return 0;
}

bool deadBrd(const Board *const board) {
    // This function is extendable and allows me to add more states to check for to determine a dead board

    // This condition checks for if only kings remain on the board, and returns false for the first non-king piece it finds
    for (int row{1}; row < board->VERTSZE - 1; row++) {
        for (int col{1}; col < board->HORZNSZ - 1; col++)
            if (board->board[row][col]->pieceID != KING)
                return false;
    }

    // Todo: King + Bishop vs King
    // Todo: King + Knight vs King
    // Todo: King + Bishop vs King + Bishop
    // Todo: King + Knight vs King + Knight
    return true;
}

bool pceIntr(const Board *const board, const Coord *const kingPos, const Coord *const enmyPos, Array *const data) {
    // This state can never occur, but if the function is called in this state, then the function returns false
    if (isEqual(kingPos, enmyPos))
        return false;

    // This should never occur, but if the function is called in this state, then the function returns false
    if (!unObPth(board, kingPos, enmyPos))
        return false;


    Array *path = calcPth(board, kingPos, enmyPos);
    for (int i{0}; i < path->utilSze; i++) {
        kingMov(board, true, true, path->data[i], data);
        lineMov(board, true, true, path->data[i], data);
        diagMov(board, true, true, path->data[i], data);
        knitMov(board, true, true, path->data[i], data);
        pawnMov(board, true, true, path->data[i], data);
    }

    dealloc(path);
    return data->utilSze != 0;
}

/*
 * When interpose mode is disabled, this function calculates if an enemy piece can reach the target location and returns the locations of those enemy pieces
 *
 * When interpose mode is enabled, this function calculates if any of the player's pieces can reach the target location,
 * and calculates the locations of those pieces that can reach the target location
 */
bool sfeSpce(const Board *const board, const Coord *const tgtPos, const bool iposeMde, Array *const data) {
    bool isSafe;
    kingMov(board, true, iposeMde, tgtPos, data);
    lineMov(board, true, iposeMde, tgtPos, data);
    diagMov(board, true, iposeMde, tgtPos, data);
    knitMov(board, true, iposeMde, tgtPos, data);
    pawnMov(board, true, iposeMde, tgtPos, data);

    isSafe = data->utilSze > 0;
    return isSafe;
}

// This overload has interpose mode disabled and does not return an array, it only checks if the space is safe
bool sfeSpce(const Board *const board, const Coord *const tgtPos) {
    Array *posData = newArry(20);
    bool isSafe;
    kingMov(board, true, false, tgtPos, posData);
    lineMov(board, true, false, tgtPos, posData);
    diagMov(board, true, false, tgtPos, posData);
    knitMov(board, true, false, tgtPos, posData);
    pawnMov(board, true, false, tgtPos, posData);

    isSafe = posData->utilSze > 0;
    dealloc(posData);
    return isSafe;
}

// Calculates a straight line path between two points, returns an empty array if there is no straight line path
// For a full calculated path, the bounds are exclusive
Array *calcPth(const Board *const board, const Coord *const initPos, const Coord *const tgtPos) {
    Array *path = newArry(10);

    if (initPos != tgtPos) {
        const Coord *start{lessEq(initPos, tgtPos) ? initPos : tgtPos};
        const Coord *end{lessEq(initPos, tgtPos) ? tgtPos : initPos};
        Coord *incAmt;
        Coord *current;

        if (abs(initPos->row - tgtPos->row) == abs(initPos->col - tgtPos->col))
            incAmt = lessEq(initPos, tgtPos) ? newCord(1, 1) : newCord(1, -1);
        else if (initPos->row == tgtPos->row) // Same Row - Left to Right
            incAmt = newCord(0, 1);
        else if (initPos->col == tgtPos->col) // Same Column - Top to Bottom
            incAmt = newCord(1, 0);
        if (incAmt != nullptr) {
            current = copyCord(start);
            incCord(current, incAmt);
            while (lessThn(current, end) && board->board[current->row][current->col]->empty) {
                appDta(path, current);
                incCord(current, incAmt);
            }
            dealloc(incAmt);
            dealloc(current);
        }
    }
    return path;
}

// Calculates if the path between two points is unobstructed. Must be a straight vertical, horizontal, or diagonal line
bool unObPth(const Board *const board, const Coord *const initPos, const Coord *const tgtPos) {
    if (initPos == tgtPos)
        return true;

    const Coord *start{lessEq(initPos, tgtPos) ? initPos : tgtPos};
    const Coord *end{lessEq(initPos, tgtPos) ? tgtPos : initPos};
    Array *path = calcPth(board, initPos, tgtPos);
    bool uobsPth{false};

    if (path->utilSze != 0)
        uobsPth = isEqual(path->data[0], start) && isEqual(path->data[path->utilSze - 1], end);

    dealloc(path);
    return uobsPth;
}

void kingMov(const Board *const board, const bool tgtMode, const bool intrpse, const Coord *const initPos, Array *const data) {
    static const size_t nOffset{8};
    static const char offsets[nOffset][2]{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    bool diagChk[nOffset]{};

    for (size_t i{0}; i < nOffset; i++) {
        Coord *fnlPos{copyCord(initPos)};
        incCord(fnlPos, offsets[i][0], offsets[i][1]);
        if (!isOOB(fnlPos)) {
            Piece *tgtPce{board->board[fnlPos->row][fnlPos->col]};
            if (tgtChk(tgtMode, intrpse, tgtPce, board->board[initPos->row][initPos->col])) {
                /*
                 * In Target Mode: checking if the piece at the target location can move to the initial location
                 * Interpose mode used to determine which piece color to use
                 * Ignoring king because it cannot occupy an adjacent square next to another king
                 * Ignoring knight because it cannot move to an adjacent space
                 * Pawn in checked in a separate move calculation function
                 */
                diagChk[0] = isEqual(fnlPos, initPos->row, initPos->col + 1);
                diagChk[1] = isEqual(fnlPos, initPos->row, initPos->col - 1);
                diagChk[2] = isEqual(fnlPos, initPos->row + 1, initPos->col);
                diagChk[3] = isEqual(fnlPos, initPos->row - 1, initPos->col);
                diagChk[4] = isEqual(fnlPos, initPos->row + 1, initPos->col - 1);
                diagChk[5] = isEqual(fnlPos, initPos->row - 1, initPos->col + 1);
                diagChk[6] = isEqual(fnlPos, initPos->row + 1, initPos->col + 1);
                diagChk[7] = isEqual(fnlPos, initPos->row - 1, initPos->col - 1);

                if (tgtPce->pieceID == QUEEN)
                    appDta(data, fnlPos);
                else if (tgtPce->pieceID == ROOK && (diagChk[0] || diagChk[1] || diagChk[2] || diagChk[3]))
                    appDta(data, fnlPos);
                else if (tgtPce->pieceID == BISHOP && (diagChk[4] || diagChk[5] || diagChk[6] || diagChk[7]))
                    appDta(data, fnlPos);
            } else if (vldPcMv(board, initPos, fnlPos))
                appDta(data, fnlPos);
        }
        dealloc(fnlPos);
    }
}

void lineMov(const Board *const board, const bool tgtMode, const bool intrpse, const Coord *const initPos, Array *const data) {
    static const size_t nOffset{4};
    // Order: Up, Down, Left, Right
    static const char offsets[nOffset][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (size_t i{0}; i < nOffset; i++) {
        Coord *fnlPos{walkPth(board, initPos, tgtMode, offsets[i][0], offsets[i][1], data)};
        if (!isOOB(fnlPos)) {
            Piece *tgtPce{board->board[fnlPos->row][fnlPos->col]};
            if (tgtChk(tgtMode, intrpse, tgtPce, board->board[initPos->row][initPos->col])) {
                /*
                 * In Target Mode: checking if the piece at the target location can move to the initial location
                 * Interpose mode used to determine which piece color to use
                 * Ignoring king because it cannot occupy an adjacent square next to another king
                 * Ignoring bishop and knight because it cannot move vertically or horizontally in a straight line
                 * Pawn in checked in a separate move calculation function
                 */
                if (tgtPce->pieceID == QUEEN || tgtPce->pieceID == ROOK)
                    appDta(data, fnlPos);
            } else if (vldPcMv(board, initPos, fnlPos)) {
                // Not in target mode: checking if the piece can move to the final position
                appDta(data, fnlPos);
            }
        }
        dealloc(fnlPos);
    }
}

void diagMov(const Board *const board, const bool tgtMode, const bool intrpse, const Coord *const initPos, Array *const data) {
    static const size_t nOffset{4};
    // Order: Top-Left, Top-Right, Bottom-Left, Bottom-Right
    static const char offsets[nOffset][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};


    for (size_t i{0}; i < nOffset; i++) {
        Coord *fnlPos{walkPth(board, initPos, tgtMode, offsets[i][0], offsets[i][1], data)};
        if (!isOOB(fnlPos)) {
            Piece *tgtPce{board->board[fnlPos->row][fnlPos->col]};
            if (tgtChk(tgtMode, intrpse, tgtPce, board->board[initPos->row][initPos->col])) {
                /*
                 * In Target Mode: checking if the piece at the target location can move to the initial location
                 * Interpose mode used to determine which piece color to use
                 * Ignoring king because it cannot occupy an adjacent square next to another king
                 * Ignoring rook and knight because they cannot move diagonally
                 * Pawn in checked in a separate move calculation function
                 */
                if (tgtPce->pieceID == QUEEN || tgtPce->pieceID == BISHOP)
                    appDta(data, fnlPos);
            } else if (vldPcMv(board, initPos, fnlPos)) {
                // Not in target mode: checking if the piece can move to the final position
                appDta(data, fnlPos);
            }
        }
        dealloc(fnlPos);
    }
}


void knitMov(const Board *const board, const bool tgtMode, const bool intrpse, const Coord *const initPos, Array *const data) {
    static const size_t nOffset{8};
    // Order: Top-Left (clockwise)
    static const char offsets[nOffset][2]{{-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}};
    for (int i{0}; i < 8; i++) {
        Coord *fnlPos{copyCord(initPos)};
        incCord(fnlPos, offsets[i][0], offsets[i][1]);
        if (!isOOB(fnlPos)) {
            Piece *tgtPce{board->board[fnlPos->row][fnlPos->col]};
            if (tgtChk(tgtMode, intrpse, tgtPce, board->board[initPos->row][initPos->col])) {
                if (tgtPce->pieceID == KNIGHT)
                    appDta(data, fnlPos);
            } else if (vldPcMv(board, initPos, fnlPos))
                appDta(data, fnlPos);
        }
        dealloc(fnlPos);
    }
}

void pawnMov(const Board *const board, const bool tgtMode, const bool intrpse, const Coord *const initPos, Array *const data) {
    // {+-2, 0} offsets are calculated if the pawn has not moved yet
    static const size_t nOffset{8};
    static const char offsets[nOffset][2]{{-2, 0}, {-1, -1}, {-1, 0}, {-1, 1}, {1, -1}, {1, 0}, {1, 1}, {2, 0}};
    static const size_t diagMov[4]{1, 3, 6, 4};
    const Piece *const initPce{board->board[initPos->row][initPos->col]};
    Coord *fnlPos;
    size_t start;
    size_t end;


    if (initPce->pieceID == PAWN) {
        // tgtMode does not need to account for forward (one or two space) because pawns cannot capture forward and cannot move forward to a space if there is a piece occupying that space
        if (tgtMode) {
            start = initPce->isWhite ? 0 : 2;
            end = initPce->isWhite ? 2 : 4;
            for (size_t i{start}; i < end; i++) {
                fnlPos = copyCord(initPos);
                incCord(fnlPos, offsets[diagMov[i]][0], offsets[diagMov[i]][1]);
                if (!isOOB(fnlPos) && !board->board[fnlPos->row][fnlPos->col]->empty && (intrpse || board->board[fnlPos->row][fnlPos->col]->isWhite != initPce->isWhite))
                    appDta(data, fnlPos);
                dealloc(fnlPos);
            }
        } else {
            start = initPce->isWhite ? (initPce->fstMove ? 0 : 1) : 4;
            end = initPce->isWhite ? 4 : (initPce->fstMove ? 8 : 7);
            for (size_t i{start}; i < end; i++) {
                fnlPos = copyCord(initPos);
                incCord(fnlPos, offsets[i][0], offsets[i][1]);
                if (vldPcMv(board, initPos, fnlPos))
                    appDta(data, fnlPos);
                dealloc(fnlPos);
            }
        }
    }
}

// Castling does not apply when trying to calculate safe spaces for the king to move
// so this function doesn't need the tgtMode or intrpse variables
void castle(const Board *const board, const Coord *const initPos, Array *const data) {
    static const size_t nPos{8};
    static const Coord pos[nPos]{Coord{8, 1}, Coord{8, 3}, Coord{8, 8}, Coord{8, 7}, Coord{1, 1}, Coord{1, 3}, Coord{1, 8}, Coord{1, 7}};
    Piece *initPce{board->board[initPos->row][initPos->col]};

    if (initPce->pieceID == KING && initPce->fstMove) {
        size_t start = initPce->isWhite ? 0 : 4;
        size_t end = initPce->isWhite ? 4 : 8;
        for (size_t i{start}; i < end; i += 2) {
            Coord *newInit{copyCord(initPos)};
            incCord(newInit, 0, -1);
            if (board->board[pos[i].row][pos[i].col]->pieceID == ROOK && board->board[pos[i].row][pos[i].col]->fstMove && sfeSpce(board, &pos[i + 1]) && unObPth(
                    board, newInit, &pos[i]))
                appDta(data, &pos[i + 1]);
            dealloc(newInit);
        }
    }
}

bool isOOB(const Coord *const coord) {
    return coord->row < 1 || coord->row > 8 || coord->col < 1 || coord->col > 8;
}

bool vldPcMv(const Board *const board, const Coord *const initPos, const Coord *const fnlPos) {
    return !isOOB(fnlPos) && (board->board[fnlPos->row][fnlPos->col]->empty || board->board[fnlPos->row][fnlPos->col]->isWhite != board->board[initPos->row][initPos->col]->
                              isWhite);
}

void mvePce(Board *const board, const Coord *const a, const Coord *const b) {
    Piece *tmp{board->board[a->row][a->col]};
    board->board[a->row][a->col] = board->board[b->row][b->col];
    board->board[b->row][b->col] = tmp;
}

Coord *getInpt() {
    string input{};
    cin >> input;

    if (input.length() == 2 && toupper(input[0]) <= 'H' && toupper(input[0]) >= 'A' && input[1] <= '8' && input[1] >= '1') {
        cout << "Row: " << input[1] - 48 << ", Col: " << toupper(input[0]) - 64 << '\n';
        return newCord(input[1] - 48, toupper(input[0]) - 64);
    }
    cout << "Invalid board coordinate. Enter new board coordinate: ";
    return getInpt();
}

bool vldMove(const Coord *const coord, const Array *const vldMves) {
    for (int i{0}; i < vldMves->utilSze; i++)
        if (isEqual(vldMves->data[i], coord))
            return true;
    return false;
}


void pmtePce(Board *const board, const Coord *const coord) {
    string usrChce;
    Piece *target = board->board[coord->row][coord->col];
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

    target->enPasnt = false;
    target->fstMove = false;
    if (usrChce == "Queen")
        target->pieceID = QUEEN;
    else if (usrChce == "Rook")
        target->pieceID = ROOK;
    else if (usrChce == "Knight")
        target->pieceID = KNIGHT;
    else if (usrChce == "Bishop")
        target->pieceID = BISHOP;
}

void drawBrd(const Board *const board) {
    cout << "     a   b   c   d   e   f   g   h\n";
    for (int row{1}; row < board->VERTSZE - 1; row++) {
        cout << "   +---+---+---+---+---+---+---+---+\n";
        cout << " " << row << " |";
        for (int col{1}; col < board->HORZNSZ - 1; col++) {
            if (!board->board[row][col]->empty) {
                cout << ' ';
                switch (board->board[row][col]->pieceID) {
                    case KING:
                        cout << (board->board[row][col]->isWhite ? 'K' : 'k');
                        break;
                    case QUEEN:
                        cout << (board->board[row][col]->isWhite ? 'Q' : 'q');
                        break;
                    case ROOK:
                        cout << (board->board[row][col]->isWhite ? 'R' : 'r');
                        break;
                    case BISHOP:
                        cout << (board->board[row][col]->isWhite ? 'B' : 'b');
                        break;
                    case KNIGHT:
                        cout << (board->board[row][col]->isWhite ? 'N' : 'n');
                        break;
                    case PAWN:
                        cout << (board->board[row][col]->isWhite ? 'P' : 'p');
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

void clrScrn() {
    cout << "\033[H\033[2J";
}

Array *newArry(const size_t size) {
    Array *array = new Array;
    array->size = size;
    array->utilSze = 0;
    array->data = new Coord *[size];

    return array;
}

Coord *newCord(const unsigned char row, const unsigned char col) {
    Coord *tuple = new Coord;
    tuple->row = row;
    tuple->col = col;

    return tuple;
}

Board *newBord() {
    // Todo: Restore game board from file
    Board *board = new Board;
    board->board = new Piece **[board->VERTSZE];

    // Todo: Remove lambda function when finished (I use it here to make my code easier to debug when working on it)
    // This does not need to be a function because I will only use this code inside the newBord function
    auto initPce = [&board](const PieceID pieceID, const bool isWhite, const unsigned char row, const unsigned char col) {
        board->board[row][col]->empty = false;
        board->board[row][col]->isWhite = isWhite;
        board->board[row][col]->pieceID = pieceID;
        board->board[row][col]->fstMove = true;
        board->board[row][col]->enPasnt = false;
        board->board[row][col]->inCheck = false;
    };
    for (int row{0}; row < board->VERTSZE; row++) {
        board->board[row] = new Piece *[board->HORZNSZ];
        for (int col{0}; col < board->HORZNSZ; col++) {
            board->board[row][col] = new Piece;
            board->board[row][col]->empty = true;
        }
    }

    /*
     *  Pawn Initialization
     */
    for (int i{21}; i < 29; i++) {
        Coord *coord = clcCord(i);
        Coord *coord2 = clcCord(i, 50);
        initPce(PAWN, false, coord->row, coord->col);
        initPce(PAWN, true, coord2->row, coord2->col);
        dealloc(coord);
        dealloc(coord2);
    }

    /*
    *  King Initialization
    */
    initPce(KING, false, 1, 5);
    initPce(KING, true, 8, 5);

    /*
    *  Queen Initialization
    */
    initPce(QUEEN, false, 1, 4);
    initPce(QUEEN, true, 8, 4);

    /*
    *  Rook Initialization
    */
    initPce(ROOK, false, 1, 1);
    initPce(ROOK, false, 1, 8);
    initPce(ROOK, true, 8, 1);
    initPce(ROOK, true, 8, 8);

    /*
    *  Bishop Initialization
    */
    initPce(BISHOP, false, 1, 3);
    initPce(BISHOP, false, 1, 6);
    initPce(BISHOP, true, 8, 3);
    initPce(BISHOP, true, 8, 6);

    /*
    *  Knight Initialization
    */
    initPce(KNIGHT, false, 1, 2);
    initPce(KNIGHT, false, 1, 7);
    initPce(KNIGHT, true, 8, 2);
    initPce(KNIGHT, true, 8, 7);

    return board;
}

Player *newPlyr() {
    // Todo: Load player from file
    Player *player = new Player;
    player->nWins = 0;
    player->nLoss = 0;

    cout << "Enter your name (35 Characters or Less): ";
    cin.ignore();
    getline(cin, player->name);
    while (player->name.length() > 35) {
        cout << "Your name is too long. Enter a shorter name: ";
        getline(cin, player->name);
    }

    return player;
}

// Creates a copy of the coord - Does not append duplicates
// Will not append duplicate
void appDta(Array *const array, const Coord *const coord) {
    if (search(array, coord) == -1) {
        if (array->utilSze >= array->size)
            resize(array);
        array->data[array->utilSze++] = copyCord(coord);
    }
}

// Creates a copy of the coord - Appends duplicates
void appDta(Array *const to, const Array *const from) {
    size_t fnlSize{to->utilSze + from->utilSze};
    if (to->size < fnlSize)
        resize(to, fnlSize);
    for (unsigned int i{to->utilSze}; i < fnlSize; to->data[i] = copyCord(from->data[i - to->utilSze]), i++);
    to->size = fnlSize;
}

void resize(Array *array, const size_t newCap) {
    // Increments size by 1
    if (newCap == 0) {
        Coord **newData = new Coord *[++array->size];
        for (size_t i{0}; i < array->utilSze; newData[i] = array->data[i], i++);
        delete []array->data;
        array->data = newData;
    } else if (newCap > array->size) {
        // Resize to new specified size
        array->size = newCap;
        Coord **newData = new Coord *[array->size];
        for (size_t i{0}; i < array->utilSze; newData[i] = array->data[i], i++);
        delete []array->data;
        array->data = newData;
    } else if (newCap < array->size) {
        Coord **newData = new Coord *[newCap];
        // [0, newCap] - Ignoring anything past the new size
        for (size_t i{0}; i < newCap; newData[i] = array->data[i], i++);
        // Deallocate all Coord structures past new size inside the old array
        for (size_t i{newCap}; i < array->size; i++)
            dealloc(array->data[i]);
        array->size = newCap;

        delete []array->data;
        array->data = newData;
    }
}

void clear(Array *array) {
    for (int i{0}; i < array->utilSze; i++)
        dealloc(array->data[i]);
    delete []array->data;
    array->data = new Coord *[array->size];
}

void shrink(Array *const array) {
    resize(array, array->utilSze);
}

void dealloc(Array *array) {
    if (array->data != nullptr) {
        for (size_t i{0}; i < array->utilSze; i++)
            dealloc(array->data[i]);
        delete []array->data;
    }
    delete array;
}

void dealloc(const Coord *coord) {
    delete coord;
}

void dealloc(Board *board) {
    for (size_t row{0}; row < board->VERTSZE; row++)
        for (size_t col{0}; col < board->VERTSZE; col++)
            dealloc(board->board[row][col]);
    if (board->white != nullptr)
        dealloc(board->white);
    if (board->black != nullptr)
        dealloc(board->black);
    delete board;
}

void dealloc(Player *player) {
    delete player;
}

void dealloc(Piece *piece) {
    if (piece->vldMove != nullptr)
        dealloc(piece->vldMove);
    if (piece->capPth != nullptr)
        dealloc(piece->capPth);
    delete piece;
}

void incCord(Coord *const val, const Coord *const by) {
    val->row += by->row;
    val->col += by->col;
}

void incCord(Coord *const val, const unsigned char row, const unsigned char col) {
    val->row += row;
    val->col += col;
}


Coord *clcCord(const unsigned char coord, const int offset) {
    Coord *cord = new Coord;
    cord->row = (coord + offset) / 10;
    cord->col = (coord + offset) % 10;
    return cord;
}

Coord *copyCord(const Coord *const toCopy) {
    return newCord(toCopy->row, toCopy->col);
}

bool lessThn(const Coord *const a, const Coord *const b) {
    return a->row < b->row && a->col < b->col;
}

bool lessThn(const Coord *const a, const unsigned char bRow, const unsigned char bCol) {
    return a->row < bRow && a->col < bCol;
}

bool lessEq(const Coord *const a, const Coord *const b) {
    return a->row <= b->row && a->col <= b->col;
}

bool lessEq(const Coord *const a, const unsigned char bRow, const unsigned char bCol) {
    return a->row <= bRow && a->col <= bCol;
}

bool isEqual(const Coord *const a, const Coord *b) {
    return a->row == b->row && a->col == b->col;
}

bool isEqual(const Coord *const a, const unsigned char bRow, const unsigned char bCol) {
    return a->row == bRow && a->col == bCol;
}

Coord *walkPth(const Board *const board, const Coord *const initPos, const bool tgtMode, const unsigned char row, const unsigned char col, Array *const data) {
    Coord *offPos{copyCord(initPos)};
    incCord(offPos, row, col);
    Piece *tgtPce{board->board[offPos->row][offPos->col]};
    while (!isOOB(offPos) && tgtPce->empty) {
        if (!tgtMode)
            appDta(data, offPos);
        incCord(offPos, row, col);
        tgtPce = board->board[offPos->row][offPos->col];
    }
    return offPos;
}

bool tgtChk(const bool tgtMode, const bool intrpse, const Piece *const tgtPce, const Piece *const initPce) {
    return tgtMode && !tgtPce->empty && (intrpse || tgtPce->isWhite != initPce->isWhite);
}

int search(const Array *const array, const Coord *const target) {
    for (size_t i{0}; i < array->utilSze; i++)
        if (isEqual(array->data[i], target))
            return i;
    return -1;
}
