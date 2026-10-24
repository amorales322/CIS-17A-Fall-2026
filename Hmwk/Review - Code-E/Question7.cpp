/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on September 9th, 2026, 2:30 PM
 * Purpose:  Input something, output it reversed with some modifications
 * Note:Range should be 5 digits, 321 = 00321 reverse = 12300 before subtraction
 *      12300 - 999 = 11301 after subtraction
 *      12300 = 00321 = 321 after reversal and no subtraction
 */

//System Libraries Here
#include <cmath>
#include <iostream>//cin,cout,endl
#include <cstring> //strlen()
#include <math.h>
using namespace std;
//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
bool inRange(const char [], unsigned short &); //Output true,unsigned or false
bool reverse(unsigned short, signed short &); //Output true,short or false
short subtrct(signed short, int);

//Program Execution Begins Here
int main(int argc, char **argv) {
    //Declare all Variables Here
    const int SIZE = 80; //More than enough
    char digits[SIZE]; //Character digits or not
    unsigned short unShort; //Unsigned short
    short snShort; //Signed short

    //Input or initialize values Here
    cout << "Reverse a number and subtract if possible." << endl;
    cout << "Input a number in the range of an unsigned short" << endl;
    cin >> digits;

    //Test if it is in the Range of an unsigned short
    if (!inRange(digits, unShort)) {
        cout << "No Conversion Possible" << endl;
        return 0;
    }

    //Reverse and see if it falls in the range of an signed short
    if (!reverse(unShort, snShort)) {
        cout << "No Conversion Possible" << endl;
        return 0;
    }

    //Now subtract if the result is not negative else don't subtract
    snShort = subtrct(snShort, 999);

    //Output the result
    cout << snShort << endl;

    //Exit
    return 0;
}

bool inRange(const char inNum[], unsigned short &outNum) {
    int numLen{static_cast<int>(strlen(inNum))};
    int calcBuf{0};
    unsigned short pow{1};

    if (numLen > 5 || inNum[0] > 54)
        return false;

    for (int i{0}; i < numLen - 1; i++)
        pow *= 10;

    for (int i{0}; i < numLen; i++, pow /= 10) {
        if (inNum[i] > 57 || inNum[i] < 48)
            return false;
        calcBuf += (inNum[i] - 48) * pow;
        // Unsigned Short Max
        if (calcBuf > 65535)
            return false;
    }
    outNum = static_cast<short>(calcBuf);
    return true;
}

bool reverse(unsigned short inNum, signed short &outNum) {
    int calcBuf{0};

    for (int i{1}, multFac{10000}; i <= 5; i++, multFac /= 10, inNum /= 10) {
        calcBuf += inNum % 10 * multFac;
        if (calcBuf > 32767)
            return false;
    }
    outNum = static_cast<short>(calcBuf);
    return true;
}

short subtrct(signed short num, int subBy) {
    if (num >= subBy)
        return num - subBy;
    return num;
}
