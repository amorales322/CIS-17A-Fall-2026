#ifndef COORD_H
#define COORD_H

#include <string>
using namespace std;

struct Coord {
    char row;
    char col;
};


Coord *newCord(unsigned char, unsigned char);

Coord *fmChsNt(const string &);

string toChsNt(const Coord *);

void incrmnt(Coord *, const Coord *);
void incrmnt(Coord *, char, char);

Coord *copyCord(const Coord *);

void dealloc(const Coord *);

/*
 * Comparison Functions
 */

bool lessThn(const Coord *, const Coord *);

bool lessThn(const Coord *, unsigned char, unsigned char);

bool lessEq(const Coord *, const Coord *);

bool lessEq(const Coord *, unsigned char, unsigned char);

bool isEqual(const Coord *, const Coord *);

bool isEqual(const Coord *, unsigned char, unsigned char);


#endif
