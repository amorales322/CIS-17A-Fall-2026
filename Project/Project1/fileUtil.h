/*
* File:   fileUtil.h
 * Author: Anthony Morales
 * Created on October 24, 2026, 1:54 PM
 * Purpose:  Project 1 - Chess
 */

#ifndef FILEUTIL_H
#define FILEUTIL_H

#include "PlyrClr.h"

string getFPth(const string & = "", const string & = "");

void opnFile(fstream &, const string &, bool = false);

/*
 * File Readers/Writers
 */
char *recast(bool &);

void read(fstream &, bool &);

void write(fstream &, bool);


char *recast(PlyrClr &);

void read(fstream &, PlyrClr &);

void write(fstream &, PlyrClr);


char *recast(unsigned short &);

void read(fstream &, unsigned short &);

void write(fstream &, unsigned short);


char *recast(size_t &);

void read(fstream &, size_t &);

void write(fstream &, size_t);


void read(fstream &, string &);

void write(fstream &, string);

#endif
