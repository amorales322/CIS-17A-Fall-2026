/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 1, 2026, 10:04 AM
 * Purpose: Sum - Dynamic Memory Allocation
 */

#include <iostream>
using namespace std;

int *getData(int &);            //Return the array size and the array from the inputs
int *sumAry(const int *, int);  //Return the array with successive sums
void prntAry(const int *, int); //Print the array

int main() {
    int nElem;
    int *array = getData(nElem);
    int *sumArry = sumAry(array, nElem);

    prntAry(array, nElem);
    cout << '\n';
    prntAry(sumArry, nElem);

    delete []array;
    delete []sumArry;
    return 0;
}

int *getData(int &nElem) {
    cin >> nElem;
    int *array = new int[nElem];

    for (int i{0}; i < nElem; i++)
        cin >> array[i];

    return array;
}

int *sumAry(const int *array, int nElem) {
    int *sumArry = new int[nElem];
    sumArry[0] = array[0];

    for (int i{1}; i < nElem; i++)
        sumArry[i] = sumArry[i - 1] + array[i];

    return sumArry;
}

void prntAry(const int *array, int nElem) {
    for (int i{0}; i < nElem; i++)
        cout << array[i] << (i < nElem - 1 ? " " : "");
}
