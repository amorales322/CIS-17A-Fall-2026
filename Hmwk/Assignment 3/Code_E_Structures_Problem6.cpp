/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 10, 2026, 2:41 PM
 * Purpose:  Structures Movie Data
 */

// System Libraries
#include <iostream> // Input Output Library
#include <iomanip> // Output Formatting Library
using namespace std;

// User Libraries
struct movData {
    string title;
    string dirName;
    unsigned short relYear;
    unsigned short runtime;
};

// Global Constants not Variables
// Science, Math, Conversions, Dimensions

// Function Prototypes

movData *initData(unsigned int);

void prntMov(const movData &);

void dealloc(movData *);

// Execution begins here at main
int main(int argc, char **argv) {
    // Set random number seed

    // Declare Variables
    unsigned int size;
    movData *data;

    // Initialize Variables
    cout << "This program reviews structures\n";
    cout << "Input how many movies, the Title of the Movie, Director, Year Released, and the Running Time in (minutes).\n\n";

    cin >> size;
    cin.ignore();

    // Map/Process the Inputs -> Outputs
    data = initData(size);

    // Display Inputs/Outputs
    for (unsigned int i{0}; i < size; i++) {
        prntMov(data[i]);
        if (i < size - 1)
            cout << '\n';
    }

    // Clean up memory and files
    dealloc(data);

    // Exit the Program
    return 0;
}

movData *initData(unsigned int size) {
    movData *data = new movData[size];

    for (unsigned int i{0}; i < size; i++) {
        getline(cin, data[i].title);
        getline(cin, data[i].dirName);
        cin >> data[i].relYear;
        cin >> data[i].runtime;
        cin.ignore();
    }

    return data;
}

void prntMov(const movData &movie) {
    cout << setw(11) << left << "Title:" << movie.title << '\n';
    cout << setw(11) << left << "Director:" << movie.dirName << '\n';
    cout << setw(11) << left << "Year:" << movie.relYear << '\n';
    cout << setw(11) << left << "Length:" << movie.runtime << '\n';
}

void dealloc(movData *data) {
    delete []data;
}
