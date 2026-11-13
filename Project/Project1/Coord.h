/*
* File:   Coord.h
 * Author: Anthony Morales
 * Created on October 24, 2026, 1:54 PM
 * Purpose:  Project 1 - Chess
 */

#ifndef COORD_H
#define COORD_H
struct Coord {
    char row;
    char col;
};

/*
 * Allocators
 */
Coord *newCord(char, char);

Coord *newCord(fstream &);

Coord *copyCord(const Coord *);

// File Writer
void toFile(fstream &, Coord *);

// Converts from chess notation to Coord struct
Coord *fmChsNt(const string &);

// Converts from Coord struct to chess notation
string toChsNt(const Coord *);

// Increments a coordinate by some value
void incrmnt(Coord *, const Coord *);
void incrmnt(Coord *, char, char);

void dealloc(const Coord *);

/*
 * Comparison Functions
 */

bool lessThn(const Coord *, const Coord *);

bool lessThn(const Coord *, char, char);

bool lessEq(const Coord *, const Coord *);

bool lessEq(const Coord *, char, char);

bool isEqual(const Coord *, const Coord *);

bool isEqual(const Coord *, char, char);


#endif
