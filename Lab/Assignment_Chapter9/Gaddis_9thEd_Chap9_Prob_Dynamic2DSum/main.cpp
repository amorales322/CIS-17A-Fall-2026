/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 1, 2026, 9:34 AM
 * Purpose: 2-D Sum - Dynamic Memory Allocation
 */

#include <iostream>
using namespace std;

int **getData(int &, int &);                //Return the 2-D array and its size.
void prntDat(const int *const *, int, int); //Print the 2-D Array
void destroy(int **, int, int);             //Deallocate memory
int sum(const int *const *, int, int);      //Return the Sum

int main() {
    int nRows;
    int nCols;
    int **array = getData(nRows, nCols);

    prntDat(array, nRows, nCols);
    cout << sum(array, nRows, nCols);

    destroy(array, nRows, nCols);
    return 0;
}

int **getData(int &nRows, int &nCols) {
    cin >> nRows >> nCols;
    int **array = new int *[nRows];

    for (int row{0}; row < nRows; row++) {
        array[row] = new int[nCols];
        for (int col{0}; col < nCols; col++)
            cin >> array[row][col];
    }

    return array;
}

void prntDat(const int *const *array, int nRows, int nCols) {
    for (int i{0}; i < nRows * nCols; i++)
        cout << *(*(array + i / nCols) + i % nCols) << (i % nCols < nCols - 1 ? " " : "\n");
}

int sum(const int *const *array, int nRows, int nCols) {
    int total{0};

    for (int i{0}; i < nRows * nCols; i++)
        total += *(*(array + i / nCols) + i % nCols);

    return total;
}

void destroy(int **array, int nRows, int nCols) {
    for (int row{0}; row < nRows; row++)
        delete []array[row];
    delete []array;
}
