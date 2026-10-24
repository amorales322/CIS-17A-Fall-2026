/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 9, 2026, 12:23 PM
 * Purpose:  Structure Weather Statistics
 */

// System Libraries
#include <iostream> // Input Output Library
#include <iomanip>
using namespace std;

// User Libraries
struct wtrStat {
    string month;
    unsigned short totRfll;
    short lowTemp;
    short hghTemp;
};

// Global Constants not Variables
// Science, Math, Conversions, Dimensions

// Function Prototypes
wtrStat initStat();

float clcAvRF(const wtrStat *, unsigned int);

string fdHghTm(const wtrStat *, unsigned int, short &);

string fdLowTm(const wtrStat *, unsigned int, short &);

float clcAvTm(const wtrStat *, unsigned int);

void dealloc(wtrStat *);

// Execution begins here at main
int main(int argc, char **argv) {
    // Set random number seed

    // Declare Variables
    unsigned int nMonths{12};
    wtrStat *stats = new wtrStat[nMonths];

    short hghTemp;
    short lowTemp;

    // Initialize Variables
    for (int i{0}; i < nMonths; i++)
        stats[i] = initStat();

    // Map/Process the Inputs -> Outputs

    // Display Inputs/Outputs
    cout << "Average Rainfall " << setprecision(2) << clcAvRF(stats, nMonths) << " inches/month\n";
    cout << "Lowest  Temperature " << fdLowTm(stats, nMonths, lowTemp) << "  " << lowTemp << " Degrees Fahrenheit\n";
    cout << "Highest Temperature " << fdHghTm(stats, nMonths, hghTemp) << "  " << hghTemp << " Degrees Fahrenheit\n";
    cout << "Average Temperature for the year " << clcAvTm(stats, nMonths) << " Degrees Fahrenheit\n";

    // Clean up memory and files
    dealloc(stats);

    // Exit the Program
    return 0;
}

wtrStat initStat() {
    wtrStat stat;

    cin >> stat.month;
    cin >> stat.totRfll;
    do {
        cin >> stat.lowTemp;
    } while (stat.lowTemp < -100 || stat.lowTemp > 140);
    do {
        cin >> stat.hghTemp;
    } while (stat.hghTemp < -100 || stat.hghTemp > 140 || stat.hghTemp < stat.lowTemp);

    return stat;
}


float clcAvRF(const wtrStat *stats, const unsigned int size) {
    float tot{0.0f};
    for (int i{0}; i < size; i++)
        tot += static_cast<float>(stats[i].totRfll);

    return tot / size;
}

float clcAvTm(const wtrStat *stats, const unsigned int size) {
    float tot{0.0f};
    for (int i{0}; i < size; i++)
        tot += static_cast<float>(stats[i].lowTemp + stats[i].hghTemp) / 2;

    return tot / size;
}

string fdHghTm(const wtrStat *stats, const unsigned int size, short &hghTemp) {
    hghTemp = stats[0].hghTemp;
    string tgtMth;
    for (int i{1}; i < size; i++) {
        if (stats[i].hghTemp > hghTemp) {
            hghTemp = stats[i].hghTemp;
            tgtMth = stats[i].month;
        }
    }

    return tgtMth;
}

string fdLowTm(const wtrStat *stats, const unsigned int size, short &lowTemp) {
    lowTemp = stats[0].lowTemp;
    string tgtMth = stats[0].month;

    for (int i{1}; i < size; i++) {
        if (stats[i].lowTemp < lowTemp) {
            lowTemp = stats[i].lowTemp;
            tgtMth = stats[i].month;
        }
    }

    return tgtMth;
}

void dealloc(wtrStat *stats) {
    delete []stats;
}
