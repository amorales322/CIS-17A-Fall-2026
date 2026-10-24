/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 14, 2026, 1:35 PM
 * Purpose:  Structure Weather Statistics
 */

// System Libraries
#include <iostream> // Input Output Library
#include <iomanip>
using namespace std;

// User Libraries
enum Month { JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE };

struct wtrStat {
    Month month;
    float totRfll;
    short lowTemp;
    short hghTemp;
};

// Global Constants not Variables
// Science, Math, Conversions, Dimensions

// Function Prototypes
wtrStat initStat(Month);

float clcAvRF(const wtrStat *, unsigned int);

short fdHghTm(const wtrStat *, unsigned int);

short fdLowTm(const wtrStat *, unsigned int);

float clcAvTm(const wtrStat *, unsigned int);

void dealloc(wtrStat *);

// Execution begins here at main
int main(int argc, char **argv) {
    // Set random number seed

    // Declare Variables
    unsigned int nMonths{6};
    wtrStat *stats = new wtrStat[nMonths];
    string temp;

    // Initialize Variables
    for (Month month{JANUARY}; month <= JUNE; month = static_cast<Month>(month + 1))
        stats[month] = initStat(month);

    // Map/Process the Inputs -> Outputs

    // Display Inputs/Outputs
    cout << fixed << showpoint;
    cout << "Average monthly rainfall:" << setprecision(2) << clcAvRF(stats, nMonths) << '\n';
    cout << "High Temp:" << fdHghTm(stats, nMonths) << '\n';
    cout << "Low Temp:" << fdLowTm(stats, nMonths) << '\n';
    cout << "Average Temp:" << setprecision(1) << clcAvTm(stats, nMonths);

    // Clean up memory and files
    dealloc(stats);

    // Exit the Program
    return 0;
}

wtrStat initStat(Month month) {
    wtrStat stat;

    stat.month = month;
    cout << "Enter the total rainfall for the month:\n";
    cin >> stat.totRfll;
    cout << "Enter the high temp:\n";
    cin >> stat.hghTemp;
    cout << "Enter the low temp:\n";
    cin >> stat.lowTemp;

    return stat;
}


float clcAvRF(const wtrStat *stats, const unsigned int size) {
    float tot{0.0f};
    for (int month{JANUARY}; month <= JUNE; month = static_cast<Month>(month + 1))
        tot += stats[month].totRfll;

    return tot / size;
}

float clcAvTm(const wtrStat *stats, const unsigned int size) {
    float tot{0.0f};
    for (int month{JANUARY}; month <= JUNE; month = static_cast<Month>(month + 1))
        tot += static_cast<float>(stats[month].lowTemp + stats[month].hghTemp) / 2;

    return tot / size;
}

short fdHghTm(const wtrStat *stats, const unsigned int size) {
    short hghTemp = stats[JANUARY].hghTemp;

    for (int month{FEBRUARY}; month <= JUNE; month = static_cast<Month>(month + 1)) {
        if (stats[month].hghTemp > hghTemp)
            hghTemp = stats[month].hghTemp;
    }

    return hghTemp;
}

short fdLowTm(const wtrStat *stats, const unsigned int size) {
    short lowTemp = stats[JANUARY].lowTemp;

    for (int month{FEBRUARY}; month <= JUNE; month = static_cast<Month>(month + 1)) {
        if (stats[month].lowTemp < lowTemp)
            lowTemp = stats[month].lowTemp;
    }

    return lowTemp;
}

void dealloc(wtrStat *stats) {
    delete []stats;
}
