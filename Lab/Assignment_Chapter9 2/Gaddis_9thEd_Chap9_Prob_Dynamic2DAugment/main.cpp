/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 1, 2026, 8:59 AM
 * Purpose: 2-D Augment - Dynamic Memory Allocation
 */

#include <iostream>
using namespace std;

int **getData(int &, int &);                 //Get the Matrix Data
void printDat(const int *const *, int, int); //Print the Matrix
int **augment(const int *const *, int, int); //Augment the original array
void destroy(int **, int);                   //Destroy the Matrix, i.e., reallocate memory

int main() {
    int nRows;
    int nCols;

    int **array = getData(nRows, nCols);
    int **augAry = augment(array, ++nRows, ++nCols);

    printDat(array, nRows - 1, nCols - 1);
    cout << '\n';
    printDat(augAry, nRows, nCols);

    destroy(augAry, nRows);
    destroy(array, nRows - 1);
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

int **augment(const int *const *origAry, int nRows, int nCols) {
    int **augAry = new int *[nRows];
    augAry[0] = new int[nCols];

    for (int row{1}; row < nRows; row++) {
        augAry[row] = new int[nCols];
        for (int col{1}; col < nCols; col++)
            augAry[row][col] = origAry[row - 1][col - 1];
    }

    return augAry;
}

void printDat(const int *const *array, int nRows, int nCols) {
    for (int i{0}; i < nRows * nCols; i++)
        cout << *(*(array + i / nCols) + i % nCols) << (i % nCols < nCols - 1 ? " " : i / nRows < nRows ? "\n" : "");
}

void destroy(int **array, int nRows) {
    for (int row{0}; row < nRows; row++)
        delete []array[row];

    delete []array;
}
