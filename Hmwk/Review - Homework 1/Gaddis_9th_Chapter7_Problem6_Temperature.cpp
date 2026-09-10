/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on September 9th, 2026, 12:15 PM
 * Purpose:  Gaddis 9th Ed. Chapter 7 Problem 6 Temperature Variation
 */

// System Libraries
#include <iostream> // Input Output Library
#include <cstdlib>  // C Standard Library
#include <ctime>    // C Time Library
#include <cmath>    // C Math Library
#include <iomanip>  // Output Formatting Library
using namespace std;

// User Libraries

// Global Constants not Variables
// Science, Math, Conversions, Dimensions

// Columns: Highest Temperature, Lowest Temperature, Humidity, Temperature Variation, Humidity Compared to Average
const int NCOLS = 5;
const int NDAYS = 120;
const int NMONTHS = 12;
const int SIZE = 10;
const char MONTHS[NMONTHS][SIZE] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};


// Function Prototypes
void initDta(int [NCOLS][NDAYS + 1]);

void calcData(int [NCOLS][NDAYS + 1]);

void prntTab(const int [NCOLS][NDAYS + 1]);

// Execution begins here at main
int main(int argc, char **argv) {
    // Set random number seed
    srand(time({}));

    // Declare Variables
    // Additional column is for calculated information
    int whtrIfo[NCOLS][NDAYS + 1] = {};

    // Initialize Variables
    initDta(whtrIfo);

    // Map/Process the Inputs -> Outputs
    calcData(whtrIfo);

    // Display Inputs/Outputs
    prntTab(whtrIfo);

    // Clean up memory and files

    // Exit the Program
    return 0;
}

void initDta(int whtrIfo[NCOLS][NDAYS + 1]) {
    // Initialize with random weather data
    whtrIfo[0][0] = rand() % 60;
    whtrIfo[1][0] = rand() % 50 - rand() % 21;
    whtrIfo[2][0] = rand() % 101;

    // Highest Temperature
    for (int i{1}; i < NDAYS; i++) {
        do {
            whtrIfo[0][i] = rand() % 110;
        } while (abs(whtrIfo[0][i] - whtrIfo[0][i - 1]) > 10); // Prevents extreme day-to-day variations
    }


    // Lowest Temperature
    for (int i{1}; i < NDAYS; i++) {
        do {
            whtrIfo[1][i] = rand() % 70 - rand() % 21;
        } while (whtrIfo[1][i] > whtrIfo[0][i]); // Checks if the lowest temperature is higher than the highest
    }

    // Humidity
    for (int i{0}; i < NDAYS; i++)
        whtrIfo[2][i] = rand() % 101;
}

void calcData(int data[NCOLS][NDAYS + 1]) {
    for (int i{0}; i < NDAYS; i++)
        data[2][NDAYS] += data[2][i];
    data[2][NDAYS] /= NDAYS;
    data[0][NDAYS] = data[0][0];
    data[1][NDAYS] = data[1][0];

    for (int i{0}; i < NDAYS; i++) {
        if (data[0][i] > data[0][NDAYS])
            data[0][NDAYS] = data[0][i];
        if (data[1][i] < data[1][NDAYS])
            data[1][NDAYS] = data[1][i];
        data[3][i] = data[0][i] - data[1][i];
        data[4][i] = data[2][i] > data[2][NDAYS] ? 1 : data[2][i] < data[2][NDAYS] ? -1 : 0;
    }
}

void prntTab(const int data[NCOLS][NDAYS + 1]) {
    int aveVar{0};

    for (int month{0}; month < 12; month++) {
        cout << MONTHS[month] << '\n';
        cout << "Day | Highest Temperature (°F) | Lowest Temperature (°F) | Diurnal Variation (°F) | Humidity (%) | > / < / == than ave. humidity" << '\n';
        for (int day{0}; day < 10; day++) {
            cout << setw(3) << day + 1 << " | " << setw(24) << data[0][month * 10 + day] << " | " << setw(23) << data[1][month * 10 + day] << " | ";
            cout << setw(22) << data[3][month * 10 + day] << " | " << setw(12) << data[2][month * 10 + day] << " | ";
            cout << setw(29) << (data[4][month * 10 + day] == 1 ? "Greater" : data[4][month * 10 + day] == 0 ? "Equal" : "Less") << "\n";

            aveVar += data[3][month * 10 + day];
        }
        cout << '\n';
    }

    cout << "Maximum Temperature: " << setw(4) << data[0][NDAYS] << "°F\n";
    cout << "Minimum Temperature: " << setw(4) << data[1][NDAYS] << "°F\n";
    cout << "  Average Variation: " << setw(4) << aveVar / NDAYS << "°F\n";
}
