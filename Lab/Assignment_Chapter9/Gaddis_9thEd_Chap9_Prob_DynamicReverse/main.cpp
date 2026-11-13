/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 1, 2026, 10:15 AM
 * Purpose:  Reverse - Dynamic Memory Allocation
 */

#include <iostream>
using namespace std;

int *getData(int &);            //Fill the array
int *sort(const int *, int);    //Sort smallest to largest
int *reverse(const int *, int); //Sort in reverse order
void prntDat(const int *, int); //Print the array

int main() {
    int nElem;
    int *array = getData(nElem);
    int *sortAry = sort(array, nElem);
    int *revAry = reverse(array, nElem);

    prntDat(sortAry, nElem);
    cout << '\n';
    prntDat(revAry, nElem);

    delete []array;
    delete []sortAry;
    delete []revAry;

    return 0;
}

int *getData(int &nElem) {
    cin >> nElem;
    int *array = new int[nElem];

    for (int i{0}; i < nElem; i++)
        cin >> array[i];

    return array;
}

int *sort(const int *oldAry, int nElem) {
    int *newAry = new int[nElem];
    int temp;
    bool sorted;

    for (int i{0}; i < nElem; i++)
        newAry[i] = oldAry[i];

    do {
        sorted = false;
        for (int i{0}; i < nElem - 1; i++) {
            if (newAry[i] > newAry[i + 1]) {
                temp = newAry[i];
                newAry[i] = newAry[i + 1];
                newAry[i + 1] = temp;
                sorted = true;
            }
        }
    } while (sorted);

    return newAry;
}

int *reverse(const int *oldAry, int nElem) {
    int *newAry = new int[nElem];
    int temp;
    bool sorted;

    for (int i{0}; i < nElem; i++)
        newAry[i] = oldAry[i];

    do {
        sorted = false;
        for (int i{0}; i < nElem - 1; i++) {
            if (newAry[i] < newAry[i + 1]) {
                temp = newAry[i];
                newAry[i] = newAry[i + 1];
                newAry[i + 1] = temp;
                sorted = true;
            }
        }
    } while (sorted);

    return newAry;
}

void prntDat(const int *array, int nElem) {
    for (int i{0}; i < nElem; i++)
        cout << array[i] << (i < nElem - 1 ? " " : "");
}
