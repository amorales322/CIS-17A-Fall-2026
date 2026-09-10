/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on September 9, 2026, 10:20 PM
 * Purpose:  Gaddis 9th Ed. Chapter 3 Problem 13 Currency Conversion
 */

// System Libraries
#include <iostream> // Input Output Library
#include <iomanip>  // Output Number Formatting Library
using namespace std;

// User Libraries

// Global Constants not Variables
// Science, Math, Conversions, Dimensions
const float YEN_DOL{98.93f};
const float EUR_DOL{0.74};

// Function Prototypes

// Execution begins here at main
int main(int argc, char **argv) {
    // Set random number seed

    // Declare Variables
    float dolAmt;
    float euroAmt;
    float yenAmt;

    // Initialize Variables
    cout << "Enter the U.S. Dollar amount you would like to convert: ";
    cin >> dolAmt;

    // Map/Process the Inputs -> Outputs
    euroAmt = dolAmt * YEN_DOL;
    yenAmt = dolAmt * EUR_DOL;

    // Display Inputs/Outputs
    cout << setprecision(2) << fixed << showpoint;
    cout << dolAmt << " Dollars is " << euroAmt << " Euros.\n";
    cout << dolAmt << " Dollars is " << yenAmt << " Yen.\n";

    // Clean up memory and files

    // Exit the Program
    return 0;
}
