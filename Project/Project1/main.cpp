/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 24, 2026, 1:54 PM
 * Purpose:  Project 1 - Chess
 */

// System Libraries
#include <iostream> // Input Output Library
#include <fstream>  // File Stream Library
using namespace std;

// User Libraries
// Contains function prototypes - will be removed and included here for my final submission
#include "Array.h"
#include "Coord.h"
#include "moveCalculations.h"
#include "Piece.h"
#include "PlyrClr.h"
#include "Board.h"
#include "PieceID.h"
#include "ASCII.h"


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
    cout << "Would you like to load data from a save file?: ";
    inpt = getOpt();
    if (inpt) {
        // Game Save
        cout << "Enter the filename for the game save you would like to load: ";
        flePth1 = getFPth();
        opnFile(gameDta, flePth1);

        // Player 1
        cout << "Enter the filename for player 1's data that you would like to load: ";
        flePth2 = getFPth(flePth1);
        opnFile(plyr1, flePth2);

        // Player 2
        cout << "Enter the filename for player 2's data that you would like to load: ";
        flePth3 = getFPth(flePth1, flePth2);
        opnFile(plyr2, flePth3);
    } else {
        cout << "Enter the filename for the game save you would like to save to: ";
        flePth1 = getFPth();
        opnFile(gameDta, flePth1, true);

        cout << "Enter the filename for player 1's data that you would like to save to: ";
        flePth2 = getFPth(flePth1);
        opnFile(plyr1, flePth2, true);

        // Player 2
        cout << "Enter the filename for player 2's data that you would like to save to: ";
        flePth3 = getFPth(flePth1, flePth2);
        opnFile(plyr2, flePth3, true);
    }

    // Initialize Board & Player
    Board *board{newBord(gameDta, plyr1, plyr2, inpt)};


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
    do {
        /*
         * Main Game Loop
         */
        do {
            drawBrd(board);
            board->deadPos = deadPos(board);
            if (!board->deadPos) {
                // if (board->whoTurn == PlyrClr::WHITE) {
                if (board->check == board->whoTurn) {
                    // Do not generalize - Conditional Based on who's turn it is
                    if (board->check == PlyrClr::WHITE)
                        vldMves = sfeMves(board, board->wKngPos);
                    else
                        vldMves = sfeMves(board, board->bKngPos);

                    // If no safe spaces remain after this elimination process ends, the game ends
                    if (vldMves->empty)
                        board->chkmte = board->whoTurn;
                    else
                        // Do not generalize - Conditional Based on who's turn it is
                        if (board->whoTurn == PlyrClr::WHITE)
                            appDta(canMove, board->wKngPos);
                        else
                            appDta(canMove, board->bKngPos);

                    // If the king is just in check and not in checkmate
                    if (board->chkmte == PlyrClr::NONE) {
                        // Two scenarios can occur
                        // 1. If the king is in check by one piece, then a piece can potentially interpose between the king and the enemy piece, and we calculate this
                        // 2. If the king is in check by multiple pieces, then no piece cannot interpose between the multiple pieces and the king, and we just skip to the player input
                        if (whoChk->utilSze == 1) {
                            // Do not generalize - Conditional Based on who's turn it is
                            if (board->whoTurn == PlyrClr::WHITE)
                                pceIntr(board, board->wKngPos, vldMves->data[0], canIPos, iPosePs, board->whoTurn);
                            else
                                pceIntr(board, board->bKngPos, vldMves->data[0], canIPos, iPosePs, board->whoTurn);
                            if (!canIPos->empty)
                                appDta(canMove, canIPos);
                        }

                        // Get Piece to Move
                        // Do not generalize - Conditional Based on who's turn it is
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
                            cout << "Where would you like to move your " << getName(board, tgtPce) << " to: ";
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
                    /*
                     * REGULAR TURN
                     */
                    // Do not generalize - Conditional Based on who's turn it is
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
                        // Do not generalize - Conditional Based on who's turn it is
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
                    // Do not generalize - Conditional Based on who's turn it is
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

                    clrScrn();
                    clear(canMove);
                    clear(vldMves);
                    clear(whoChk);
                    clear(canIPos);
                    clear(iPosePs);
                    // Do not generalize - Conditional Based on who's turn it is
                    board->whoTurn = board->whoTurn == PlyrClr::WHITE ? PlyrClr::BLACK : PlyrClr::WHITE;
                }
            }
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

    // Clean up memory and files
    cout << "Saving game...\n";
    toFile(gameDta, plyr1, plyr2, board);


    dealloc(tgtPce);
    dealloc(whereTo);
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
