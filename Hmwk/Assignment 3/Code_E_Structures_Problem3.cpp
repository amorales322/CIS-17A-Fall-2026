/*
* File: main.cpp
 * Author: Anthony Morales
 * Created on October 8, 2026, 2:23 PM
 * Purpose: Gaddis 9th Ed. Chapter 11 Problem 11
 */

//System Libraries
#include <iostream>
#include <iomanip>
using namespace std;

//User Libraries
struct MthBdgt {
    unsigned int housing;
    unsigned int util;
    unsigned int hseExp;
    unsigned int tnspt;
    unsigned int food;
    unsigned int medical;
    unsigned int insur;
    unsigned int entrmnt;
    unsigned int clothes;
    unsigned int miscel;
};

//Global Constants - No Global Variables
//Only Universal Constants, Math, Physics, Conversions, Higher Dimensions

//Function Prototypes
MthBdgt initBgt();

const char *compBgt(unsigned int, unsigned int);

unsigned int clcBdAm(const MthBdgt &);

void bdgtRpt(const MthBdgt &, const MthBdgt &);

// From Problem 1
unsigned int cnvToP(float);

float cnvToD(unsigned int);

//Execution Begins Here
int main(int argc, char **argv) {
    //Set Random Number seed

    //Declare Variable Data Types and Constants
    MthBdgt maxSpnd{
        cnvToP(500.00f), cnvToP(150.00f), cnvToP(65.00f), cnvToP(50.00f), cnvToP(250.00f), cnvToP(30.00f), cnvToP(100.00f), cnvToP(150.00f), cnvToP(75.00f), cnvToP(50.00f)
    };
    MthBdgt budget;

    //Initialize Variables
    budget = initBgt();

    //Process or map Inputs to Outputs

    //Display Outputs
    bdgtRpt(budget, maxSpnd);

    //Exit stage right!
    return 0;
}

MthBdgt initBgt() {
    MthBdgt budget;
    float temp;

    cout << "Enter housing cost for the month:$\n";
    cin >> temp;
    budget.housing = cnvToP(temp);
    cout << "Enter utilities cost for the month:$\n";
    cin >> temp;
    budget.util = cnvToP(temp);
    cout << "Enter household expenses cost for the month:$\n";
    cin >> temp;
    budget.hseExp = cnvToP(temp);
    cout << "Enter transportation cost for the month:$\n";
    cin >> temp;
    budget.tnspt = cnvToP(temp);
    cout << "Enter food cost for the month:$\n";
    cin >> temp;
    budget.food = cnvToP(temp);
    cout << "Enter medical cost for the month:$\n";
    cin >> temp;
    budget.medical = cnvToP(temp);
    cout << "Enter insurance cost for the month:$\n";
    cin >> temp;
    budget.insur = cnvToP(temp);
    cout << "Enter entertainment cost for the month:$\n";
    cin >> temp;
    budget.entrmnt = cnvToP(temp);
    cout << "Enter clothing cost for the month:$\n";
    cin >> temp;
    budget.clothes = cnvToP(temp);
    cout << "Enter miscellaneous cost for the month:$\n";
    cin >> temp;
    budget.miscel = cnvToP(temp);

    return budget;
}

const char *compBgt(const unsigned int toComp, const unsigned int compWth) {
    if (toComp > compWth)
        return "Over";
    if (toComp == compWth)
        return "Even";
    return "Under";
}

unsigned int clcBdAm(const MthBdgt &budget) {
    unsigned int bdgtAmt{0};

    bdgtAmt += budget.housing;
    bdgtAmt += budget.util;
    bdgtAmt += budget.hseExp;
    bdgtAmt += budget.tnspt;
    bdgtAmt += budget.food;
    bdgtAmt += budget.medical;
    bdgtAmt += budget.insur;
    bdgtAmt += budget.entrmnt;
    bdgtAmt += budget.clothes;
    bdgtAmt += budget.miscel;

    return bdgtAmt;
}

void bdgtRpt(const MthBdgt &toComp, const MthBdgt &compWth) {
    unsigned int maxSpnd{clcBdAm(compWth)};
    unsigned int curSpnd(clcBdAm(toComp));

    cout << "Housing " << compBgt(toComp.housing, compWth.housing) << '\n';
    cout << "Utilities " << compBgt(toComp.util, compWth.util) << '\n';
    cout << "Household Expenses " << compBgt(toComp.hseExp, compWth.hseExp) << '\n';
    cout << "Transportation " << compBgt(toComp.tnspt, compWth.tnspt) << '\n';
    cout << "Food " << compBgt(toComp.food, compWth.food) << '\n';
    cout << "Medical " << compBgt(toComp.medical, compWth.medical) << '\n';
    cout << "Insurance " << compBgt(toComp.insur, compWth.insur) << '\n';
    cout << "Entertainment " << compBgt(toComp.entrmnt, compWth.entrmnt) << '\n';
    cout << "Clothing " << compBgt(toComp.clothes, compWth.clothes) << '\n';
    cout << "Miscellaneous " << compBgt(toComp.miscel, compWth.miscel) << '\n';

    cout << fixed << setprecision(2) << showpoint;
    if (curSpnd > maxSpnd)
        cout << "You were $" << cnvToD(curSpnd - maxSpnd) << " over budget";
    else if (curSpnd < maxSpnd)
        cout << "You were $" << cnvToD(maxSpnd - curSpnd) << " under budget";
}

unsigned int cnvToP(const float val) {
    return static_cast<int>(val * 100);
}

float cnvToD(const unsigned int val) {
    return static_cast<float>(val) / 100;
}
