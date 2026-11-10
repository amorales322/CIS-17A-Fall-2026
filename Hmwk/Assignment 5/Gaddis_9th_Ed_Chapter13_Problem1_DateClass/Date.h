/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on November 7, 2026, 12:18 AM
 * Purpose: Date Class Header File
 */

#ifndef DATE_H
#define DATE_H

#include <string>
using namespace std;

enum class Format { MDY, MMDY, DMY };

class Date {
private:
    unsigned char day;
    unsigned char month;
    unsigned short year;
    const char *months[12]{"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

public:
    Date(unsigned char, unsigned char, unsigned short);

    string getDate(Format) const;
};

#endif
