/*
* File:   Array.h
 * Author: Anthony Morales
 * Created on October 24, 2026, 1:54 PM
 * Purpose:  CIS-17A Fall 2026 Project 1 - Chess
 */

#ifndef ARRAY_H
#define ARRAY_H

#include "Coord.h"

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

void appDta(Array *, const Array *);

void pop(Array *, int = -1);


/*
 * Capacity Modifiers
 */
void resize(Array *, int = -1);

void clear(Array *);

void dealloc(Array *);


/*
 * Serach Functions
 */
int search(const Array *, const Coord *);


#endif
