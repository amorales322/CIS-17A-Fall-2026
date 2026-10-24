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

void drawBrd(const Board *const board) {
    cout << "     a   b   c   d   e   f   g   h\n";
    for (int row{0}; row < board->HORZNSZ; row++) {
        cout << "   +---+---+---+---+---+---+---+---+";
        cout << " " << row + 1 << " |";
        for (int col{0}; col < board->VERTSZE; col++) {
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

void appDta(Array *array, unsigned char newDta) {
    if (array->utilSze >= array->size)
        resize(array);
    array->data[array->utilSze++] = newDta;
}

void appDta(Array *to, Array *from, bool dstryFm) {
    if (to->size < to->utilSze + from->utilSze)
        resize(to, to->utilSze + from->utilSze);
    for (unsigned int i{to->utilSze}; i < to->utilSze + from->utilSze; to->data[i] = from->data[i - to->utilSze], i++);
    if (dstryFm)
        dealloc(from);
}

void resize(Array *array, int newCap) {
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
