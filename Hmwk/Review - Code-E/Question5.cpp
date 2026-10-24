/*
 * File:   main.cpp
 * Author: Anthony Morales
 * Created on September 9th, 2026, 1:12 PM
 * Purpose:  Sum Rows, Sum Columns, Grand Sum of an integer array
 */

//System Libraries Here
#include <iostream>//cin,cout
#include <iomanip> //setw(10)
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Allowed like PI, e, Gravity, conversions, array dimensions necessary
const int COLMAX=80;  //Max Columns much larger than needed.

//Function Prototypes Here
void read(int [][COLMAX],int &,int &);//Prompt for size then table
void sum(const int [][COLMAX],int,int,int[][COLMAX]);//Sum rows,col,grand total
void print(const int [][COLMAX],int,int,int);//Either table can be printed

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    const int ROW=80;           //Max Rows much larger than needed
    int array[ROW][COLMAX]={};  //Declare original array
    int augAry[ROW][COLMAX]={}; //Actual augmented table row+1, col+1
    int row,col;

   	cout << "Input a table and output the Augment row,col and total sums.\n";

    //Input the original table
    read(array,row,col);

    //Augment the original table by the sums
    sum(array,row,col,augAry);

    //Output the original array
    cout<<endl<<"The Original Array"<<endl;
    print(array,row,col,10);//setw(10)

    //Output the augmented array
    cout<<endl<<"The Augmented Array"<<endl;
    print(augAry,row+1,col+1,10);//setw(10)

    //Exit
    return 0;
}


void read(int array[][COLMAX], int &numRow, int &numCol) {
	cout << "First input the number of rows and cols. <20 for each\n";

	cin >> numRow >> numCol;

	while (numRow >= 20) {
		cout << "Number of rows is >= 20. Number of rows must be less than 20. Enter a new number of rows\n";
		cin >> numRow;
	}
	while (numCol >= 20) {
		cout << "Number of columns is >= 20. Number of columns must be less than 20. Enter a new number of columns\n";
		cin >> numCol;
	}

	cout << "Now input the table.\n";
	for (int row{0}; row < numRow; row++) {
		for (int col{0}; col < numCol; col++)
			cin >> array[row][col];
	}
}

void sum(const int array[][COLMAX], int numRow, int numCol, int augAry[][COLMAX]) {
	for (int row{0}; row < numRow; row++) {
		for (int col{0}; col < numCol; col++) {
			augAry[row][col] = array[row][col];
			augAry[numRow][col] += array[row][col];
			augAry[row][numCol] += array[row][col];
			augAry[numRow][numCol] += array[row][col];
		}
	}
}

void print(const int array[][COLMAX], int numRow, int numCol, int elmWdth) {
	for (int row{0}; row < numRow; row++) {
		for (int col{0}; col < numCol; col++) {
			cout << setw(elmWdth) << array[row][col];
			if (col == numCol - 1)
				cout << '\n';
		}
	}
}
