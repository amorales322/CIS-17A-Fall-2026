/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on September 10th, 2026, 11:10 AM
 * Purpose:  Gaddis 9th Ed. Chapter 6 Problem 7 Weight on Another Planet
 */

// System Libraries
#include <iostream> // Input Output Library
#include <cstring>  // C-Style String Library
#include <iomanip>  // Output Number Formatting Library
using namespace std;

// User Libraries

// Global Constants not Variables
// Science, Math, Conversions, Dimensions
const float VEN_WGT{0.905f};
const float MAR_WGT{0.3787f};
const float JUP_WGT{2.53f};
const int SIZE{80};

// Function Prototypes
float calcWght(const char [], const float);

// Execution begins here at main
int main(int argc, char **argv) {
    // Set random number seed

    // Declare Variables
    char planet[80]; // Larger than needed
    float initWgt;
    float fnlWgt;

    // Initialize Variables
    cout << "Enter the name of a planet (\"Venus\", \"Mars\", \"Jupiter\"): ";
    cin >> planet;
    while (strcmp(planet, "Venus") != 0 && strcmp(planet, "Mars") != 0 && strcmp(planet, "Jupiter") != 0) {
        cout << "The inputted planet is not a valid planet, enter a new planet name (\"Venus\", \"Mars\", \"Jupiter\"):";
        cin >> planet;
    }

    cout << "Enter the weight of the object on earth in lbs: ";
    cin >> initWgt;
    while (initWgt <= 0.0f) {
        cout << "Weight cannot be negative, enter a new positive weight in lbs: ";
        cin >> initWgt;
    }

    // Map/Process the Inputs -> Outputs
    fnlWgt = calcWght(planet, initWgt);

    // Display Inputs/Outputs
    cout << fixed << showpoint << setprecision(2);
    cout << "The weight of the object on the planet " << planet << " is " << fnlWgt << " lbs.\n";

    // Clean up memory and files

    // Exit the Program
    return 0;
}

float calcWght(const char planet[], const float initWgt) {
    if (strcmp(planet, "Venus") == 0)
        return VEN_WGT * initWgt;
    if (strcmp(planet, "Mars") == 0)
        return MAR_WGT * initWgt;
    return JUP_WGT * initWgt;
}
