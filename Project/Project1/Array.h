#ifndef ARRAY_H
#define ARRAY_H

#include "Coord.h"
#include "Board.h"

#include <iostream>
using namespace std;

struct Array {
    Coord **data;
    unsigned int size;
    unsigned int utilSze;
    bool empty;
};

Array *newArry(size_t = 15);

void pntArry(const Array *);

void cpyArry(Array *, const Array *);

/*
 * Element Modifiers
 * Note: Creates a copy of the elements, does not insert duplicate elements
 */


void appDta(Array *, const Coord *);

// Todo: Fix to not insert duplicates
void appDta(Array *, const Array *);

void pop(Array *, int);


/*
 * Capacity Modifiers
 */
void resize(Array *, int = -1);

void clear(Array *);

void shrink(Array *);

void dealloc(Array *);


/*
 * Serach Functions
 */
int search(const Array *, const Coord *);


#endif
