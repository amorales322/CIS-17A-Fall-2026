/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 1, 2026, 9:27 AM
 * Purpose: 1-D Augment - Dynamic Memory Allocation
 */

#include <iostream>
using namespace std;

int *getData(int &);            //Read the array
int *augment(const int *, int); //Augment and copy the original array
void prntAry(const int *, int); //Print the array

int main() {
    int nElem;
    int *array = getData(nElem);
    int *augAry = augment(array, ++nElem);

    prntAry(array, nElem - 1);
    cout << '\n';
    prntAry(augAry, nElem);

    delete []array;
    delete []augAry;
    return 0;
}

int *getData(int &nElem) {
    cin >> nElem;
    int *array = new int[nElem];

    for (int i{0}; i < nElem; i++)
        cin >> array[i];

    return array;
}

int *augment(const int *origAry, int nElem) {
    int *augAry = new int[nElem];

    for (int i{1}; i < nElem; i++)
        augAry[i] = origAry[i - 1];

    return augAry;
}

void prntAry(const int *array, int nElem) {
    for (int i{0}; i < nElem; i++)
        cout << array[i] << (i < nElem - 1 ? " " : "");
}
