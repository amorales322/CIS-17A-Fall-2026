/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 17, 2026, 10:10 AM
 * Purpose:  Gaddis 9th Ed. Chapter 12 Problem 7 - Binary Character File
 */

// System Libraries
#include <iostream> // Input Output Library
#include <string>   // String Libary
#include <cstdlib>  // C Standard Library
#include <ctime>    // C Time Library
#include <fstream>  // File Stream Library
using namespace std;

// User Libraries

// Global Constants not Variables
// Science, Math, Conversions, Dimensions

// Function Prototypes

char *fillAry(unsigned int &);

void storeArray(string &, const char *, unsigned int);

void dealloc(char *);

// Execution begins here at main
int main(int argc, char **argv) {
    // Set random number seed
    srand(time(0));

    // Declare Variables
    unsigned int size;
    string fileNme;
    char *array;

    // Initialize Variables
    cout << "Enter the size of the character array you would like to write to a binary file (Greater than 1): ";
    cin >> size;
    cout << "Enter the name of the binary file you would like to write to: ";
    cin >> fileNme;

    // Map/Process the Inputs -> Outputs
    array = fillAry(size);
    storeArray(fileNme, array, size);

    // Display Inputs/Outputs

    // Clean up memory and files
    dealloc(array);
    // Exit the Program
    return 0;
}

char *fillAry(unsigned int &size) {
    // Change size to 2 if the size is 1 or 0
    size = size > 1 ? size : 2;
    char *array = new char[size];

    // Fill with random characters
    for (unsigned int i{0}; i < size; i++)
        array[i] = rand() % 94 + 33;

    return array;
}

void storeArray(string &fileNme, const char *const array, const unsigned int size) {
    ofstream file{fileNme, ios::binary};

    file.write(array, size * sizeof(char));

    file.close();
}

void dealloc(char *array) {
    delete []array;
}
