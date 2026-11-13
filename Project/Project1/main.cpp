/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 24, 2026, 1:54 PM
 * Purpose:  Project 1 - Chess
 */

// System Libraries
#include <iostream> // Input Output Library
#include <fstream>  // File Stream Library
#include <string>   // String Library
#include <cstring>  // C String Library
using namespace std;

// User Libraries
// Contains Function Prototypes
#include "Array.h"
#include "ASCII.h"
#include "Board.h"
#include "Coord.h"
#include "fileUtil.h"
#include "moveCalculations.h"
#include "Piece.h"
#include "PieceID.h"
#include "PlyrClr.h"


// Global Constants not Variables
// Science, Math, Conversions, Dimensions

// Function Prototypes

// Execution begins here at main
int main(int argc, char **argv) {
    // Set random number seed

    // Declare & Initialize Variables
    /*
     * User inputs
     */
    string flePth1;
    string flePth2;
    string flePth3;
    bool inpt{false};
    Coord *tgtPce{nullptr};
    Coord *whereTo{nullptr};

    /*
     * Game Save Files
     */
    fstream plyr1;
    fstream plyr2;
    fstream gameDta;

    /*
     * Loading Data
     */
    cout << "Would you like to load a game from a save file?: ";
    inpt = getOpt();
    cin.ignore();
    if (inpt) {
        // Game Save
        cout << "Enter the filename for the game save you would like to load: ";
        flePth1 = getFPth();
        opnFile(gameDta, flePth1);
    } else {
        cout << "Enter the filename for the game save you would like to save to: ";
        flePth1 = getFPth();
        opnFile(gameDta, flePth1, true);
    }
    Board *board{newBord(gameDta, inpt)};

    cout << "Would you like to load player save data for player 1 from a file?: ";
    inpt = getOpt();
    cin.ignore();
    if (inpt) {
        // Player 1
        cout << "Enter the filename for player 1's data that you would like to load: ";
        flePth2 = getFPth(flePth1);
        opnFile(plyr1, flePth2);
    } else {
        cout << "Enter the filename for player 1's data that you would like to save to: ";
        flePth2 = getFPth(flePth1);
        opnFile(plyr1, flePth2, true);
    }
    board->white = newPlyr(plyr1, inpt, 1);

    cout << "Would you like to load player save data for player 2 from a file?: ";
    inpt = getOpt();
    cin.ignore();
    if (inpt) {
        // Player 2
        cout << "Enter the filename for player 2's data that you would like to load: ";
        flePth3 = getFPth(flePth1, flePth2);
        opnFile(plyr2, flePth3);
    } else {
        // Player 2
        cout << "Enter the filename for player 2's data that you would like to save to: ";
        flePth3 = getFPth(flePth1, flePth2);
        opnFile(plyr2, flePth3, true);
    }
    board->black = newPlyr(plyr2, inpt, 2);


    /*
     * Game Arrays
     */
    // Which pieces can move, if limited in some way
    Array *canMove{newArry()};
    // Valid positions a piece can move to
    Array *vldMves{newArry()};
    // Stores which pieces are putting the king in check
    Array *whoChk{newArry()};

    // Stores the location(s) of piece(s) that can interpose between an enemy piece and the king
    Array *canIPos{newArry()};
    // Stores the location(s) of where piece(s) can go to in order to interpose
    Array *iPosePs{newArry()};

    // Map/Process the Inputs -> Outputs
    if (inpt)
        ptPlrSt(board->white, board->black);
    do {
        /*
         * Main Game Loop
         */
        do {
            drawBrd(board);
            board->deadPos = deadPos(board);
            if (!board->deadPos) {
                if (board->check == board->whoTurn) {
                    if (board->check == PlyrClr::WHITE)
                        vldMves = sfeMves(board, board->wKngPos);
                    else
                        vldMves = sfeMves(board, board->bKngPos);

                    // If no safe spaces remain after this elimination process ends, the game ends
                    if (vldMves->empty)
                        board->chkmte = board->whoTurn;
                    else if (board->whoTurn == PlyrClr::WHITE)
                        appDta(canMove, board->wKngPos);
                    else
                        appDta(canMove, board->bKngPos);

                    // If the king is just in check and not in checkmate
                    if (board->chkmte == PlyrClr::NONE) {
                        /*
                         * Two scenarios can occur
                         * 1. If the king is in check by one piece, then a piece can potentially interpose between the king and the enemy piece, and we calculate this
                         * 2. If the king is in check by multiple pieces, then no piece cannot interpose between the multiple pieces and the king, and we just skip to the player input
                         */
                        if (whoChk->utilSze == 1) {
                            if (board->whoTurn == PlyrClr::WHITE)
                                pceIntr(board, board->wKngPos, vldMves->data[0], canIPos, iPosePs, board->whoTurn);
                            else
                                pceIntr(board, board->bKngPos, vldMves->data[0], canIPos, iPosePs, board->whoTurn);
                            if (!canIPos->empty)
                                appDta(canMove, canIPos);
                        }

                        // Get Piece to Move
                        cout << (board->whoTurn == PlyrClr::WHITE ? board->white->name : board->black->name) <<
                                ", enter which piece you would like to move (-1 to surrender, -2 to save & quit) (Can move: ";
                        pntArry(canMove);
                        cout << "): ";

                        tgtPce = getInpt();
                        while (!isEqual(tgtPce, -1, -1) && !isEqual(tgtPce, -2, -2) && !vldMove(tgtPce, canMove)) {
                            cout << "Invalid selection, select a new piece to move: ";
                            dealloc(tgtPce);
                            tgtPce = getInpt();
                        }
                        if (!isEqual(tgtPce, -1, -1) && !isEqual(tgtPce, -2, -2)) {
                            /*
                             * Get where to move piece
                             */
                            cout << "Where would you like to move your " << getName(board, tgtPce) << " to (Can move to: ";
                            pntArry(vldMves);
                            cout << "): ";
                            whereTo = getInpt();

                            // If king is selected
                            if (search(canMove, tgtPce) == 0) {
                                while (!vldMove(whereTo, vldMves)) {
                                    cout << "Cannot move your " << getName(board, tgtPce) << " here, enter new spot to move your " << getName(board, tgtPce) << " to: ";
                                    dealloc(whereTo);
                                    whereTo = getInpt();
                                }
                            } else {
                                // While the target location is not the valid location the interposing piece can move to
                                while (!isEqual(whereTo, iPosePs->data[search(canIPos, tgtPce)])) {
                                    cout << "Cannot move your " << getName(board, tgtPce) << " here, enter new spot to move your " << getName(board, tgtPce) << " to: ";
                                    dealloc(whereTo);
                                    whereTo = getInpt();
                                }
                            }
                        } else {
                            if (isEqual(tgtPce, -1, -1))
                                board->surndr = board->whoTurn;
                            else if (isEqual(tgtPce, -2, -2))
                                board->exitGme = board->whoTurn;
                        }
                    }
                } else {
                    board->stlemte = stlmte(board, board->whoTurn);
                    if (!board->stlemte) {
                        cout << (board->whoTurn == PlyrClr::WHITE ? board->white->name : board->black->name) <<
                                ", enter which piece you would like to move (-1 to surrender, -2 to save & quit): ";
                        do {
                            tgtPce = getInpt();
                            while (!isEqual(tgtPce, -1, -1) && !isEqual(tgtPce, -2, -2) && (getPce(board, tgtPce)->empty || getPce(board, tgtPce)->pceClr != board->whoTurn)) {
                                cout << "Invalid selection, enter a new piece that you would like to move: ";
                                dealloc(tgtPce);
                                tgtPce = getInpt();
                            }
                            if (!isEqual(tgtPce, -1, -1) && !isEqual(tgtPce, -2, -2)) {
                                switch (getPce(board, tgtPce)->pieceID) {
                                    case PieceID::KING:
                                        dealloc(vldMves);
                                        vldMves = sfeMves(board, tgtPce);
                                        break;
                                    case PieceID::QUEEN:
                                        lineMov(board, false, false, tgtPce, vldMves);
                                        diagMov(board, false, false, tgtPce, vldMves);
                                        break;
                                    case PieceID::ROOK:
                                        lineMov(board, false, false, tgtPce, vldMves);
                                        break;
                                    case PieceID::BISHOP:
                                        diagMov(board, false, false, tgtPce, vldMves);
                                        break;
                                    case PieceID::KNIGHT:
                                        knitMov(board, false, false, tgtPce, vldMves);
                                        break;
                                    case PieceID::PAWN:
                                        pawnMov(board, false, false, tgtPce, vldMves);
                                        break;
                                }
                                if (vldMves->empty)
                                    cout << "This piece cannot move anywhere at the moment, enter a new piece you would like to move: ";
                            } else {
                                if (isEqual(tgtPce, -1, -1))
                                    board->surndr = board->whoTurn;
                                else if (isEqual(tgtPce, -2, -2))
                                    board->exitGme = board->whoTurn;
                            }
                        } while (vldMves->empty && board->surndr == PlyrClr::NONE && board->exitGme == PlyrClr::NONE);

                        if (board->surndr == PlyrClr::NONE && board->exitGme == PlyrClr::NONE) {
                            cout << "Where would you like to move your " << getName(board, tgtPce) << " to (Can move to: ";
                            pntArry(vldMves);
                            cout << "): ";
                            whereTo = getInpt();
                            while (!vldMove(whereTo, vldMves)) {
                                cout << "Cannot move your " << getName(board, tgtPce) << " here, enter new spot to move your " << getName(board, tgtPce) << " to: ";
                                dealloc(whereTo);
                                whereTo = getInpt();
                            }
                        }
                    }
                }

                if (board->chkmte == PlyrClr::NONE && !board->stlemte && board->surndr == PlyrClr::NONE && board->exitGme == PlyrClr::NONE) {
                    getPce(board, tgtPce)->fstMove = false;
                    if (getPce(board, tgtPce)->pieceID == PieceID::KING) {
                        if (board->whoTurn == PlyrClr::WHITE) {
                            board->wKngPos->row = whereTo->row;
                            board->wKngPos->col = whereTo->col;
                        } else {
                            board->bKngPos->row = whereTo->row;
                            board->bKngPos->col = whereTo->col;
                        }
                    }
                    if (getPce(board, tgtPce)->pieceID == PieceID::PAWN && (whereTo->row == 1 || whereTo->row == 8))
                        pmtePce(getPce(board, tgtPce));
                    mvePce(board, tgtPce, whereTo);

                    if (board->whoTurn == PlyrClr::WHITE) {
                        if (!sfeSpce(board, board->bKngPos, PlyrClr::BLACK))
                            board->check = PlyrClr::BLACK;
                        else
                            board->check = PlyrClr::NONE;
                    } else {
                        if (!sfeSpce(board, board->wKngPos, PlyrClr::WHITE))
                            board->check = PlyrClr::WHITE;
                        else
                            board->check = PlyrClr::NONE;
                    }
                    board->whoTurn = board->whoTurn == PlyrClr::WHITE ? PlyrClr::BLACK : PlyrClr::WHITE;
                }
            }
            clrScrn();
            clear(canMove);
            clear(vldMves);
            clear(whoChk);
            clear(canIPos);
            clear(iPosePs);
            dealloc(tgtPce);
            dealloc(whereTo);
            tgtPce = nullptr;
            whereTo = nullptr;
        } while (board->chkmte == PlyrClr::NONE && !board->stlemte && !board->deadPos && board->surndr == PlyrClr::NONE && board->exitGme == PlyrClr::NONE);

        /*
         * Game Ending
         */
        if (board->chkmte != PlyrClr::NONE | board->surndr != PlyrClr::NONE) {
            if (board->chkmte != PlyrClr::NONE)
                cout << "Game over, " << (board->chkmte == PlyrClr::WHITE ? board->black->name : board->white->name) << " wins!.\n";
            if (board->surndr != PlyrClr::NONE)
                cout << (board->surndr == PlyrClr::WHITE ? board->white->name : board->black->name) << " has chosen to surrender, " << (board->surndr == PlyrClr::WHITE
                    ? board->black->name : board->white->name) << " wins!.\n";
            if (board->chkmte == PlyrClr::WHITE || board->surndr == PlyrClr::WHITE) {
                board->white->nLoss++;
                board->black->nWins++;
            } else {
                board->white->nWins++;
                board->black->nLoss++;
            }
        }
        if (board->stlemte)
            cout << "Stalemate detected, game over.\n";
        if (board->deadPos)
            cout << "Dead position detected, game over.\n";
        switch (board->exitGme) {
            case PlyrClr::NONE:
                cout << "Would you like to start a new game (Y) or save & quit (N)?: ";
                inpt = getOpt();
                rstBrd(board);
                break;
            case PlyrClr::WHITE:
                cout << board->white->name << " has requested to end the game, would you like to end the game " << board->black->name << " (Y or N)?: ";
                inpt = !getOpt();
                if (inpt == true)
                    board->exitGme = PlyrClr::NONE;
                break;
            case PlyrClr::BLACK:
                cout << board->black->name << " has requested to end the game, would you like to end the game " << board->white->name << " (Y or N)?: ";
                inpt = !getOpt();
                if (inpt == true)
                    board->exitGme = PlyrClr::NONE;
                break;
        }
    } while (inpt);

    // Display Inputs/Outputs
    ptPlrSt(board->white, board->black);

    // Clean up memory and files
    cout << "Saving game...\n";
    toFile(gameDta, plyr1, plyr2, board);

    dealloc(vldMves);
    dealloc(canMove);
    dealloc(whoChk);
    dealloc(iPosePs);
    dealloc(canIPos);
    dealloc(board);

    plyr1.close();
    plyr2.close();
    gameDta.close();

    // Exit the Program
    return 0;
}

/*
 * Array.h Functions
 */
Array *newArry(const size_t size) {
    Array *array = new Array;
    array->size = size;
    array->utilSze = 0;
    array->data = new Coord *[size];
    array->empty = true;

    return array;
}

void pntArry(const Array *const array) {
    if (!array->empty)
        for (size_t i{0}; i < array->utilSze; i++)
            cout << toChsNt(array->data[i]) << (i < array->utilSze - 1 ? " " : "");
    else
        cout << "None";
}

void cpyArry(Array *const to, const Array *const from) {
    if (!from->empty)
        appDta(to, from);
}

void appDta(Array *const array, const Coord *const coord) {
    if (search(array, coord) == -1) {
        if (array->utilSze >= array->size)
            resize(array);
        array->data[array->utilSze++] = copyCord(coord);
        array->empty = false;
    }
}

void appDta(Array *const to, const Array *const from) {
    if (!from->empty) {
        size_t fnlSize{to->utilSze + from->utilSze};
        if (to->size < fnlSize)
            resize(to, fnlSize);
        for (unsigned int i{to->utilSze}; i < fnlSize; i++)
            to->data[i] = copyCord(from->data[i - to->utilSze]);
        to->utilSze = fnlSize;
        to->empty = false;
    }
}

void pop(Array *const array, const int idx = -1) {
    if (!array->empty) {
        if (idx < 0 || idx == array->utilSze - 1)
            delete []array->data[--array->utilSze];
        else if (idx < array->utilSze) {
            Coord **newData = new Coord *[array->size];
            for (size_t i{0}; i < idx; i++)
                newData[i] = array->data[i];
            for (size_t i{static_cast<size_t>(idx) + 1}; i < array->utilSze; i++)
                newData[i - 1] = array->data[i];
            delete []array->data;
            array->data = newData;
            array->utilSze--;
        }
        if (array->utilSze == 0)
            array->empty = true;
    }
}

void resize(Array *array, const int newCap) {
    if (newCap >= -1) {
        // Increments size by 1
        if (newCap == -1) {
            Coord **newData = new Coord *[++array->size];
            for (size_t i{0}; i < array->utilSze; i++)
                newData[i] = array->data[i];
            delete []array->data;
            array->data = newData;
        } else if (newCap == 0) {
            clear(array);
        } else if (newCap < array->size) {
            Coord **newData = new Coord *[newCap];
            // [0, newCap] - Ignoring anything past the new size
            for (size_t i{0}; i < newCap; i++)
                newData[i] = array->data[i];
            // Deallocate all Coord structures past new size inside the old array
            for (size_t i{static_cast<size_t>(newCap)}; i < array->size; i++)
                dealloc(array->data[i]);
            array->size = newCap;

            delete []array->data;
            array->data = newData;
        } else if (newCap > array->size) {
            // Resize to new specified size
            array->size = newCap;
            Coord **newData = new Coord *[array->size];
            for (size_t i{0}; i < array->utilSze; i++)
                newData[i] = array->data[i];
            delete []array->data;
            array->data = newData;
        }
        if (array->utilSze == 0)
            array->empty = true;
    }
}

void clear(Array *array) {
    for (int i{0}; i < array->utilSze; i++)
        dealloc(array->data[i]);
    delete []array->data;
    array->utilSze = 0;
    array->data = new Coord *[array->size];
    array->empty = true;
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

int search(const Array *const array, const Coord *const target) {
    if (!array->empty) {
        for (size_t i{0}; i < array->utilSze; i++)
            if (isEqual(array->data[i], target))
                return i;
    }
    return -1;
}

/*
 * Ascii.h Functions
 */

/*
 * Utility
 */
size_t clcLftW(size_t width) {
    return width % 2 == 0 ? width / 2 : width / 2 + 1;
}

size_t clcRgtW(size_t width) {
    return width / 2;
}

string getBlnk(const size_t width, const bool ligtCel) {
    return string(width, ligtCel ? '#' : ' ');
}

string getBlnk(const size_t width, const char fillChr) {
    return string(width, fillChr);
}

void drwBlRw(const bool lghtCel) {
    cout << '|' << getBlnk(23, lghtCel);
}

void drClmRw(const char *content, const bool lghtCel) {
    static const size_t width{23};
    size_t remWdth{width - strlen(content) - 2};
    size_t lftWdth{clcLftW(remWdth)};
    size_t rgtWdth{clcRgtW(remWdth)};

    // Print cell row
    cout << '|' << getBlnk(lftWdth, lghtCel) << ' ' << content << ' ' << getBlnk(rgtWdth, lghtCel);
}

void drawNum(const char *content, const size_t width) {
    size_t remWdth{width - strlen(content) - 1};
    size_t lftWdth{clcLftW(remWdth)};
    size_t rgtWdth{clcRgtW(remWdth)};

    // Print cell row
    cout << getBlnk(lftWdth, false) << ' ' << content << ' ' << getBlnk(rgtWdth, false);
}

void drClmRw(const char *left, const char *right, const size_t inrWdth, const bool lghtCel, const char filChar) {
    static const size_t width{23};
    size_t remWdth{width - inrWdth - strlen(left) - strlen(right) - 2};
    size_t lftWdth{clcLftW(remWdth)};
    size_t rgtWdth{clcRgtW(remWdth)};

    // Print cell row
    cout << '|' << getBlnk(lftWdth, lghtCel) << ' ' << left << getBlnk(inrWdth, filChar) << right << ' ' << getBlnk(rgtWdth, lghtCel);
}

void drClmRw(const char *left, const char *right, const size_t inrWdth, const bool lghtCel, const PlyrClr &player) {
    static const size_t width{23};
    size_t remWdth{width - inrWdth - strlen(left) - strlen(right) - 2};
    size_t lftWdth{clcLftW(remWdth)};
    size_t rgtWdth{clcRgtW(remWdth)};

    // Print cell row
    cout << '|' << getBlnk(lftWdth, lghtCel) << ' ' << left << (player == PlyrClr::WHITE ? getBlnk(inrWdth, '#') : getBlnk(inrWdth, ' ')) << right << ' ' <<
            getBlnk(rgtWdth, lghtCel);
}

void drClmRw(const char *left, const char *right, const size_t inrWdth, const bool lghtCel, const PlyrClr &player, const char filChar) {
    static const size_t width{23};
    size_t remWdth{width - inrWdth - strlen(left) - strlen(right) - 2};
    size_t lftWdth{clcLftW(remWdth)};
    size_t rgtWdth{clcRgtW(remWdth)};

    // Print cell row
    cout << '|' << getBlnk(lftWdth, lghtCel) << ' ' << left << (player == PlyrClr::WHITE ? getBlnk(inrWdth, '#') : getBlnk(inrWdth, filChar)) << right << ' ' <<
            getBlnk(rgtWdth, lghtCel);
}

/*
 * Letters
 * https://www.asciiart.eu/text-to-ascii-art
 */
void drawA(const size_t row) {
    switch (row) {
        case 3:
            drawNum("_");
            break;
        case 4: //
            drawNum("/ \\");
            break;
        case 5:
            drawNum("/ _ \\");
            break;
        case 6:
            drawNum("/ ___ \\");
            break;
        case 7:
            drawNum("/_/   \\_\\");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void drawB(const size_t row) {
    switch (row) {
        case 3:
            drawNum("____");
            break;
        case 4: //
            drawNum("| __ )");
            break;
        case 5:
            drawNum("|  _ \\");
            break;
        case 6:
            drawNum("| |_) |");
            break;
        case 7:
            drawNum("|____/");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void drawC(const size_t row) {
    switch (row) {
        case 3:
            drawNum("____");
            break;
        case 4: //
            drawNum("/ ___|");
            break;
        case 5:
            drawNum("| |     ");
            break;
        case 6:
            drawNum("| |___  ");
            break;
        case 7:
            drawNum("\\____|");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void drawD(const size_t row) {
    switch (row) {
        case 3:
            drawNum("____");
            break;
        case 4: //
            drawNum("|  _ \\");
            break;
        case 5:
            drawNum("| | | |");
            break;
        case 6:
            drawNum("| |_| |");
            break;
        case 7:
            drawNum("|____/");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void drawE(const size_t row) {
    switch (row) {
        case 3:
            drawNum("_____");
            break;
        case 4: //
            drawNum("| ____|");
            break;
        case 5:
            drawNum("|  _| ");
            break;
        case 6:
            drawNum("| |___");
            break;
        case 7:
            drawNum("|_____|");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void drawF(const size_t row) {
    switch (row) {
        case 3:
            drawNum("_____");
            break;
        case 4: //
            drawNum("|  ___|");
            break;
        case 5:
            drawNum("| |_  ");
            break;
        case 6:
            drawNum("|  _| ");
            break;
        case 7:
            drawNum("|_|   ");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void drawG(const size_t row) {
    switch (row) {
        case 3:
            drawNum("____");
            break;
        case 4: //
            drawNum("/ ___|");
            break;
        case 5:
            drawNum("| |  _  ");
            break;
        case 6:
            drawNum("| |_| |  ");
            break;
        case 7:
            drawNum("\\____|");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void drawH(const size_t row) {
    switch (row) {
        case 3:
            drawNum("_   _");
            break;
        case 4: //
            drawNum("| | | |");
            break;
        case 5:
            drawNum("| |_| |");
            break;
        case 6:
            drawNum("|  _  |");
            break;
        case 7:
            drawNum("|_| |_|");
            break;
        default:
            cout << getBlnk(24, false);
    }
}


/*
 * Numbers
 */
void draw1(const size_t row) {
    switch (row) {
        case 3:
            drawNum(" _ ");
            break;
        case 4: //
            drawNum("/ |");
            break;
        case 5:
        case 6:
            drawNum("| |");
            break;
        case 7:
            drawNum("|_|");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void draw2(const size_t row) {
    switch (row) {
        case 3:
            drawNum(" ____  ");
            break;
        case 4: //
            drawNum("|___ \\ ");
            break;
        case 5:
            drawNum("  __) |");
            break;
        case 6:
            drawNum(" / __/ ");
            break;
        case 7:
            drawNum("|_____|");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void draw3(const size_t row) {
    switch (row) {
        case 3:
            drawNum(" _____ ");
            break;
        case 4: //
            drawNum("|___ / ");
            break;
        case 5:
            drawNum("  |_ \\ ");
            break;
        case 6:
            drawNum(" ___) |");
            break;
        case 7:
            drawNum("|____/ ");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void draw4(const size_t row) {
    switch (row) {
        case 3:
            drawNum(" _  _   ");
            break;
        case 4: //
            drawNum("| || |  ");
            break;
        case 5:
            drawNum("| || |_ ");
            break;
        case 6:
            drawNum("|__   _|");
            break;
        case 7:
            drawNum("   |_|  ");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void draw5(const size_t row) {
    switch (row) {
        case 3:
            drawNum(" ____  ");
            break;
        case 4: //
            drawNum("| ___| ");
            break;
        case 5:
            drawNum("|___ \\ ");
            break;
        case 6:
            drawNum(" ___) |");
            break;
        case 7:
            drawNum("|____/ ");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void draw6(const size_t row) {
    switch (row) {
        case 3:
            drawNum("  __   ");
            break;
        case 4: //
            drawNum(" / /_  ");
            break;
        case 5:
            drawNum("| '_ \\ ");
            break;
        case 6:
            drawNum("| (_) |");
            break;
        case 7:
            drawNum(" \\___/ ");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void draw7(const size_t row) {
    switch (row) {
        case 3:
            drawNum(" _____ ");
            break;
        case 4: //
            drawNum("|___  |");
            break;
        case 5:
            drawNum("   / / ");
            break;
        case 6:
            drawNum("  / /  ");
            break;
        case 7:
            drawNum(" /_/   ");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void draw8(const size_t row) {
    switch (row) {
        case 3:
            drawNum("  ___  ");
            break;
        case 4: //
            drawNum(" ( _ ) ");
            break;
        case 5:
            drawNum(" / _ \\ ");
            break;
        case 6:
            drawNum("| (_) |");
            break;
        case 7:
            drawNum(" \\___/ ");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

/*
 * Board.h Functions
 */

Board *newBord(fstream &gmeFile, bool frmFile) {
    gmeFile.seekg(0, ios::beg);
    Board *board = new Board;

    board->whoTurn = PlyrClr::WHITE;
    board->check = PlyrClr::NONE;
    board->chkmte = PlyrClr::NONE;
    board->surndr = PlyrClr::NONE;
    board->exitGme = PlyrClr::NONE;
    board->stlemte = false;
    board->deadPos = false;

    if (frmFile) {
        read(gmeFile, board->whoTurn);
        read(gmeFile, board->check);
        read(gmeFile, board->chkmte);
        read(gmeFile, board->surndr);
        read(gmeFile, board->stlemte);
        read(gmeFile, board->deadPos);
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
    // Condition 1: Checks if only kings, bishops and knights remain
    for (int row{1}; row < board->VERTSZE - 1; row++) {
        for (int col{1}; col < board->HORZNSZ - 1; col++) {
            Piece *curPce{getPce(board, row, col)};
            if (curPce->pieceID != PieceID::KING && curPce->pieceID != PieceID::BISHOP && curPce->pieceID != PieceID::KNIGHT)
                return false;
        }
    }

    return true;
}

void drawBrd(const Board *const board) {
    static const size_t width{23};
    Piece *curPce;
    bool lghtCel;

    // Draw Board Numbers
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

/*
 * Coord.h Functions
 */

Coord *newCord(const char row, const char col) {
    Coord *tuple = new Coord;
    tuple->row = row;
    tuple->col = col;

    return tuple;
}

Coord *newCord(fstream &file) {
    Coord *tuple = new Coord;
    file.read(reinterpret_cast<char *>(tuple), sizeof(Coord));
    return tuple;
}

void toFile(fstream &file, Coord *coord) {
    file.write(reinterpret_cast<char *>(coord), sizeof(Coord));
}

Coord *fmChsNt(const string &pos) {
    return newCord(pos[1] - 48, toupper(pos[0]) - 64);
}

string toChsNt(const Coord *const pos) {
    string chsNot{static_cast<char>(pos->col + 64), static_cast<char>(pos->row + 48), '\0'};
    return chsNot;
}

void incrmnt(Coord *const val, const Coord *const by) {
    incrmnt(val, by->row, by->col);
}

void incrmnt(Coord *const val, const char row, const char col) {
    val->row += row;
    val->col += col;
}

Coord *copyCord(const Coord *const toCopy) {
    return newCord(toCopy->row, toCopy->col);
}

void dealloc(const Coord *coord) {
    if (coord != nullptr)
        delete coord;
    coord = nullptr;
}

bool lessThn(const Coord *const a, const Coord *const b) {
    return lessThn(a, b->row, b->col);
}

bool lessThn(const Coord *const a, const char bRow, const char bCol) {
    return a->row < bRow && a->col < bCol;
}

bool lessEq(const Coord *const a, const Coord *const b) {
    return lessEq(a, b->row, b->col);
}

bool lessEq(const Coord *const a, const char bRow, const char bCol) {
    return a->row <= bRow && a->col <= bCol;
}

bool isEqual(const Coord *const a, const Coord *b) {
    return isEqual(a, b->row, b->col);
}

bool isEqual(const Coord *const a, const char bRow, const char bCol) {
    return a->row == bRow && a->col == bCol;
}

/*
 * fileUtil.h Functions
 */
string getFPth(const string &comp1, const string &comp2) {
    string input{};
    cin >> input;
    // Make sure its just a filename, not a filepath
    if (input.find('.') == string::npos && input != comp1 && input != comp2) {
        cin.ignore();
        return input;
    }
    cout << "Invalid file, enter new filename: ";
    return getFPth(comp1, comp2);
}

void opnFile(fstream &file, const string &filePth, bool newFile) {
    if (newFile)
        file.open(filePth, ios::binary | ios::in | ios::out | ios::trunc);
    else {
        file.open(filePth, ios::binary | ios::in | ios::out);
        if (!file.is_open()) {
            cout << "File does not exist. Creating new file.\n";
            file.open(filePth, ios::binary | ios::in | ios::out | ios::trunc);
        } else
            file.seekg(0, ios::end);
    }
}

char *recast(bool &data) {
    return reinterpret_cast<char *>(&data);
}

void read(fstream &file, bool &data) {
    file.read(recast(data), sizeof(data));
}

void write(fstream &file, bool data) {
    file.write(recast(data), sizeof(data));
}

char *recast(PlyrClr &data) {
    return reinterpret_cast<char *>(&data);
}

void read(fstream &file, PlyrClr &data) {
    file.read(recast(data), sizeof(data));
}

void write(fstream &file, PlyrClr data) {
    file.write(recast(data), sizeof(data));
}

char *recast(unsigned short &data) {
    return reinterpret_cast<char *>(&data);
}

void read(fstream &file, unsigned short &data) {
    file.read(recast(data), sizeof(data));
}

void write(fstream &file, unsigned short data) {
    file.write(recast(data), sizeof(data));
}

char *recast(size_t &data) {
    return reinterpret_cast<char *>(&data);
}

void read(fstream &file, size_t &data) {
    file.read(recast(data), sizeof(data));
}

void write(fstream &file, size_t data) {
    file.write(recast(data), sizeof(data));
}

void read(fstream &file, string &data) {
    size_t nameLen{};
    read(file, nameLen);
    data.resize(nameLen);
    file.read(data.data(), nameLen * sizeof(data[0]));
}

void write(fstream &file, string data) {
    size_t nameLen{data.length()};
    write(file, nameLen);
    file.write(data.data(), nameLen * sizeof(data[0]));
}

/*
 * moveCalculations.h Functions
 */

void kingMov(const Board *const board, const bool tgtMode, const Coord *const initPos, Array *const data, const PlyrClr &player) {
    // Order: Top-Left (clockwise)
    static const Coord offsets[] = {Coord{-1, -1}, Coord{-1, 0}, Coord{-1, 1}, Coord{0, -1}, Coord{0, 1}, Coord{1, -1}, Coord{1, 0}, Coord{1, 1}};
    Piece *initPce{getPce(board, initPos)};

    for (size_t i{0}; i < sizeof(offsets) / sizeof(offsets[0]); i++) {
        Coord *curPos{copyCord(initPos)};
        incrmnt(curPos, &offsets[i]);

        if (!isOOB(curPos)) {
            Piece *tgtPce{getPce(board, curPos)};
            if (tgtMode) {
                if (tgtChk(false, initPce, tgtPce, player)) {
                    if (tgtPce->pieceID == PieceID::KING)
                        appDta(data, curPos);
                }
            } else {
                // Not in target mode: checking if the piece can move to the final position
                if (vldPcMv(board, initPce, curPos))
                    appDta(data, curPos);
            }
        }
        dealloc(curPos);
    }
}

void lineMov(const Board *const board, const bool tgtMode, const bool intrpse, const Coord *const initPos, Array *const data, const PlyrClr &player) {
    // Order: Up, Down, Left, Right
    static const Coord offsets[] = {Coord{-1, 0}, Coord{1, 0}, Coord{0, -1}, Coord{0, 1}};
    Piece *initPce{getPce(board, initPos)};

    for (size_t i{0}; i < sizeof(offsets) / sizeof(offsets[0]); i++) {
        Coord *curPos{walkPth(board, initPos, offsets[i].row, offsets[i].col)};
        if (!tgtMode) {
            Array *path{calcPth(board, initPos, curPos)};
            appDta(data, path);
            dealloc(path);
        }
        if (!isOOB(curPos)) {
            Piece *tgtPce{getPce(board, curPos)};
            if (tgtMode) {
                if (tgtChk(intrpse, initPce, tgtPce, player)) {
                    if (tgtPce->pieceID == PieceID::QUEEN || tgtPce->pieceID == PieceID::ROOK)
                        appDta(data, curPos);
                }
            } else {
                // Not in target mode: checking if the piece can move to the target location
                if (vldPcMv(board, getPce(board, initPos), curPos))
                    appDta(data, curPos);
            }
        }
        dealloc(curPos);
    }
}

void diagMov(const Board *const board, const bool tgtMode, const bool intrpse, const Coord *const initPos, Array *const data, const PlyrClr &player) {
    // Order: Top-Left, Top-Right, Bottom-Left, Bottom-Right
    static const Coord offsets[] = {Coord{-1, -1}, Coord{-1, 1}, Coord{1, -1}, Coord{1, 1}};
    Piece *initPce{getPce(board, initPos)};

    for (size_t i{0}; i < sizeof(offsets) / sizeof(offsets[0]); i++) {
        Coord *curPos{walkPth(board, initPos, offsets[i].row, offsets[i].col)};
        if (!tgtMode) {
            Array *path{calcPth(board, initPos, curPos)};
            appDta(data, path);
            dealloc(path);
        }
        if (!isOOB(curPos)) {
            Piece *tgtPce{getPce(board, curPos)};
            if (tgtMode) {
                if (tgtChk(intrpse, initPce, tgtPce, player)) {
                    if (tgtPce->pieceID == PieceID::QUEEN || tgtPce->pieceID == PieceID::BISHOP)
                        appDta(data, curPos);
                }
            } else {
                // Not in target mode: checking if the piece can move to the final position
                if (vldPcMv(board, getPce(board, initPos), curPos))
                    appDta(data, curPos);
            }
        }
        dealloc(curPos);
    }
}

void knitMov(const Board *const board, const bool tgtMode, const bool intrpse, const Coord *const initPos, Array *const data, const PlyrClr &player) {
    // Order: Top-Left (clockwise)
    static const Coord offsets[] = {Coord{-2, -1}, Coord{-2, 1}, Coord{-1, 2}, {1, 2}, Coord{2, 1}, Coord{2, -1}, Coord{1, -2}, Coord{-1, -2}};
    Piece *initPce{getPce(board, initPos)};

    for (int i{0}; i < sizeof(offsets) / sizeof(offsets[0]); i++) {
        Coord *curPos{copyCord(initPos)};
        incrmnt(curPos, &offsets[i]);
        if (!isOOB(curPos)) {
            Piece *tgtPce{getPce(board, curPos)};
            if (tgtMode) {
                if (tgtChk(intrpse, initPce, tgtPce, player)) {
                    if (tgtPce->pieceID == PieceID::KNIGHT)
                        appDta(data, curPos);
                }
            } else {
                // Not in target mode: checking if the piece can move to the final position
                if (vldPcMv(board, initPce, curPos))
                    appDta(data, curPos);
            }
        }
        dealloc(curPos);
    }
}

void pawnMov(const Board *const board, const bool tgtMode, const bool intrpse, const Coord *const initPos, Array *const data, const PlyrClr &player) {
    // {+-2, 0} offsets are calculated if the pawn has not moved yet
    // Order: (White) 2 Space Forward, 1 Space Forward, Diagonal Left, Diagonal Right, (Black) Diagonal Right, Diagonal Left, 1 Space Forward, 2 Space Forward
    static const Coord offsets[] = {Coord{-2, 0}, Coord{-1, 0}, Coord{-1, -1}, Coord{-1, 1}, Coord{1, -1}, Coord{1, 1}, Coord{1, 0}, Coord{2, 0}};
    const Piece *const initPce{board->board[initPos->row][initPos->col]};
    Coord *curPos;
    size_t start;
    size_t end;


    // tgtMode does not need to account for forward (one or two space) because pawns cannot capture forward and cannot move forward to a space if there is a piece occupying that space
    if (tgtMode) {
        start = player == PlyrClr::WHITE ? 2 : 4;
        end = player == PlyrClr::WHITE ? 4 : 6;

        for (size_t i{start}; i < end; i++) {
            curPos = copyCord(initPos);
            incrmnt(curPos, &offsets[i]);
            Piece *tgtPce{getPce(board, curPos)};
            if (!isOOB(curPos) && tgtChk(intrpse, initPce, tgtPce, player))
                if (tgtPce->pieceID == PieceID::PAWN)
                    appDta(data, curPos);
            dealloc(curPos);
        }
    } else {
        // Not in target mode: checking if the piece can move to the final position
        start = initPce->pceClr == PlyrClr::WHITE ? (initPce->fstMove ? 0 : 1) : 4;
        end = initPce->pceClr == PlyrClr::WHITE ? 4 : (initPce->fstMove ? 8 : 7);
        size_t diagSta = initPce->pceClr == PlyrClr::WHITE ? 2 : 4;
        size_t strStrt = initPce->pceClr == PlyrClr::WHITE ? start : 6;
        size_t strEnd = initPce->pceClr == PlyrClr::WHITE ? 2 : end;
        for (size_t i{start}; i < end; i++) {
            curPos = copyCord(initPos);
            incrmnt(curPos, &offsets[i]);
            if (vldPcMv(board, getPce(board, initPos), curPos)) {
                // If checking diagonals
                if (i >= diagSta && i < diagSta + 2) {
                    if (!getPce(board, curPos)->empty && getPce(board, curPos)->pceClr != initPce->pceClr)
                        appDta(data, curPos);
                } else if (i >= strStrt && i < strEnd) {
                    // If checking straight line paths
                    if (getPce(board, curPos)->empty)
                        appDta(data, curPos);
                } else
                // Normal Checks
                    appDta(data, curPos);
            }
            dealloc(curPos);
        }
    }
}

void castle(const Board *const board, const Coord *const initPos, Array *const data) {
    static const Coord offsets[] = {Coord{8, 1}, Coord{8, 3}, Coord{8, 8}, Coord{8, 7}, Coord{1, 1}, Coord{1, 3}, Coord{1, 8}, Coord{1, 7}};
    Piece *initPce{board->board[initPos->row][initPos->col]};

    if (initPce->pieceID == PieceID::KING && initPce->fstMove) {
        size_t start = initPce->pceClr == PlyrClr::WHITE ? 0 : 4;
        size_t end = initPce->pceClr == PlyrClr::WHITE ? 4 : 8;
        for (size_t i{start}; i < end; i += 2) {
            Piece *offPce{getPce(board, &offsets[i])};
            if (offPce->pieceID == PieceID::ROOK && offPce->fstMove && sfeSpce(board, &offsets[i + 1], initPce->pceClr) && unObPth(board, initPos, &offsets[i]))
                appDta(data, &offsets[i + 1]);
        }
    }
}

bool pceIntr(const Board *const board, const Coord *const kingPos, const Coord *const enmyPos, Array *const pceLoc, Array *const toWhere, const PlyrClr &player) {
    //If the positions are the same
    if (isEqual(kingPos, enmyPos))
        return false;

    // Checks if a valid path exists between the two points
    if (!unObPth(board, kingPos, enmyPos))
        return false;

    Array *path = calcPth(board, kingPos, enmyPos);
    for (int i{0}; i < path->utilSze; i++) {
        size_t initSze{pceLoc->utilSze};
        lineMov(board, true, true, path->data[i], pceLoc, player);
        diagMov(board, true, true, path->data[i], pceLoc, player);
        size_t fnlSize{pceLoc->utilSze};

        // Interposing pieces were found
        if (fnlSize > initSze)
            for (size_t j{0}; j < fnlSize - initSze; appDta(toWhere, path->data[i]), j++);
    }


    dealloc(path);
    return !pceLoc->empty;
}

bool sfeSpce(const Board *const board, const Coord *const tgtPos, const bool iposeMde, Array *const data, const PlyrClr &player) {
    bool isSafe;

    kingMov(board, true, tgtPos, data, player);
    lineMov(board, true, iposeMde, tgtPos, data, player);
    diagMov(board, true, iposeMde, tgtPos, data, player);
    knitMov(board, true, iposeMde, tgtPos, data, player);
    pawnMov(board, true, iposeMde, tgtPos, data, player);

    isSafe = data->empty;
    return isSafe;
}

bool sfeSpce(const Board *const board, const Coord *const tgtPos, const PlyrClr &player) {
    Array *posData{newArry()};
    bool isSafe{sfeSpce(board, tgtPos, false, posData, player)};
    dealloc(posData);
    return isSafe;
}

Array *sfeMves(const Board *board, const Coord *kingPos) {
    Array *vldMves{newArry()};
    Array *whoChk{newArry()};

    Piece *kingPce{getPce(board, kingPos)};

    // Determines the locations of the pieces that are putting the king in check
    sfeSpce(board, kingPos, false, whoChk, kingPce->pceClr);

    // Determine which spaces the king can move to, not yet accounting for spaces where the king would still be in check
    kingMov(board, false, kingPos, vldMves);

    // Eliminate surrounding spaces the king cannot move to, accounting for ones where the king would still be in check
    if (!vldMves->empty) {
        for (size_t i{vldMves->utilSze - 1}; i > 0; i--)
            if (!sfeSpce(board, vldMves->data[i], kingPce->pceClr))
                pop(vldMves, i);
        if (!sfeSpce(board, vldMves->data[0], kingPce->pceClr))
            pop(vldMves, 0);
    }

    dealloc(whoChk);
    return vldMves;
}

bool stlmte(const Board *board, const PlyrClr player) {
    Coord *curCord;
    Array *vldMves;
    Piece *curPce;
    for (size_t row{1}; row < board->VERTSZE - 1; row++)
        for (size_t col{1}; col < board->HORZNSZ - 1; col++) {
            curCord = newCord(row, col);
            curPce = getPce(board, curCord);
            vldMves = newArry(10);
            if (curPce->pceClr == player) {
                switch (curPce->pieceID) {
                    case PieceID::KING:
                        vldMves = sfeMves(board, curCord);
                        break;
                    case PieceID::QUEEN:
                        lineMov(board, false, false, curCord, vldMves);
                        diagMov(board, false, false, curCord, vldMves);
                        break;
                    case PieceID::ROOK:
                        lineMov(board, false, false, curCord, vldMves);
                        break;
                    case PieceID::BISHOP:
                        diagMov(board, false, false, curCord, vldMves);
                        break;
                    case PieceID::KNIGHT:
                        knitMov(board, false, false, curCord, vldMves);
                        break;
                    case PieceID::PAWN:
                        pawnMov(board, false, false, curCord, vldMves);
                        break;
                }
                if (!vldMves->empty) {
                    dealloc(curCord);
                    dealloc(vldMves);
                    return false;
                }
            }
            dealloc(curCord);
            dealloc(vldMves);
        }
    return true;
}

Array *calcPth(const Board *const board, const Coord *const initPos, const Coord *const tgtPos, const bool incBnds) {
    Array *path = newArry();

    if (initPos != tgtPos) {
        const Coord *start{nullptr};
        const Coord *end{nullptr};
        Coord *incAmt{nullptr};
        Piece *curPce{nullptr};
        Coord *curPos{nullptr};

        if (abs(initPos->row - tgtPos->row) == abs(initPos->col - tgtPos->col)) {
            // Diagonal Path
            start = initPos->row > tgtPos->row ? tgtPos : initPos;
            end = initPos->row > tgtPos->row ? initPos : tgtPos;
            incAmt = start->row < end->row && start->col > end->col ? newCord(1, -1) : newCord(1, 1);
        } else if (initPos->row == tgtPos->row) {
            // Horizontal Path
            start = lessEq(initPos, tgtPos) ? initPos : tgtPos;
            end = lessEq(initPos, tgtPos) ? tgtPos : initPos;
            incAmt = newCord(0, 1);
        } else if (initPos->col == tgtPos->col) {
            // Vertical Path
            incAmt = newCord(1, 0);
            start = lessEq(initPos, tgtPos) ? initPos : tgtPos;
            end = lessEq(initPos, tgtPos) ? tgtPos : initPos;
        }
        if (incAmt != nullptr) {
            if (incBnds & !isOOB(start))
                appDta(path, start);

            curPos = copyCord(start);
            incrmnt(curPos, incAmt);
            curPce = getPce(board, curPos);
            while (!isOOB(curPos) && !isEqual(curPos, end) && curPce->empty) {
                appDta(path, curPos);
                incrmnt(curPos, incAmt);
                curPce = getPce(board, curPos);
            }
            if (incBnds && !isOOB(end))
                appDta(path, end);

        }
        dealloc(incAmt);
        dealloc(curPos);
    }
    return path;
}


Coord *walkPth(const Board *const board, const Coord *const initPos, const char rowOfst, const char colOfst) {
    Coord *curPos{copyCord(initPos)};
    Piece *tgtPce;

    do {
        incrmnt(curPos, rowOfst, colOfst);
        tgtPce = getPce(board, curPos);
    } while (!isOOB(curPos) && tgtPce->empty);

    return curPos;
}


bool unObPth(const Board *const board, const Coord *const initPos, const Coord *const tgtPos) {
    if (initPos == tgtPos)
        return true;

    const Coord *start{lessEq(initPos, tgtPos) ? initPos : tgtPos};
    const Coord *end{lessEq(initPos, tgtPos) ? tgtPos : initPos};
    Array *path = calcPth(board, initPos, tgtPos, true);
    bool uobsPth{false};

    if (!path->empty)
        uobsPth = isEqual(path->data[0], start) && isEqual(path->data[path->utilSze - 1], end);

    dealloc(path);
    return uobsPth;
}

bool vldMove(const Coord *const coord, const Array *const vldMves) {
    for (int i{0}; i < vldMves->utilSze; i++)
        if (isEqual(vldMves->data[i], coord))
            return true;
    return false;
}

bool vldPcMv(const Board *const board, const Piece *const init, const Coord *const curPos) {
    Piece *tgt{getPce(board, curPos)};
    return !isOOB(curPos) && (tgt->empty || tgt->pceClr != init->pceClr);
}

bool tgtChk(const bool intrpse, const Piece *const init, const Piece *const tgt, const PlyrClr &player) {
    /*
     * For interpose mode, three criteria must be met
     * 1. The target space must not be empty
     * 2. The piece at the target space must be the player's piece
     * 3. The initial position must be empty
     */

    /*
     * For target mode, these criteria must be met
     * 1. The target space must not be empty
     * 2. The target space must be an enemy piece
     */
    if (intrpse)
        return !tgt->empty && init->empty && tgt->pceClr == player;
    return !tgt->empty && tgt->pceClr != player;
}

/*
 * Piece.h Functions
 */
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

/*
 * Player.h Functions
 */
Player *newPlyr(fstream &file, const bool frmFile, const size_t plrNum) {
    Player *player = new Player;
    if (frmFile) {
        file.seekp(0, ios::beg);
        read(file, player->nWins);
        read(file, player->nWins);
        read(file, player->name);
    } else {
        bool vldInpt{true};
        player->nWins = 0;
        player->nLoss = 0;
        cout << "Player " << plrNum << ", enter your name (a-z, A-Z, and space only): ";
        getline(cin, player->name);
        do {
            vldInpt = true;
            for (size_t i{0}; i < player->name.length(); i++)
                if (!(toupper(player->name[i]) >= 65 && toupper(player->name[i]) <= 90) && player->name[i] != 32)
                    vldInpt = false;

            if (!vldInpt) {
                cout << "Invalid name, enter new name: ";
                getline(cin, player->name);
            }
        } while (!vldInpt);
    }
    return player;
}

void toFile(fstream &file, Player *player) {
    file.seekp(0, ios::beg);
    write(file, player->nWins);
    write(file, player->nLoss);
    write(file, player->name);
}

void ptPlrSt(const Player *const plyr1, const Player *const plyr2) {
    cout << "\n\n";
    cout << plyr1->name << "'s Stats: \n";
    cout << "# Wins: " << plyr1->nWins << '\n';
    cout << "# Losses: " << plyr1->nLoss << '\n';

    cout << plyr2->name << "'s Stats: \n";
    cout << "# Wins: " << plyr2->nWins << '\n';
    cout << "# Losses: " << plyr2->nLoss << '\n';
    cout << "\n\n";
}

void dealloc(Player *player) {
    if (player != nullptr)
        delete player;
    player = nullptr;
}