/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Modified By: Anthony Morales
 * Created on September 22nd, 2021, 1:30 PM
 * Modified on October 8, 2026, 1:01 PM
 * Purpose:  Compare 1 and 2 Dimensional Dynamic Arrays
 */

//System Libraries Here
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions and Array Dimension


//Function Prototypes Here
void fillVec(vector<vector<int> > &, const vector<int> &, int);

vector<int> fil1DVc(int, int, int);

vector<vector<int> > fil2DVec(int, int);

void pnt2DVc(const vector<vector<int> > &);

void pnt1DVc(const vector<int> &, int);

void mrkSort(vector<int> &);

void smlLst(vector<int> &, int);

void swap(int &, int &);

//Program Execution Begins Here
int main(int argc, char **argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare all Variables Here
    int rowsize = 4; //Row size for both 1 and 2 D arrays
    int colsize = 3; //The column size for a 2 dimensional Array
    vector<int> array;
    vector<int> brray;
    vector<int> crray;
    vector<vector<int> > table;

    int lowRng = 100, highRng = 999;
    int perLine = 4;

    //Fill each parallel array
    array = fil1DVc(rowsize, highRng, lowRng);
    brray = fil1DVc(rowsize, highRng / 10, lowRng / 10);
    crray = fil1DVc(rowsize, highRng / 100, lowRng / 100);

    //Sort the array the for all positions
    mrkSort(array);
    mrkSort(brray);
    mrkSort(crray);

    //Fill the 2-D array
    table = fil2DVec(rowsize, colsize);
    fillVec(table, array, 0);
    fillVec(table, brray, 1);
    fillVec(table, crray, 2);

    //Print the values in the array
    pnt1DVc(array, perLine);
    pnt1DVc(brray, perLine);
    pnt1DVc(crray, perLine);
    pnt2DVc(table);

    //Cleanup: Vectors are automatically deallocated

    //Exit
    return 0;
}

void fillVec(vector<vector<int> > &a, const vector<int> &c, const int targCol) {
    for (int row = 0; row < a.size(); row++)
        a[row][targCol] = c[row];
}

vector<int> fil1DVc(int size, const int max, const int min) {
    size = size < 2 ? 2 : size;
    vector<int> a(size);

    for (int indx = 0; indx < size; indx++)
        a[indx] = rand() % (max - min + 1) + min;

    return a;
}

vector<vector<int> > fil2DVec(int nRows, int nCols) {
    nRows = nRows < 2 ? 2 : nRows;
    nCols = nCols < 2 ? 2 : nCols;

    // Initialize and fill with 0's
    vector<vector<int> > a(nRows, vector<int>(nCols, 0));

    return a;
}

void pnt2DVc(const vector<vector<int> > &a) {
    cout << endl << "The Array Values" << endl;
    for (int row = 0; row < a.size(); row++) {
        // Gets the size for the first column, which is the same for all columns
        for (int col = 0; col < a[0].size(); col++)
            cout << setw(4) << a[row][col];

        cout << endl;
    }
}

void pnt1DVc(const vector<int> &a, const int perLine) {
    //Print the values in the array
    cout << endl << "The Array Values" << endl;
    for (int indx = 0; indx < a.size(); indx++) {
        cout << a[indx] << " ";
        if (indx % perLine == (perLine - 1))
            cout << endl;
    }
    cout << endl;
}

void mrkSort(vector<int> &a) {
    for (int pos = 0; pos < a.size() - 1; pos++)
        smlLst(a, pos);
}

void smlLst(vector<int> &a, const int pos) {
    for (int i = pos + 1; i < a.size(); i++) {
        if (a[pos] > a[i])
            swap(a[pos], a[i]);
    }
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}
