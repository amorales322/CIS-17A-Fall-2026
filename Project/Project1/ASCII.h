/*
* File:   ASCII.h
 * Author: Anthony Morales
 * Created on October 24, 2026, 1:54 PM
 * Purpose:  Project 1 - Chess
 */

#ifndef ASCII_H
#define ASCII_H
#include "PlyrClr.h"

/*
 * Utility Functions
 */
size_t clcLftW(size_t);

size_t clcRgtW(size_t);

string getBlnk(size_t, bool);

string getBlnk(size_t, char);


/*
 * Printing Functions
 */
void drwBlRw(bool);

void drClmRw(const char *, bool);

void drawNum(const char *, size_t = 23);

void drClmRw(const char *, const char *, size_t, bool, char);

void drClmRw(const char *, const char *, size_t, bool, const PlyrClr &);

void drClmRw(const char *, const char *, size_t, bool, const PlyrClr &, char);

/*
 * Letters
 */
void drawA(size_t);

void drawB(size_t);

void drawC(size_t);

void drawD(size_t);

void drawE(size_t);

void drawF(size_t);

void drawG(size_t);

void drawH(size_t);

/*
 * Numbers
 */
void drwLtrs();

void draw1(size_t);

void draw2(size_t);

void draw3(size_t);

void draw4(size_t);

void draw5(size_t);

void draw6(size_t);

void draw7(size_t);

void draw8(size_t);

#endif
