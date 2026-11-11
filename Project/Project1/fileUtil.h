#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <fstream>
#include <string>
using namespace std;

#include "PlyrClr.h"

void read(fstream &, bool &);

void write(fstream &, bool);


void read(fstream &, PlyrClr &);

void write(fstream &, PlyrClr);


void read(fstream &, unsigned short &);

void write(fstream &, unsigned short);


void read(fstream &, size_t &);

void write(fstream &, size_t);


void read(fstream &, string &);

void write(fstream &, string);

#endif
