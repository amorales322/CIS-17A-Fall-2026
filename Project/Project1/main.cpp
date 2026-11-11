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
// Contains function prototypes - will be removed and included here for my final submission
#include "Array.h"
#include "Coord.h"
#include "moveCalculations.h"
#include "Piece.h"
#include "PlyrClr.h"
#include "Board.h"
#include "PieceID.h"


// Global Constants not Variables
// Science, Math, Conversions, Dimensions

// Function Prototypes

// Execution begins here at main
int main(int argc, char **argv) {
    // Set random number seed
    // for (size_t i{0}; i < 14; i++) {
    //     drwQuen(true, i, PlyrClr::WHITE);
    //     cout << "|\n";
    // }
    // cout << "\n\n";
    // for (size_t i{0}; i < 14; i++) {
    //     drwQuen(true, i, PlyrClr::BLACK);
    //     cout << "|\n";
    // }
    // Declare Variables

    Board *board = newBord();
    drawBrd(board);
    // board->check = PlyrClr::WHITE;
    // board->white = newPlyr();
    // board->black = newPlyr();
    //
    // // User inputs
    // Coord *tgtPce;
    // Coord *whereTo;
    //
    // // Which pieces can move, if limited in some way
    // Array *canMove{newArry()};
    // // Valid positions a piece can move to
    // Array *vldMves{newArry()};
    //
    // // Stores which pieces are putting the king in Check
    // Array *whoChk{newArry()};
    //
    // /*
    //  * These are parallel arrays
    //  */
    // // Stores the location(s) of piece(s) that can interpose between an enemy piece and the king
    // Array *canIPos{newArry()};
    // // Stores the location(s) of where piece(s) can go to in order to interpose
    // Array *iPosePs{newArry()};
    //
    // do {
    //     drawBrd(board);
    //
    //     board->deadBrd = deadBrd(board);
    //     if (!board->deadBrd) {
    //         // White Turn
    //         if (board->whoTurn == PlyrClr::WHITE) {
    //             // If the king is in check
    //             if (board->check == PlyrClr::WHITE) {
    //                 vldMves = sfeMves(board, board->wKngPos);
    //
    //                 // If no safe spaces remain after this elimination process ends, the game ends
    //                 if (vldMves->empty)
    //                     board->chkmte = PlyrClr::WHITE;
    //                 else
    //                     appDta(canMove, board->wKngPos);
    //
    //                 // If the king is just in check and not in checkmate
    //                 if (board->chkmte == PlyrClr::NONE) {
    //                     // Two scenarios can occur
    //                     // 1. If the king is in check by one piece, then a piece can potentially interpose between the king and the enemy piece, and we calculate this
    //                     // 2. If the king is in check by multiple pieces, then no piece cannot interpose between the multiple pieces and the king, and we just skip to the player input
    //                     if (whoChk->utilSze == 1) {
    //                         pceIntr(board, board->wKngPos, vldMves->data[0], canIPos, iPosePs, PlyrClr::WHITE);
    //                         if (!canIPos->empty)
    //                             appDta(canMove, canIPos);
    //                     }
    //
    //                     /*
    //                      * Get piece to move
    //                      */
    //                     cout << "Enter which piece you would like to move";
    //                     if (!canMove->empty) {
    //                         cout << " (Can move: ";
    //                         pntArry(canMove);
    //                         cout << "): ";
    //                     } else
    //                         cout << ": ";
    //                     tgtPce = getInpt();
    //
    //                     while (!vldMove(tgtPce, canMove)) {
    //                         cout << "Cannot move this piece at the moment, select a new piece to move: ";
    //                         dealloc(tgtPce);
    //                         tgtPce = getInpt();
    //                     }
    //
    //                     /*
    //                      * Get where to move piece
    //                      */
    //                     cout << "Where would you like to move your " << getName(board, tgtPce) << " to: ";
    //                     whereTo = getInpt();
    //
    //                     // If king is selected
    //                     if (search(canMove, tgtPce) == 0) {
    //                         while (!vldMove(whereTo, vldMves)) {
    //                             cout << "Cannot move your " << getName(board, tgtPce) << " here, enter new spot to move your " << getName(board, tgtPce) << " to: ";
    //                             dealloc(whereTo);
    //                             whereTo = getInpt();
    //                         }
    //                     } else {
    //                         // While the target location is not the valid location the interposing piece can move to
    //                         while (!isEqual(whereTo, iPosePs->data[search(canIPos, tgtPce)])) {
    //                             cout << "Cannot move your " << getName(board, tgtPce) << " here, enter new spot to move your " << getName(board, tgtPce) << " to: ";
    //                             dealloc(whereTo);
    //                             whereTo = getInpt();
    //                         }
    //                     }
    //                 }
    //             } else {
    //                 /*
    //                  * Regular move
    //                  */
    //
    //                 // Calculate stalemate
    //
    //                 // if (!board->stlemte) {
    //                 //     if (board->check == WHITE) {
    //                 //         if (whoChk->utilSze > 1) {
    //                 //             // King only
    //                 //         } else if (vldMves->utilSze == 1 && canIPos->utilSze >= 1) {
    //                 //             // Interposing pieces
    //                 //         } else if (vldMves->utilSze > 1) {
    //                 //             // King + interposing pieces
    //                 //         }
    //                 //     } else {
    //                 //         // Any Piece
    //                 //     }
    //                 // }
    //             }
    //         } else {
    //         }
    //     }
    //
    //     dealloc(tgtPce);
    //     dealloc(whereTo);
    //     dealloc(vldMves);
    //     dealloc(canMove);
    //     dealloc(whoChk);
    //     dealloc(iPosePs);
    //     dealloc(canIPos);
    // } while (board->chkmte != PlyrClr::NONE && !board->stlemte && !board->deadBrd);

    // Initialize Variables

    // Map/Process the Inputs -> Outputs

    // Display Inputs/Outputs

    // Clean up memory and files
    // dealloc(board);

    // Exit the Program
    return 0;
}
