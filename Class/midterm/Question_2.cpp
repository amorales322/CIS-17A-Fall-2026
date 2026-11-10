/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 20, 2026, 2:22 PM
 * Purpose: CIS-17A Midterm: Problem 2
 */

// System Libraries
#include <iostream> // Input Output Library
#include <string>   // String Library
#include <iomanip>  // Output Number Formatting Library
using namespace std;

// User Libraries
struct empInfo {
    string name;
    // 168 Hours in a week
    float hrsWork;
    //Represented as pennies
    int payRate;
};

// Global Constants not Variables
// Science, Math, Conversions, Dimensions

// Function Prototypes
int cnvToP(float);

float cnvToD(int);

int calcPay(const empInfo *);

unsigned int numDig(unsigned int);

string engVal(int);

empInfo *newEmp(unsigned int);

void prntChk(const empInfo *, const string &, const string &);

void dealloc(empInfo **, unsigned int);

// Execution begins here at main
int main(int argc, char **argv) {
    // Set random number seed

    // Declare Variables
    string compNme;
    string compAdd;
    int numEmp;
    empInfo **empData;

    // Initialize Variables
    cout << "Enter company name: ";
    getline(cin, compNme);

    cout << "Enter company address: ";
    getline(cin, compAdd);

    cout << "Enter how many employees you would like to get a weekly check for (Greater than 0): ";
    cin >> numEmp;
    while (numEmp < 1) {
        cout << "Invalid number of employees, number of employees must be greater than 0. Enter a new number of employees: ";
        cin >> numEmp;
    }
    empData = new empInfo *[numEmp];
    cout << '\n';

    // Map/Process the Inputs -> Outputs
    for (int i{0}; i < numEmp; i++)
        empData[i] = newEmp(i + 1);

    // Display Inputs/Outputs
    cout << fixed << showpoint << '\n';
    for (int i{0}; i < numEmp; i++)
        prntChk(empData[i], compNme, compAdd);

    // Clean up memory and files
    dealloc(empData, numEmp);

    // Exit the Program
    return 0;
}

int cnvToP(const float val) {
    return static_cast<int>(val * 100);
}

float cnvToD(const int val) {
    return static_cast<float>(val) / 100;
}

int calcPay(const empInfo *const info) {
    return cnvToP(cnvToD(info->payRate) * (info->hrsWork <= 40 ? info->hrsWork : info->hrsWork < 50 ? 40 + (info->hrsWork - 40) * 2 : 60 + (info->hrsWork - 50) * 3));
}

empInfo *newEmp(const unsigned int empNum) {
    empInfo *empData = new empInfo;
    float usrInpt;

    cout << "Enter Employee #" << empNum << "'s Name: ";
    cin.ignore();
    getline(cin, empData->name);

    cout << "Enter Employee #" << empNum << "'s Hours Worked this Week: ";
    cin >> empData->hrsWork;
    while (empData->hrsWork < 0 || empData->hrsWork > 168) {
        cout << "Hours worked must be between 0 and 168, enter new number of hours worked: ";
        cin >> empData->hrsWork;
    }

    cout << "Enter Employee #" << empNum << "'s Pay Rate: ";
    cin >> usrInpt;
    while (usrInpt < 0) {
        cout << "Pay rate cannot be negative, enter a new pay rate: ";
        cin >> usrInpt;
    }
    empData->payRate = cnvToP(usrInpt);

    cout << '\n';
    return empData;
}

string engVal(const int pay) {
    string onesWrd[]{"One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    string tens[]{"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    string tensWrd[]{"Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

    string englVal;
    int decPart{pay / 100};
    int frcPart{pay % 100};

    unsigned int nDigits;
    unsigned int toCalc;

    while (decPart > 0) {
        nDigits = numDig(decPart);

        if (nDigits == 3)
            englVal += onesWrd[decPart / 100 - 1] + " Hundred ";
        else if (nDigits == 6)
            englVal += onesWrd[decPart / 1000 / 100 - 1] + " Hundred ";
        else if (nDigits == 9)
            englVal += onesWrd[decPart / 1000000 / 100 - 1] + " Hundred ";

        toCalc = decPart / (nDigits <= 3 ? 1 : nDigits <= 6 ? 1000 : 1000000) % 100;
        if (toCalc > 0)
            englVal += (toCalc < 10 ? onesWrd[toCalc - 1] : toCalc < 20 ? tens[toCalc - 10]
                                                                : tensWrd[toCalc / 10 - 2] + (toCalc % 10 == 0 ? "" : " " + onesWrd[toCalc % 10 - 1])) + " ";

        decPart %= nDigits <= 3 ? 1 : nDigits <= 6 ? 1000 : 1000000;
        englVal += nDigits > 3 && nDigits <= 6 ? "Thousand " : nDigits > 6 && nDigits <= 9 ? "Million " : "";
    }
    if (pay / 100 > 0)
        englVal += "and ";
    englVal += frcPart == 0 ? "None/100" : to_string(frcPart) + "/100";

    return englVal;
}

unsigned int numDig(unsigned int val) {
    unsigned int count{0};
    for (; val > 0; count++, val /= 10);
    return count;
}

void prntChk(const empInfo *const data, const string &compNme, const string &compAdd) {
    int pay{calcPay(data)};

    cout << compNme << '\n';
    cout << compAdd << '\n';
    cout << "Pay to the Order Of: " << setw(30) << left << data->name << '$' << setprecision(2) << cnvToD(pay) << '\n';
    cout << engVal(pay) << '\n';
    cout << setw(51) << "For: Paycheck" << "Signature: " << compNme << "\n\n";
}

void dealloc(empInfo **data, const unsigned int numEmp) {
    for (unsigned int i{0}; i < numEmp; delete data[i++]);
    delete []data;
}
