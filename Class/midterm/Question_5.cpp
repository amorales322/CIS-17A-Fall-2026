/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 22, 2026, 10:45 AM
 * Purpose: CIS-17A Midterm: Problem 5
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
    int b{1};

    // Initialize Variables

    // Map/Process the Inputs -> Outputs

    // Display Inputs/Outputs
    for (long a{1}; a <= 127 / b; a *= ++b);
    cout << "'signed char' max n for n!: " << b << '\n';
    b = 1;
    for (unsigned long a{1}; a <= 255 / b; a *= ++b);
    cout << "'unsigned char' max n for n!: " << b << "\n\n";

    b = 1;
    for (long a{1}; a <= 32'767 / b; a *= ++b);
    cout << "'signed short' max n for n!: " << b << '\n';
    b = 1;
    for (unsigned long a{1}; a <= 65'535 / b; a *= ++b);
    cout << "'unsigned short' max n for n!: " << b << "\n\n";

    b = 1;
    for (long a{1}; a <= 2'147'483'647 / b; a *= ++b);
    cout << "'signed int' max n for n!: " << b << '\n';
    b = 1;
    for (unsigned long a{1}; a <= 4'294'967'295 / b; a *= ++b);
    cout << "'unsigned int' max n for n!: " << b << "\n\n";

    b = 1;
    // 'long' is 64 bits on macOS, which is what I am using
    // It is 32 bits on Windows, which is the same as for 'int'
    for (long a{1}; a <= 9'223'372'036'854'775'807 / b; a *= ++b);
    cout << "'signed long int' max n for n!: " << b << '\n';
    b = 1;
    for (unsigned long a{1}; a <= 18'446'744'073'709'551'615ULL / b; a *= ++b);
    cout << "'unsigned long int' max n for n!: " << b << "\n\n";

    b = 1;
    for (long long a{1}; a <= 9'223'372'036'854'775'807 / b; a *= ++b);
    cout << "'signed long long int' max n for n!: " << b << '\n';
    b = 1;
    for (unsigned long long a{1}; a <= 18'446'744'073'709'551'615U / b; a *= ++b);
    cout << "'unsigned long long int' max n for n!: " << b << '\n';

    b = 1;
    for (long long a{1}; a <= 9'223'372'036'854'775'807 / b; a *= ++b);
    cout << "'signed long long int' max n for n!: " << b << '\n';
    b = 1;
    for (unsigned long long a{1}; a <= 18'446'744'073'709'551'615U / b; a *= ++b);
    cout << "'unsigned long long int' max n for n!: " << b << "\n\n";

    b = 1;
    for (float a{1}; a <= 3.402'823'4e38f / b; a *= ++b);
    cout << "'float' max n for n!: " << b << '\n';
    b = 1;
    for (double a{1}; a <= 1.797'693'134'862'315'7e308 / b; a *= ++b);
    cout << "'double' max n for n!: " << b << '\n';

    // 'long double' is 64 bits on macOS ARM64, which is what I am using
    // On x86 macOS, it is 80 bits
    // On Windows, it is 64 or 128 bits depending on the compiler
    b = 1;
    for (long double a{1}; a <= 1.797'693'134'862'315'7e308L / b; a *= ++b);
    cout << "'long double' max n for n!: " << b << '\n';


    // Clean up memory and files

    // Exit the Program
    return 0;
}
