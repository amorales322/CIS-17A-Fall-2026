#ifndef MOVECALCULATIONS_H
#define MOVECALCULATIONS_H

#include "Board.h"

/*
 * King move does not need target or interpose modes because:
 * 1. Target mode for each piece type is covered with the other functions
 * 2. A piece cannot interpose between adjacent pieces
 */
void kingMov(const Board *, const Coord *, Array *);

/*
 * These Functions have three modes
 * 1. Default mode: Returns an array of all positions the piece can move to along a path
 * 2. Target Mode Enabled: Searches along the specified path and returns an array of all enemy piece positions that can reach the initial position
 * 3. Target & Interpose Mode Enabled: Searches along the specified path and returns an array of all player piece positions that can reach the initial position
 *
 * Returns: Array of all piece positions that can reach the initial location
 */
void lineMov(const Board *, bool, bool, const Coord *, Array *, const PlyrClr & = NONE);

void diagMov(const Board *, bool, bool, const Coord *, Array *, const PlyrClr & = NONE);

void knitMov(const Board *, bool, bool, const Coord *, Array *, const PlyrClr & = NONE);

void pawnMov(const Board *, bool, bool, const Coord *, Array *, const PlyrClr & = NONE);

// Target & Interpose modes not needed, castling only applies to the king
void castle(const Board *, const Coord *, Array *);

/*
 * Walks the path between the king piece and the checking piece, checks if any piece can interpose between the two pieces, and saves the location(s) of the pieces
 *
 * Ignores:
 * Pawn: A piece cannot interpose between adjacent pieces
 * Knight: Can jump over other pieces
 * Surrounding Spaces: A piece cannot interpose between two adjacent pieces
 *
 * Returns: false if there is no straight line path between the king piece and the enemy piece
 */
bool pceIntr(const Board *board, const Coord *kingPos, const Coord *enmyPos, Array *canIPos, Array *iposWhr, const PlyrClr &);


/*
 * Determines if the specified space is safe.
 * This function has two modes:
 * 1. Interpose Mode Disabled: Calculates if any of the enemy's pieces can reach the target location
 * 2. Interpose Mode Enabled: Calculates if any of the players pieces can reach the target location
 *
 * Returns: If the specified space is safe & array of pieces that can reach the target location
 */

bool sfeSpce(const Board *, const Coord *, bool, Array *, const PlyrClr &);

/*
 * Determines if the specified space is safe.
 *
 * Returns: If the specified space is safe
 */
bool sfeSpce(const Board *, const Coord *, const PlyrClr &);

/*
 * Calculates a straight line path between two points. Bounds default to exclusive.
 *
 * Returns: Empty array if there is no straight line path between the two points, or an array of all points along the path.
 *
 */
Array *calcPth(const Board *, const Coord *, const Coord *, bool = false);

/*
 * Walks a straight line path between two points until it goes out of bounds or stops at a piece, and returns the final position
 *
 * Returns: The final position along the path
 */
Coord *walkPth(const Board *, const Coord *, char, char);


/*
 * Determines if the direct path between two points is a straight line and if there is no obstructions along the path
 */
bool unObPth(const Board *, const Coord *, const Coord *);

/*
 * Checks a specific move against an array of valid positions to move to.
 */
bool vldMove(const Coord *, const Array *);

/*
 * Checks if a piece can move to a new position.
 */
bool vldPcMv(const Board *, const Piece *, const Coord *);

/*
 * Check used for target mode.
 */
bool tgtChk(bool, const Piece *, const Piece *, const PlyrClr &);

#endif
