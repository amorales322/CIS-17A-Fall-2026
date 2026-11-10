#ifndef ARRAY_H
#define ARRAY_H

#include "Coord.h"

#include <cstddef>

struct Array {
    Coord **data;
    unsigned int size;
    unsigned int utilSze;
};

Array *newArry(size_t);

void cpyArry(Array *, const Array *);

/*
 * Element Modifiers
 * Notes: Creates a copy of the elements, does not insert duplicate elements
 */

void appDta(Array *, const Coord *);

void appDta(Array *, const Array *);

void pop(Array *, int);


/*
 * Capacity Modifiers
 */
void resize(Array *, size_t = 0);

void clear(Array *);

void shrink(Array *);

void dealloc(Array *);


/*
 * Serach Functions
 */
int search(const Array *, const Coord *);


#endif
