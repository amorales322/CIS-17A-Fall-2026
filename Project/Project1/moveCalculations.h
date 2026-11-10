#ifndef MOVECALCULATIONS_H
#define MOVECALCULATIONS_H

#include "Board.h"

/*
 * Move Calculation Functions
 */

/* King move does not need target or interpose modes because:
 * 1. Target mode for each piece type is covered with the other functions
 * 2. A piece cannot interpose between adjacent pieces
 */
void kingMov(const Board *, const Coord *, Array *);

/*
 * These Functions have three modes
 * 1. Default mode: Returns an array of all positions the piece can move to along a path
 * 2. Target Mode Enabled: Searches along the specified path and returns an array of all pieces along that path that can return to the initial position
 * 3. Target & Interpose Mode Enabled: Searches like target mode, but checks if any pieces on the board can reach a point along the path, and returns the positions of those pieces
 */

void lineMov(const Board *, bool, bool, const Coord *, Array *, const PlyrClr &);

void diagMov(const Board *, bool, bool, const Coord *, Array *, const PlyrClr &);

void knitMov(const Board *, bool, bool, const Coord *, Array *, const PlyrClr &);

void pawnMov(const Board *, bool, bool, const Coord *, Array *, const PlyrClr &);

// Target mode not needed, castling only works with kings
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
bool pceIntr(const Board *board, const Coord *kingPos, const Coord *enmyPos, Array *canIPos, Array *iposWhr);


/*
 * Determines if the specified space is safe and returns the position
 * This function has two modes:
 * 1. Interpose Mode Disabled: Calculates if any of the enemy's pieces can reach the target location
 * 2. Interpose Mode Enabled: Calculates if any of the players pieces can reach the target location
 */

bool sfeSpce(const Board *, const Coord *, bool, Array *);

bool sfeSpce(const Board *, const Coord *);

Array *calcPth(const Board *, const Coord *, const Coord *, bool = false);

/*
 * Walks a straight line path between two points until it goes out of bounds or stops at a piece, and returns the final position
 */
Coord *walkPth(const Board *, const Coord *, unsigned char, unsigned char);


/*
 * Determines if the direct path between two points is a straight line and if there is no obstructions along the path
 */
bool unObPth(const Board *, const Coord *, const Coord *);

bool vldMove(const Coord *, const Array *);

bool vldPcMv(const Board *, const Piece *, const Coord *);

bool tgtChk(bool, const Piece *, const Piece *, const PlyrClr &);

#endif
