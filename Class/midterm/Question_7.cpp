/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 21, 2026, 7:32PM
 * Purpose: CIS-17A Midterm: Problem 7
 */

// System Libraries
#include <iostream> // Input Output Library
#include <cmath>    // C Math Library
using namespace std;

// User Libraries
struct Prime {
    unsigned char power;
    unsigned short prime;
};

struct Primes {
    unsigned short n;
    unsigned char nPrimes;
    Prime *pStrAry; // Prime Array
};

// Global Constants not Variables
// Science, Math, Conversions, Dimensions

// Function Prototypes
Primes *factor(int);

void prtPrms(const Primes *);

bool isPrime(int);

void updPrme(Primes *, int, unsigned int &);

void resize(Primes *, unsigned int &);

void dealloc(Primes *);

// Execution begins here at main
int main(int argc, char **argv) {
    // Set random number seed

    // Declare Variables
    int usrInpt;
    Primes *fctr;

    // Map/Process the Inputs -> Outputs
    cout << "Enter the number you would like to calculate the prime factorization for [2, 65000]: ";
    cin >> usrInpt;
    while (usrInpt < 2 || usrInpt > 65000) {
        cout << "Number must be between 2 and 65,000, enter a new number: ";
        cin >> usrInpt;
    }

    fctr = factor(usrInpt);

    // Display Inputs/Outputs
    prtPrms(fctr);

    // Clean up memory and files
    dealloc(fctr);

    // Exit the Program
    return 0;
}

Primes *factor(int value) {
    unsigned int size = 2;
    Primes *primes = new Primes{static_cast<unsigned short>(value), 0, new Prime[size]};

    // Prime Factorization
    int factor{1};
    while (!isPrime(value)) {
        while (value % ++factor != 0);
        updPrme(primes, factor, size);
        value /= factor;
        factor = 1;
    }
    updPrme(primes, value, size);

    return primes;
}

void prtPrms(const Primes *const primes) {
    cout << primes->n << " = ";
    for (int i{0}; i < primes->nPrimes; i++)
        cout << primes->pStrAry[i].prime << '^' << static_cast<int>(primes->pStrAry[i].power) << (i < primes->nPrimes - 1 ? " * " : "");
    cout << '\n';
}

bool isPrime(const int num) {
    if (num <= 1)
        return false;
    if (num == 2 || num == 3 || num == 5)
        return true;
    if (num % 2 == 0 || num % 3 == 0 || num % 5 == 0)
        return false;
    for (int i{7}; i <= static_cast<int>(sqrt(num)); i += 6)
        if (num % i == 0 || num % (i + 4) == 0)
            return false;
    return true;
}

void updPrme(Primes *const primes, const int target, unsigned int &size) {
    bool found{false};

    for (int i{0}; i < primes->nPrimes && !found; i++)
        if (primes->pStrAry[i].prime == target) {
            primes->pStrAry[i].power++;
            found = true;
        }
    if (!found) {
        if (primes->nPrimes >= size)
            resize(primes, size);
        primes->pStrAry[primes->nPrimes].prime = target;
        primes->pStrAry[primes->nPrimes++].power = 1;
    }
}

void resize(Primes *const primes, unsigned int &size) {
    Prime *newData = new Prime[++size];
    for (int i{0}; i < primes->nPrimes; i++)
        newData[i] = primes->pStrAry[i];

    delete []primes->pStrAry;
    primes->pStrAry = newData;
}

void dealloc(Primes *primes) {
    delete []primes->pStrAry;
    delete primes;
}
