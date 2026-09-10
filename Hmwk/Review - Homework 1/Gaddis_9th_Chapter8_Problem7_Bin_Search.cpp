/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on September 9th, 2026, 2:30 PM
 * Purpose:  Gaddis 9th Ed. Chapter 8 Problem 7 Binary String Search
 */

// System Libraries
#include <iostream> // Input Output Library
#include <string>   // String Library
using namespace std;

// User Libraries

// Global Constants not Variables
// Science, Math, Conversions, Dimensions
const int SIZE{20};

// Function Prototypes
void bblSort(string [SIZE]);

int binSrch(string [SIZE], string &);

// Execution begins here at main
int main(int argc, char **argv) {
    // Set random number seed

    // Declare Variables
    string names[SIZE] = {
        "Collins, Bill", "Smith, Bart", "Allen, Jim", "Griffin, Jim", "Stamey, Marty", "Rose, Geri", "Taylor, Terri", "Johnson, Jill", "Allison, Jeff", "Looney, Joe",
        "Wolfe, Bill", "James, Jean", "Weaver, Jim", "Pore, Bob", "Rutherford, Greg", "Javens, Renee", "Harrison, Rose", "Setzer, Cathy", "Pike, Gordon", "Holland, Beth"
    };
    string target{};
    int idx;

    // Initialize Variables
    cout << "Input the name you would like to search for: ";
    getline(cin, target);

    // Map/Process the Inputs -> Outputs
    bblSort(names);
    idx = binSrch(names, target);

    // Display Inputs/Outputs
    if (idx == -1)
        cout << "Match not Found.\n";
    else
        cout << "The name \"" << target << "\" was found in the list of names at the index of " << idx << ".\n";

    // Clean up memory and files

    // Exit the Program
    return 0;
}

void bblSort(string names[SIZE]) {
    bool wasSort{false};
    string temp;

    do {
        wasSort = false;
        for (int i{0}; i < SIZE - 1; i++) {
            if (names[i] > names[i + 1]) {
                temp = names[i];
                names[i] = names[i + 1];
                names[i + 1] = temp;
                wasSort = true;
            }
        }
    } while (wasSort);
}

int binSrch(string names[SIZE], string &toFind) {
    int left{0};
    int right{SIZE - 1};
    int middle;

    while (left <= right) {
        middle = left + (right - left) / 2;
        if (toFind == names[middle])
            return middle;
        if (toFind < names[middle])
            right = middle - 1;
        if (toFind > names[middle])
            left = middle + 1;
    }
    return -1;
}
