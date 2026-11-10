/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 20, 2026, 9:15 AM
 * Purpose: CIS-17A Midterm: Problem 1
 */

// System Libraries
#include <iostream> // Input Output Library
#include <iomanip>  // Output Formatting Library
#include <string>   // String Library
using namespace std;

// User Libraries
struct cstmAct {
    unsigned int acctNum;
    string name;
    string address;
    // Represented as pennies - can be negative (overdrawn)
    int balance;
    unsigned int nChkWr;
    unsigned int *chkWrit;
    unsigned int nDepCdt;
    unsigned int *depCdt;
};

// Global Constants not Variables
// Science, Math, Conversions, Dimensions

// Function Prototypes
cstmAct *newCstm();

int cnvToP(float);

float cnvToD(int);

int clcNBal(const cstmAct *);

void pntCstm(const cstmAct *, int);

void pntArry(const unsigned int *, unsigned int);

unsigned int *resize(unsigned int *, unsigned int &, unsigned int);

void dealloc(cstmAct *);


// Execution begins here at main
int main(int argc, char **argv) {
    // Set random number seed

    // Declare Variables
    cstmAct *cstmr;
    int newBal;

    // Initialize Variables
    cstmr = newCstm();

    // Map/Process the Inputs -> Outputs
    newBal = clcNBal(cstmr);

    // Display Inputs/Outputs
    pntCstm(cstmr, newBal);

    // Clean up memory and files
    dealloc(cstmr);

    // Exit the Program
    return 0;
}

cstmAct *newCstm() {
    // Arbitrary starting size, resizes when needed
    unsigned int size = 10;
    cstmAct *cstmr = new cstmAct;
    float usrInpt;

    cstmr->nChkWr = 0;
    cstmr->chkWrit = new unsigned int[size];
    cstmr->nDepCdt = 0;
    cstmr->depCdt = new unsigned int[size];

    cout << "Enter customer name: ";
    getline(cin, cstmr->name);

    cout << "Enter your address: ";
    getline(cin, cstmr->address);

    cout << "Enter 5-digit account number: ";
    cin >> cstmr->acctNum;
    while (cstmr->acctNum < 10000 || cstmr->acctNum > 99999) {
        cout << "Invalid account number, account number must be 5-digits long. Enter new account number: ";
        cin >> cstmr->acctNum;
    }

    cout << "Enter your starting account balance: ";
    cin >> usrInpt;
    while (cnvToP(usrInpt) <= 0) {
        cout << "Invalid starting balance, starting balance must be greater than 0. Enter a new starting balance: ";
        cin >> usrInpt;
    }
    cstmr->balance = cnvToP(usrInpt);

    do {
        cout << "Enter amount of check written (Enter -1 to stop): ";
        cin >> usrInpt;
        while (cnvToP(usrInpt) <= 0 && cnvToP(usrInpt) != -100) {
            cout << "Invalid check amount, check amount must be greater than 0. Enter new amount: ";
            cin >> usrInpt;
        }
        if (cnvToP(usrInpt) != -100) {
            if (cstmr->nChkWr >= size)
                cstmr->chkWrit = resize(cstmr->chkWrit, size, cstmr->nChkWr);
            cstmr->chkWrit[cstmr->nChkWr++] = cnvToP(usrInpt);
        }
    } while (cnvToP(usrInpt) != -100);

    size = 10;
    do {
        cout << "Enter deposit amount (Enter -1 to stop): ";
        cin >> usrInpt;
        while (cnvToP(usrInpt) <= 0 && cnvToP(usrInpt) != -100) {
            cout << "Invalid deposit amount, deposit amount must be greater than 0. Enter new amount: ";
            cin >> usrInpt;
        }
        if (cnvToP(usrInpt) != -100) {
            if (cstmr->nDepCdt >= size)
                cstmr->depCdt = resize(cstmr->depCdt, size, cstmr->nDepCdt);
            cstmr->depCdt[cstmr->nDepCdt++] = cnvToP(usrInpt);
        }
    } while (cnvToP(usrInpt) != -100);

    return cstmr;
}

int cnvToP(float val) {
    return static_cast<int>(val * 100);
}

float cnvToD(int val) {
    return static_cast<float>(val) / 100;
}

int clcNBal(const cstmAct *const cstmr) {
    int bal{cstmr->balance};

    for (unsigned int i{0}; i < cstmr->nChkWr; bal -= cstmr->chkWrit[i++]);

    for (unsigned int i{0}; i < cstmr->nDepCdt; bal += cstmr->depCdt[i++]);

    return bal - (bal < 0 ? cnvToP(20.0f) : 0);
}

void pntCstm(const cstmAct *const cstmr, const int remBal) {
    // Do not have to calculate this inside the clcNBal() function
    // If the remaining balance is under 0, we can infer that account has been overdrawn
    // Otherwise it wasn't overdrawn if not negative
    bool ovrdft{remBal < 0};

    cout << fixed << showpoint << '\n';
    cout << cstmr->name << '\n';
    cout << "Account Number: " << cstmr->acctNum << '\n';
    cout << "Address: " << cstmr->address << '\n';
    cout << "Initial Balance at Beginning of Month: $" << setprecision(2) << cnvToD(cstmr->balance) << '\n';
    cout << "Check Amounts Written this Month: ";
    pntArry(cstmr->chkWrit, cstmr->nChkWr);
    cout << "Deposits Credited to Account: ";
    pntArry(cstmr->depCdt, cstmr->nDepCdt);
    cout << '\n';

    if (ovrdft)
        cout << "Account was overdrawn, a $20 overdraft fee was applied to your account.\n";
    cout << "Remaining Balance at End of Month: $" << setprecision(2) << cnvToD(remBal) << '\n';
}

void pntArry(const unsigned int *const array, const unsigned int size) {
    for (unsigned int i{0}; i < size; i++)
        cout << '$' << setprecision(2) << cnvToD(array[i]) << (i < size - 1 ? ", " : "");
    cout << '\n';
}

unsigned int *resize(unsigned int *array, unsigned int &size, const unsigned int utilsze) {
    unsigned int *newArry = new unsigned int[++size];
    for (unsigned int i{0}; i < utilsze; newArry[i] = array[i], i++);

    delete []array;
    return newArry;
}

void dealloc(cstmAct *cstmr) {
    delete []cstmr->chkWrit;
    delete []cstmr->depCdt;
    delete cstmr;
}
