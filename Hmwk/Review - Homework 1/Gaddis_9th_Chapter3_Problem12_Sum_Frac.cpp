/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on September 9, 2026, 9:14 PM
 * Purpose:  Gaddis 9th Ed. Chapter 3 Problem 12 Sum of Two Fractions
 */

// System Libraries
#include <iostream> // Input Output Library
using namespace std;

// User Libraries

// Global Constants not Variables
// Science, Math, Conversions, Dimensions

// Function Prototypes
// Algorithm to find the greatest common denominator among two numbers
// https://en.wikipedia.org/wiki/Euclidean_algorithm
int euclAlg(int a, int b);

// Execution begins here at main
int main(int argc, char **argv) {
    // Set random number seed

    // Declare Variables
    int a;
    int b;
    int c;
    int d;
    int numSum;
    int denSum;
    int gcd;

    // Initialize Variables
    cout << "Enter the numerator for fraction 1: ";
    cin >> a;

    cout << "Enter the denominator for fraction 1: ";
    cin >> b;
    while (b == 0) {
        cout << "The denominator of a fraction cannot be zero. Enter a new number that is not zero: ";
        cin >> b;
    }

    cout << "Enter the numerator for fraction 2: ";
    cin >> c;

    cout << "Enter the denominator for fraction 2: ";
    cin >> d;
    while (d == 0) {
        cout << "The denominator of a fraction cannot be zero. Enter a new number that is not zero: ";
        cin >> d;
    }

    // Map/Process the Inputs -> Outputs
    numSum = a * d + b * c;
    denSum = b * d;

    // So I could simplify the fraction
    gcd = euclAlg(numSum, denSum);
    numSum /= gcd;
    denSum /= gcd;

    // Display Inputs/Outputs
    cout << "Simplified sum of two fractions: " << numSum << "/" << denSum << '\n';

    // Clean up memory and files

    // Exit the Program
    return 0;
}

int euclAlg(int a, int b) {
    int temp{a};

    if (a % b == 0)
        return b;
    a = b;
    b = temp % b;
    return euclAlg(a, b);
}
