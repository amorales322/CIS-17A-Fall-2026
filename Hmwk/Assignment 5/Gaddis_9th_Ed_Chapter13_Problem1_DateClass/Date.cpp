/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on November 7, 2026, 12:18 AM
 * Purpose:  Date Class Implementation
 */

#include <string>
#include <sstream>
#include <iomanip>
#include "Date.h"
using namespace std;

Date::Date(const unsigned char dte, const unsigned char mth, const unsigned short yr) {
    day = dte;
    month = mth;
    year = yr;
}

string Date::getDate(Format format) const {
    stringstream buffer;
    switch (format) {
        case Format::MDY:
            buffer << month << '/' << setfill('0') << setw(2) << day << '/' << year;
            return buffer.str();
        case Format::MMDY:
            buffer << months[month - 1] << ' ' << setfill('0') << setw(2) << day << ", " << year;
            return buffer.str();
        case Format::DMY:
            buffer << setfill('0') << day << ' ' << months[month - 1] << ' ' << year;
            return buffer.str();
    }
    return "Invalid Format.";
}
