/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 1, 2026, 10:37 AM
 * Purpose: Median - Dynamic Memory Allocation
 */

#include <iostream>
#include <iomanip>
using namespace std;

int *getData(int &); //Return the array size and the array
void prntDat(int *, int); //Print the integer array
float *median(int *, int); //Fill the median Array with the Float array size, the median, and the integer array data
void prntMed(float *); //Print the median Array

int main() {
    int nElem;
    int *data = getData(nElem);
    float *medData = median(data, nElem);

    prntDat(data, nElem);
    prntMed(medData);

    delete []data;
    delete []medData;
    return 0;
}

int *getData(int &nElem) {
    cin >> nElem;
    int *array = new int[nElem];

    for (int i{0}; i < nElem; i++)
        cin >> array[i];

    return array;
}

float *median(int *array, int nElem) {
    float *medAry = new float[nElem + 2];
    medAry[0] = static_cast<float>(nElem + 2);
    medAry[1] = nElem % 2 == 0 ? static_cast<float>(array[nElem / 2 - 1] + array[nElem / 2]) / 2.0f : static_cast<float>(array[(nElem - 1) / 2]);

    for (int i{0}; i < nElem; i++)
        medAry[i + 2] = static_cast<float>(array[i]);

    return medAry;
}

void prntDat(int *array, int nElem) {
    for (int i{0}; i < nElem; i++)
        cout << array[i] << (i < nElem - 1 ? " " : "\n");
}

void prntMed(float *array) {
    int nElem{static_cast<int>(array[0])};

    cout << nElem << " ";
    cout << fixed << setprecision(2) << showpoint;
    for (int i{1}; i < nElem; i++)
        cout << array[i] << (i < nElem - 1 ? " " : "");
}
