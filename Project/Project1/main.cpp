/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 24, 2026, 1:54 PM
 * Purpose:  Project 1 - Chess
 */

// System Libraries
#include <iostream> // Input Output Library
#include <cctype>
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

void kingMov(const Board *const board, const bool tgtMode, const unsigned char initPos, Array *data) {
    const char offsets[]{-11, -10, -9, -1, 1, 9, 10, 11};
    unsigned char cur;

    for (int i{0}; i < 8; i++) {
        cur = initPos + offsets[i];
        if (!isOOB(cur) && board->board[cur]->isWhite != board->board[initPos]->isWhite) {
            if (tgtMode) {
                switch (board->board[cur]->pieceID) {
                    // Since the king cannot be right next to the other king, the king case is ignored
                    // Additionally the knight is ignored because it is impossible for a knight to move to an adjacent square
                    case QUEEN:
                        appDta(data, cur);
                        break;
                    case ROOK:
                        if (cur == initPos + 1 || cur == initPos - 1 || cur == initPos - 10 || cur == initPos + 10)
                            appDta(data, cur);
                        break;
                    case BISHOP:
                        if (cur == initPos + 9 || cur == initPos - 9 || cur == initPos + 11 || cur == initPos - 11)
                            appDta(data, cur);
                        break;
                    case PAWN:
                        // Todo: Account for en passant
                        if ((board->board[cur]->isWhite && (cur == initPos + 11 || cur == initPos + 9)) || (
                                !board->board[cur]->isWhite && (cur == initPos - 11 || cur == initPos - 9)))
                            appDta(data, cur);
                        break;
                }
            } else
                appDta(data, cur);
        }
    }
}

void lineMov(const Board *const board, const bool tgtMode, const unsigned char initPos, Array *data) {
    unsigned char cur{initPos};
    // Up
    cur -= 10;
    while (!isOOB(cur) && board->board[cur]->empty)
        if (!tgtMode)
            appDta(data, postDec(cur, 10));

    // The knight and bishop are ignored because they cannot move in a straight path vertically or horizontally
    // The pawn is also ignored because it cannot capture vertically or horizontally
    // The king is ignored because it cannot ocupy an adjacent square next to another king
    if (tgtMode && cur >= 12 && (board->board[cur]->pieceID == QUEEN || board->board[cur]->pieceID == ROOK))
        appDta(data, cur);

    // Down
    cur = initPos + 10;
    while (!isOOB(cur) && board->board[cur]->empty)
        if (!tgtMode)
            appDta(data, postInc(cur, 10));
    if (tgtMode && !isOOB(cur) && (board->board[cur]->pieceID == QUEEN || board->board[cur]->pieceID == ROOK))
        appDta(data, cur);

    // Left
    cur = initPos - 1;
    while (!isOOB(cur) && board->board[cur]->empty)
        if (!tgtMode)
            appDta(data, cur--);
    if (tgtMode && !isOOB(cur) && (board->board[cur]->pieceID == QUEEN || board->board[cur]->pieceID == ROOK))
        appDta(data, cur);

    // Right
    cur = initPos + 1;
    while (!isOOB(cur) && board->board[cur]->empty)
        if (!tgtMode)
            appDta(data, cur++);
    if (tgtMode && !isOOB(cur) && (board->board[cur]->pieceID == QUEEN || board->board[cur]->pieceID == ROOK))
        appDta(data, cur);
}


bool isOOB(const unsigned char pos) {
    return pos <= 12 || pos >= 89 || pos % 10 == 0 || pos % 10 == 1;
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
