/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 24, 2026, 1:54 PM
 * Purpose:  Project 1 - Chess
 */

// System Libraries
#include <iostream> // Input Output Library
#include <cctype>   // C Character Handling Library
#include <cmath>    // C Math Library
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

bool unObPth(const Board *const board, const unsigned char initPos, const unsigned char tgtPos) {
    unsigned char start;
    unsigned char end;

    if (initPos == tgtPos)
        return true;

    // Left/Right
    if (initPos % 10 == tgtPos % 10) {
        start = initPos <= tgtPos ? initPos : tgtPos;
        end = initPos <= tgtPos ? tgtPos : initPos;
        for (; start <= end; start++)
            if (!board->board[start]->empty)
                return false;
        return true;
    }

    // Up/Down
    if (initPos / 10 == tgtPos / 10) {
        start = initPos <= tgtPos ? initPos : tgtPos;
        end = initPos <= tgtPos ? tgtPos : initPos;
        for (; start <= end; start += 10)
            if (!board->board[start]->empty)
                return false;
        return true;
    }
    //

    // Diagonal
    if (abs(initPos % 10 - tgtPos % 10) == abs(initPos / 10 - tgtPos / 10)) {
        start = initPos <= tgtPos ? initPos : tgtPos;
        end = initPos <= tgtPos ? tgtPos : initPos;
        int incAmt{initPos <= tgtPos ? 11 : -9};
        for (; start <= end; start += incAmt)
            if (!board->board[start]->empty)
                return false;
        return true;
    }
    return false;
}

void kingMov(const Board *const board, const bool tgtMode, const unsigned char initPos, Array *data) {
    const char offsets[]{-11, -10, -9, -1, 1, 9, 10, 11};
    unsigned char cur;

    for (int i{0}; i < 8; i++) {
        cur = initPos + offsets[i];
        if (tgtMode && !board->board[cur]->empty && board->board[cur]->isWhite != board->board[initPos]->isWhite) {
            if (board->board[cur]->pieceID == QUEEN)
                appDta(data, cur);
            else if (board->board[cur]->pieceID == ROOK && (cur == initPos + 1 || cur == initPos - 1 || cur == initPos - 10 || cur == initPos + 10))
                appDta(data, cur);
            else if (board->board[cur]->pieceID == BISHOP && (cur == initPos + 9 || cur == initPos - 9 || cur == initPos + 11 || cur == initPos - 11))
                appDta(data, cur);
            else if (board->board[cur]->pieceID == PAWN && ((board->board[cur]->isWhite && (cur == initPos + 11 || cur == initPos + 9)) || (
                                                                !board->board[cur]->isWhite && (cur == initPos - 11 || cur == initPos - 9))))
                appDta(data, cur);
        } else if (vldPcMv(board, initPos, cur))
            appDta(data, cur);
    }
}

void lineMov(const Board *const board, const bool tgtMode, const unsigned char initPos, Array *data) {
    unsigned char cur;
    // Up
    cur = initPos - 10;
    while (!isOOB(cur) && board->board[cur]->empty) {
        if (!tgtMode)
            appDta(data, cur);
        cur -= 10;
    }
    if (!isOOB(cur) && board->board[cur]->isWhite != board->board[initPos]->isWhite) {
        // The knight and bishop are ignored because they cannot move in a straight path vertically or horizontally
        // The pawn is also ignored because it cannot capture vertically or horizontally
        // The king is ignored because it cannot ocupy an adjacent square next to another king
        if (tgtMode) {
            if (board->board[cur]->pieceID == QUEEN || board->board[cur]->pieceID == ROOK)
                appDta(data, cur);
        } else
            appDta(data, cur);
    }

    // Down
    cur = initPos + 10;
    while (!isOOB(cur) && board->board[cur]->empty) {
        if (!tgtMode)
            appDta(data, cur);
        cur += 10;
    }

    if (!isOOB(cur) && board->board[cur]->isWhite != board->board[initPos]->isWhite) {
        if (tgtMode) {
            if (board->board[cur]->pieceID == QUEEN || board->board[cur]->pieceID == ROOK)
                appDta(data, cur);
        } else
            appDta(data, cur);
    }

    // Left
    cur = initPos - 1;
    while (!isOOB(cur) && board->board[cur]->empty)
        if (!tgtMode)
            appDta(data, cur--);
    if (!isOOB(cur) && board->board[cur]->isWhite != board->board[initPos]->isWhite) {
        if (tgtMode) {
            if (board->board[cur]->pieceID == QUEEN || board->board[cur]->pieceID == ROOK)
                appDta(data, cur);
        } else
            appDta(data, cur);
    }

    // Right
    cur = initPos + 1;
    while (!isOOB(cur) && board->board[cur]->empty)
        if (!tgtMode)
            appDta(data, cur++);
    if (!isOOB(cur) && board->board[cur]->isWhite != board->board[initPos]->isWhite) {
        if (tgtMode) {
            if (board->board[cur]->pieceID == QUEEN || board->board[cur]->pieceID == ROOK)
                appDta(data, cur);
        } else
            appDta(data, cur);
    }
}

void diagMov(const Board *const board, const bool tgtMode, const unsigned char initPos, Array *data) {
    const char offsets[]{-11, -9, 9, 11};
    unsigned char cur;
    for (int i{0}; i < 4; i++) {
        cur = initPos + offsets[i];
        while (!isOOB(cur) && board->board[cur]->empty) {
            if (!tgtMode)
                appDta(data, cur);
            cur += offsets[i];
        }
        if (!isOOB(cur) && board->board[cur]->isWhite != board->board[initPos]->isWhite) {
            // Ignoring king because it cannot occupy an adjacent square next to another king
            // Ignoring rook and knight because they cannot move diagonally
            if (tgtMode) {
                if (board->board[cur]->pieceID == QUEEN || board->board[cur]->pieceID == BISHOP)
                    appDta(data, cur);
                else if (board->board[cur]->pieceID == PAWN && ((board->board[cur]->isWhite && (cur == initPos + 11 || cur == initPos + 9)) || (
                                                                    !board->board[cur]->isWhite && (cur == initPos - 11 || cur == initPos - 9))))
                    appDta(data, cur);
            } else
                appDta(data, cur);
        }
    }
}

void knitMov(const Board *const board, const bool tgtMode, const unsigned char initPos, Array *data) {
    const char offsets[]{-21, -19, -12, -8, 8, 12, 19, 21};
    unsigned char cur;
    for (int i{0}; i < 8; i++) {
        cur = initPos + offsets[i];
        if (!isOOB(cur)) {
            if (tgtMode && !board->board[cur]->empty && board->board[cur]->isWhite != board->board[initPos]->isWhite && board->board[cur]->pieceID == KNIGHT) {
                appDta(data, cur);
            } else if (vldPcMv(board, initPos, cur))
                appDta(data, cur);
        }
    }
}

void pawnMov(const Board *const board, const bool tgtMode, const unsigned char initPos, Array *data) {
    const char offsets[]{-11, -10, -9, 9, 10, 11};
    char cur;
    if (tgtMode) {
        if (!board->board[initPos - 11]->empty && !board->board[initPos - 11]->isWhite && board->board[initPos]->isWhite)
            appDta(data, cur);
        if (!board->board[initPos - 9]->empty && !board->board[initPos - 9]->isWhite && board->board[initPos]->isWhite)
            appDta(data, cur);

        if (!board->board[initPos + 11]->empty && board->board[initPos + 11]->isWhite && !board->board[initPos]->isWhite)
            appDta(data, cur);
        if (!board->board[initPos + 9]->empty && board->board[initPos + 9]->isWhite && !board->board[initPos]->isWhite)
            appDta(data, cur);
    } else {
        if (board->board[initPos]->isWhite) {
            for (int i{0}; i < 3; i++) {
                cur = initPos + offsets[i];
                if (vldPcMv(board, initPos, cur))
                    appDta(data, cur);
            }
        } else {
            for (int i{3}; i < 6; i++) {
                cur = initPos + offsets[i];
                if (vldPcMv(board, initPos, cur))
                    appDta(data, cur);
            }
        }
    }
}

void castle(const Board *const board, const unsigned char initPos, Array *data) {
    if (board->board[initPos]->pieceID == KING && board->board[initPos]->fstMove) {
        if (board->board[initPos]->isWhite) {
            if (board->board[82]->pieceID == ROOK && board->board[82]->fstMove)
                if (sfeSpce(board, 84) && unObPth(board, initPos - 1, 82))
                    appDta(data, 84);

            if (board->board[89]->pieceID == ROOK && board->board[89]->fstMove)
                if (sfeSpce(board, 88) && unObPth(board, initPos + 1, 89))
                    appDta(data, 88);
        } else {
            if (board->board[12]->pieceID == ROOK && board->board[12]->fstMove)
                if (sfeSpce(board, 14) && unObPth(board, initPos - 1, 12))
                    appDta(data, 14);

            if (board->board[19]->pieceID == ROOK && board->board[19]->fstMove)
                if (sfeSpce(board, 18) && unObPth(board, initPos + 1, 19))
                    appDta(data, 18);
        }
    }
}

bool isOOB(const unsigned char pos) {
    return pos <= 12 || pos >= 89 || pos % 10 == 0 || pos % 10 == 1;
}

bool vldPcMv(const Board *const board, const unsigned char initPos, const unsigned char fnlPos) {
    return !isOOB(fnlPos) && (board->board[fnlPos]->empty || board->board[fnlPos]->isWhite != board->board[initPos]->isWhite);
}

void mvePce(Board *board, const unsigned char a, const unsigned char b) {
    Piece *tmp(board->board[a]);
    board->board[a] = board->board[b];
    board->board[b] = tmp;
}

unsigned char getInpt() {
    string input{};
    cin >> input;
    while (input.length() != 2) {
        cout << "Invalid board coordinate. Enter new board coordinate: ";
        cin >> input;
    }
    while (toupper(input[0]) > 'H' || toupper(input[0]) < 'A' || input[1] > '8' || input[1] < '1') {
        cout << "Invalid board coordinate. Enter new board coordinate: ";
        cin >> input;
        while (input.length() != 2) {
            cout << "Invalid board coordinate. Enter new board coordinate: ";
            cin >> input;
        }
    }
    return (toupper(input[0]) - 63) + (82 - (input[1] - 49) * 10);
}

bool vldMove(const unsigned char tgtMove, const Array *const vldMves) {
    for (int i{0}; i < vldMves->utilSze; i++)
        if (vldMves->data[i] == tgtMove)
            return true;
    return false;
}

void pmtePce(Board *const board, const unsigned char tgtPce) {
    string usrChce;
    Piece *target = *(board->board + tgtPce / board->VERTSZE) + tgtPce % board->HORZNSZ;
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
    for (int row{1}; row < board->HORZNSZ - 1; row++) {
        cout << "   +---+---+---+---+---+---+---+---+";
        cout << " " << row + 1 << " |";
        for (int col{1}; col < board->VERTSZE - 1; col++) {
            if (!board->board[row][col].empty) {
                cout << ' ';
                switch (board->board[row][col].pieceID) {
                    case KING:
                        cout << (board->board[row][col].isWhite ? 'K' : 'k');
                        break;
                    case QUEEN:
                        cout << (board->board[row][col].isWhite ? 'Q' : 'q');
                        break;
                    case ROOK:
                        cout << (board->board[row][col].isWhite ? 'R' : 'r');
                        break;
                    case BISHOP:
                        cout << (board->board[row][col].isWhite ? 'B' : 'b');
                        break;
                    case KNIGHT:
                        cout << (board->board[row][col].isWhite ? 'N' : 'n');
                        break;
                    case PAWN:
                        cout << (board->board[row][col].isWhite ? 'P' : 'p');
                        break;
                    default:
                        cout << ' ';
                }
                cout << " |";
            } else
                cout << " * |";
        }
    }
    cout << "   +---+---+---+---+---+---+---+---+\n\n";
}

void clrScrn() {
    cout << "\033[H\033[2J";
}

Array *alloc(const unsigned int size) {
    Array *array = new Array;
    array->size = size;
    array->data = new unsigned char[size];

    return array;
}

Player *newPlyr() {
    // Todo: New Player from file
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

void appDta(Array *const array, unsigned char newDta) {
    if (array->utilSze >= array->size)
        resize(array);
    array->data[array->utilSze++] = newDta;
}

void appDta(Array *const to, Array *from, bool dstryFm) {
    if (to->size < to->utilSze + from->utilSze)
        resize(to, to->utilSze + from->utilSze);
    for (unsigned int i{to->utilSze}; i < to->utilSze + from->utilSze; to->data[i] = from->data[i - to->utilSze], i++);
    if (dstryFm)
        dealloc(from);
}

void resize(Array *const array, int newCap) {
    if (newCap == -1) {
        unsigned char *newData = new unsigned char[array->size++];
        for (unsigned int i{0}; i < array->utilSze; newData[i] = array->data[i], i++);
        delete []array->data;
        array->data = newData;
    } else if (newCap > array->size) {
        array->size = newCap;
        unsigned char *newData = new unsigned char[array->size];
        for (unsigned int i{0}; i < array->utilSze; newData[i] = array->data[i], i++);
        delete []array->data;
        array->data = newData;
    }
}

void dealloc(Array *array) {
    delete []array->data;
    delete array;
}

void dealloc(Board *board) {
    for (unsigned int i{0}; i < board->VERTSZE * board->HORZNSZ; i++)
        dealloc(*(board->board + i / board->VERTSZE) + i % board->HORZNSZ);
}

void dealloc(Player *player) {
    delete player;
}

void dealloc(Piece *piece) {
    if (piece->vldMove != nullptr)
        dealloc(piece->vldMove);
    if (piece->capPth != nullptr)
        dealloc(piece->capPth);
}

unsigned char postDec(unsigned char &val, const int by) {
    val -= by;
    return val + by;
}

unsigned char postInc(unsigned char &val, const int by) {
    val += by;
    return val - by;
}
