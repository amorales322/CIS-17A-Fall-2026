/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on September 9, 2026, 10:25 PM
 * Purpose:  Gaddis 9th Ed. Chapter 4 Problem 10 Days in a Month
 */

// System Libraries
#include <iostream> // Input Output Library
using namespace std;

// User Libraries

// Global Constants not Variables
// Science, Math, Conversions, Dimensions

// Function Prototypes

// Execution begins here at main
int main(int argc, char **argv) {
    // Set random number seed

    // Declare Variables
    short month;
    short year;
    bool isLeap{false};

    // Initialize Variables
    cout << "Enter a month: ";
    cin >> month;
    while (month < 1 || month > 12) {
        cout << "Invalid month entered. Valid values are between [1, 12]. Enter a new month: ";
        cin >> month;
    }
    cout << "Enter a year: ";
    cin >> year;

    // Map/Process the Inputs -> Outputs
    if (year % 100 == 0) {
        if (year % 400 == 0)
            isLeap = true;
    } else if (year % 4 == 0)
        isLeap = true;

    // Display Inputs/Outputs
    if (month == 2) {
        if (isLeap)
            cout << "29 days\n";
        else
            cout << "28 days\n";
    } else if (month <= 7)
        cout << (month % 2 == 0 ? "30 days" : "31 days") << '\n';
    else
        cout << (month % 2 == 0 ? "31 days" : "30 days") << '\n';

    // Clean up memory and files

    // Exit the Program
    return 0;
}
