/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on September 9, 2026, 10:55 PM
 * Purpose:  Gaddis 9th Ed. Chapter 5 Problem 11
 */

// System Libraries
#include <iostream> // Input Output Library
#include <iomanip>  // Output Number Formatting Library
using namespace std;

// User Libraries

// Global Constants not Variables
// Science, Math, Conversions, Dimensions

// Function Prototypes

// Execution begins here at main
int main(int argc, char **argv) {
    // Set random number seed

    // Declare Variables
    int popSize;
    float popInc;
    int days;

    // Initialize Variables
    cout << "Enter the initial population size (> 2): ";
    cin >> popSize;
    while (popSize < 2) {
        cout << "Initial population size must be greater than 2. Enter a new initial population size greater than 2: ";
        cin >> popSize;
    }

    cout << "Enter the average daily population increase (as a positive float): ";
    cin >> popInc;
    while (popInc < 0.0f) {
        cout << "The average daily population increase cannot be negative. Enter a new positive average: ";
        cin >> popInc;
    }

    cout << "Enter the number of days to track the population size over: ";
    cin >> days;
    while (days < 1) {
        cout << "The number of days must be greater than 1. Enter a new number of days: ";
        cin >> days;
    }

    // Map/Process the Inputs -> Outputs

    // Display Inputs/Outputs
    cout << setprecision(0);
    for (int day{0}; day < days; day++) {
        popSize += static_cast<int>(popSize * popInc);
        cout << "Day " << day + 1 << " population size: " << popSize << "\n";
    }

    // Clean up memory and files

    // Exit the Program
    return 0;
}
