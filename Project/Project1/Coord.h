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

Coord *cpyCord(const Coord *);

// File Writer
void toFile(fstream &, Coord *);

// Converts from chess notation to Coord struct
Coord *fmChsNt(const string &);

// Converts from Coord struct to chess notation
string toChsNt(const Coord *);

// Adds two coordinates together
void add(Coord *, const Coord *);
void add(Coord *, char, char);

void dealloc(Coord *);

/*
 * Comparison Functions
 */

bool lessEq(const Coord *, const Coord *);

bool lessEq(const Coord *, char, char);

bool isEqual(const Coord *, const Coord *);

bool isEqual(const Coord *, char, char);


#endif
