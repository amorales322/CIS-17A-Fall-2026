/*
* File: main.cpp
 * Author: Anthony Morales
 * Created on October 8, 2026, 1:38 PM
 * Purpose: Code-E: Gaddis 9th Ed. Chapter 11 Problem 3
 */

//System Libraries
#include <iostream>
#include <iomanip>
using namespace std;

//User Libraries
struct CompDiv {
    const char *name;
    // Represented as pennies and stored as an integer
    int q1Sales;
    int q2Sales;
    int q3Sales;
    int q4Sales;

    // Cannot store variables that are dependent on each other inside arrays
    // So I will create a function that calculates total annual sales and average quarterly sales
};

CompDiv initStr(const char []);

float calcTot(const CompDiv &);

float calcAvg(const CompDiv &);

int cnvToP(const float &);

float cnvToD(const int &);

//Global Constants - No Global Variables
//Only Universal Constants, Math, Physics, Conversions, Higher Dimensions

//Function Prototypes

//Execution Begins Here
int main(int argc, char **argv) {
    //Set Random Number seed

    //Declare Variable Data Types and Constants
    CompDiv nthDiv;
    CompDiv sthDiv;
    CompDiv estDiv;
    CompDiv wstDiv;

    //Initialize Variables
    cout << fixed << setprecision(2) << showpoint;
    nthDiv = initStr("North");
    cout << "Total Annual sales:$" << calcTot(nthDiv) << '\n';
    cout << "Average Quarterly Sales:$" << calcAvg(nthDiv) << '\n';
    sthDiv = initStr("West");
    cout << "Total Annual sales:$" << calcTot(sthDiv) << '\n';
    cout << "Average Quarterly Sales:$" << calcAvg(sthDiv) << '\n';
    estDiv = initStr("East");
    cout << "Total Annual sales:$" << calcTot(estDiv) << '\n';
    cout << "Average Quarterly Sales:$" << calcAvg(estDiv) << '\n';
    wstDiv = initStr("South");
    cout << "Total Annual sales:$" << calcTot(wstDiv) << '\n';
    cout << "Average Quarterly Sales:$" << calcAvg(wstDiv);

    //Process or map Inputs to Outputs

    //Display Outputs

    //Exit stage right!
    return 0;
}

CompDiv initStr(const char name[]) {
    CompDiv divData{name};
    float temp;

    cout << divData.name << '\n';
    cout << "Enter first-quarter sales:\n";
    cin >> temp;
    divData.q1Sales = cnvToP(temp);
    cout << "Enter second-quarter sales:\n";
    cin >> temp;
    divData.q2Sales = cnvToP(temp);
    cout << "Enter third-quarter sales:\n";
    cin >> temp;
    divData.q3Sales = cnvToP(temp);
    cout << "Enter fourth-quarter sales:\n";
    cin >> temp;
    divData.q4Sales = cnvToP(temp);

    return divData;
}

float calcTot(const CompDiv &div) {
    return cnvToD(div.q1Sales) + cnvToD(div.q2Sales) + cnvToD(div.q3Sales) + cnvToD(div.q4Sales);
}

float calcAvg(const CompDiv &div) {
    return calcTot(div) / 4;
}

int cnvToP(const float &val) {
    return static_cast<int>(val * 100);
}

float cnvToD(const int &val) {
    return static_cast<float>(val) / 100;
}
