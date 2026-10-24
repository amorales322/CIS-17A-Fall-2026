/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 17, 2026, 10:44 AM
 * Purpose:  Gaddis 9th Ed. Chapter 12 Problem 8 - Sorting a File of Records
 */

// System Libraries
#include <iostream> // Input Output Library
#include <fstream>  // File Stream Library
using namespace std;

// User Libraries
struct empData {
    string frstNme;
    string lstName;
    unsigned short age;
};

// Global Constants not Variables
// Science, Math, Conversions, Dimensions

// Function Prototypes
empData *readRec(ifstream &);

void wrteRec(ofstream &, const empData *const *, unsigned int);

void sortRec(empData **, unsigned int);

void swap(empData **, unsigned int, unsigned int);

void dealloc(empData **, unsigned int);


// Execution begins here at main
int main(int argc, char **argv) {
    // Set random number seed

    // Declare Variables
    unsigned int nRecord{10};
    empData **data = new empData *[nRecord];
    ifstream inFile{"emp_age.txt"};
    ofstream outFile{"sort_age.txt"};

    // Initialize Variables

    // Map/Process the Inputs -> Outputs
    for (unsigned int i{0}; i < nRecord; i++)
        data[i] = readRec(inFile);

    sortRec(data, nRecord);

    wrteRec(outFile, data, nRecord);

    // Display Inputs/Outputs

    // Clean up memory and files
    inFile.close();
    outFile.close();
    dealloc(data, nRecord);

    // Exit the Program
    return 0;
}

empData *readRec(ifstream &inFile) {
    empData *data = new empData;

    inFile >> data->frstNme;
    inFile >> data->lstName;
    inFile >> data->age;

    return data;
}

void wrteRec(ofstream &outFile, const empData *const *const data, const unsigned int size) {
    for (unsigned int i{0}; i < size; i++)
        outFile << data[i]->frstNme << ' ' << data[i]->lstName << ' ' << data[i]->age << '\n';
}

void sortRec(empData **const data, const unsigned int size) {
    // Bubble sort
    bool sorted{false};
    do {
        sorted = false;
        for (unsigned int i{0}; i < size - 1; i++)
            if (data[i]->age < data[i + 1]->age) {
                swap(data, i, i + 1);
                sorted = true;
            }
    } while (sorted);
}

void swap(empData **const data, const unsigned int a, const unsigned int b) {
    empData *temp = data[a];
    data[a] = data[b];
    data[b] = temp;
}

void dealloc(empData **data, const unsigned int size) {
    for (unsigned int i{0}; i < size; i++)
        delete data[i];

    delete []data;
}
