/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 17, 2026, 11:58 AM
 * Purpose:  Gaddis 9th Ed. Chapter 12 Problem 11 - Wind Observation Data
 */

// System Libraries
#include <iostream> // Input Output Library
#include <fstream>  // File Stream Library
#include <ctime>    // C Time Library
#include <cstdlib>  // C Standard Library
#include <cctype>   // Character Handling Library
using namespace std;

// User Libraries
struct windDta {
    char dirct;
    short speed;
    time_t tmestmp;
};

// Global Constants not Variables
// Science, Math, Conversions, Dimensions

// Function Prototypes
windDta *newDtPt();

void wrteDta(ofstream &, windDta *const *, unsigned int);

void dealloc(windDta **, unsigned int);

// Execution begins here at main
int main(int argc, char **argv) {
    // Set random number seed
    srand(time(0));

    // Declare Variables
    unsigned int nDataPt;
    windDta **data;
    ofstream outFile{"weather_data.bin", ios::binary};

    // Initialize Variables
    cout << "Enter how many weather datapoints you would like to enter: ";
    cin >> nDataPt;

    data = new windDta *[nDataPt];


    // Map/Process the Inputs -> Outputs
    for (unsigned int i{0}; i < nDataPt; i++)
        data[i] = newDtPt();

    wrteDta(outFile, data, nDataPt);

    // Display Inputs/Outputs

    // Clean up memory and files
    dealloc(data, nDataPt);
    outFile.close();

    // Exit the Program
    return 0;
}

windDta *newDtPt() {
    // January 1, 2020 - 12:00:00 AM
    const time_t MINDATE{1577836800};

    windDta *dataPt = new windDta;

    cout << "Enter wind direction (N: North, S: South, E: East, W: West): ";
    cin >> dataPt->dirct;
    dataPt->dirct = static_cast<char>(toupper(dataPt->dirct));
    while (dataPt->dirct != 'N' && dataPt->dirct != 'E' && dataPt->dirct != 'S' && dataPt->dirct != 'W') {
        cout << "Invalid wind direction. Enter wind direction (N: North, S: South, E: East, W: West): ";
        cin >> dataPt->dirct;
        dataPt->dirct = static_cast<char>(toupper(dataPt->dirct));
    }

    cout << "Enter wind speed (Positive Value Only): ";
    cin >> dataPt->speed;
    while (dataPt->speed < 0) {
        cout << "Invalid wind speed. Enter wind speed (Positive Value Only): ";
        cin >> dataPt->speed;
    }

    dataPt->tmestmp = rand() % (time(0) - MINDATE + 1) + MINDATE;

    return dataPt;
}

void wrteDta(ofstream &outFile, windDta *const *const data, const unsigned int size) {
    for (unsigned int i{0}; i < size; i++)
        outFile.write(reinterpret_cast<char *>(data[i]), sizeof(windDta));
}

void dealloc(windDta **data, const unsigned int size) {
    for (unsigned int i{0}; i < size; i++)
        delete data[i];

    delete []data;
}
