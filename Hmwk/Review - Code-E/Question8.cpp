/*
 * File: main.cpp
 * Author: Anthony Morales
 * Created on September 9th, 2026, 3:31 PM
 * Note:  This time you create the strcmp() function that takes into
 * account the new sort order.
 */

//System Libraries Here
#include <iostream>//cin,cout
#include <cstring> //strlen(),strcmp(),strcpy()
using namespace std;

//Global Constants Only, No Global Variables
//Allowed like PI, e, Gravity, conversions, array dimensions necessary
const int COLMAX = 80; //Only 20 required, and 1 for null terminator

//Function Prototypes Here
int read(char [][COLMAX], int &); //Outputs row and columns detected from input
void sort(char [][COLMAX], int, int, const char [], const char []); //Sort by row using strcmp();
void print(const char [][COLMAX], int, int); //Print the sorted 2-D array
//int strcmp(char a[],char b[],char replace[],char with[]){
int strcmp(char [], char [], const char [], const char []); //Replace sort order

//Program Execution Begins Here
int main(int argc, char **argv) {
    //Declare all Variables Here
    const int ROW = 30; //Only 20 required
    char array[ROW][COLMAX]; //Bigger than necessary
    int colIn, colDet, rowIn, rowDet; //Row, Col input and detected
    char replace[COLMAX], with[COLMAX]; //New sort order

    //Input the new sort order then sort
    cout << "Modify the sort order by swapping these characters." << endl;
    cin >> replace;
    cout << "With the following characters" << endl;
    cin >> with;
    cout << "Read in a 2 dimensional array of characters and sort by Row" << endl;
    cout << "Input the number of rows <= 20" << endl;
    cin >> rowIn;
    cout << "Input the maximum number of columns <=20" << endl;
    cin >> colIn;

    //Now read in the array of characters and determine it's size
    rowDet = rowIn;
    cout << "Now input the array." << endl;
    colDet = read(array, rowDet);

    //Compare the size input vs. size detected and sort if same
    //Else output different size
    if (rowDet == rowIn && colDet == colIn) {
        sort(array, rowIn, colIn, replace, with);
        cout << "The Sorted Array" << endl;
        print(array, rowIn, colIn);
    } else {
        if (rowDet != rowIn)
            cout << (rowDet < rowIn ? "Row Input size less than specified." : "Row Input size greater than specified.") << endl;
        if (colDet != colIn)
            cout << (colDet < colIn ? "Column Input size less than specified." : "Column Input size greater than specified.") << endl;
    }
    //Exit
    return 0;
}

int read(char array[][COLMAX], int &numRows) {
    int numCols{0};
    numRows = 0;

    while (cin >> array[numRows]) {
        if (strlen(array[numRows]) > numCols)
            numCols = strlen(array[numRows]);
        numRows++;
    }
    return numCols;
}

void sort(char array[][COLMAX], int nRows, int nCols, const char replace[], const char with[]) {
    bool wasSort{false};
    char buffer[COLMAX];
    int compRes;

    do {
        wasSort = false;
        for (int row{0}; row < nRows - 1; row++) {
            compRes = strcmp(array[row], array[row + 1], replace, with);

            if (compRes > 0) {
                strcpy(buffer, array[row]);
                strcpy(array[row], array[row + 1]);
                strcpy(array[row + 1], buffer);
                wasSort = true;
            }
        }
    } while (wasSort);
}

void print(const char array[][COLMAX], int nRows, int nCols) {
    for (int row{0}; row < nRows; row++) {
        cout << array[row] << '\n';
    }
}

int strcmp(char a[], char b[], const char replace[], const char with[]) {
    char tempa[COLMAX];
    char tempb[COLMAX];
    int repLen{static_cast<int>(strlen(replace))};
    int aLen{static_cast<int>(strlen(a))};
    int bLen{static_cast<int>(strlen(b))};

    strcpy(tempa, a);
    strcpy(tempb, b);


    for (int i{0}; i < aLen; i++) {
        for (int j{0}; j < repLen; j++) {
            if (tempa[i] == replace[j]) {
                tempa[i] = with[j];
                j = repLen;
            }
        }
    }
    for (int i{0}; i < bLen; i++) {
        for (int j{0}; j < repLen; j++) {
            if (tempb[i] == replace[j]) {
                tempb[i] = with[j];
                j = repLen;
            }
        }
    }

    return strcmp(tempa, tempb);
}
