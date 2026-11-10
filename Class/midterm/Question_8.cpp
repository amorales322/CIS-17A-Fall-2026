/*
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Modified By: Anthony Morales
 * Modified On: October 28, 2026, 11:18 AM
 * Purpose:  Menu using Functions,
 *           extend for midterm
 */

//System Libraries
#include <iostream> // Input Output Library
#include <iomanip>  // Output Formatting Library
#include <string>   // String Library
#include <cmath>    // C Math Library
using namespace std;

//User Libraries

// Question 1
struct cstmAct {
    unsigned int acctNum;
    string name;
    string address;
    // Represented as pennies - can be negative (overdrawn)
    int balance;
    unsigned int nChkWr;
    unsigned int *chkWrit;
    unsigned int nDepCdt;
    unsigned int *depCdt;
};

// Question 2
struct empInfo {
    string name;
    // 168 Hours in a week
    float hrsWork;
    //Represented as pennies
    int payRate;
};

// Question 7
struct Prime {
    unsigned char power;
    unsigned short prime;
};

struct Primes {
    unsigned short n;
    unsigned char nPrimes;
    Prime *pStrAry; // Prime Array
};

//Global Constants - Math/Physics Constants, Conversions,
//                   2-D Array Dimensions

//Function Prototypes
void menu();

void prblm1();

cstmAct *newCstm();

int cnvToP(float);

float cnvToD(int);

int clcNBal(const cstmAct *);

void pntCstm(const cstmAct *, int);

void pntArry(const unsigned int *, unsigned int);

unsigned int *resize(unsigned int *, unsigned int &, unsigned int);

void dealloc(cstmAct *);

void prblm2();

int calcPay(const empInfo *);

unsigned int numDig(unsigned int);

string engVal(int);

empInfo *newEmp(unsigned int);

void prntChk(const empInfo *, const string &, const string &);

void dealloc(empInfo **, unsigned int);

void prblm3();

void prblm4();

string encrypt(const string &);

void encrNum(char &);

string decrypt(const string &);

void decrNum(char &);

bool valdMes(const string &);

void swap(char &, char &);

void prblm5();

void prblm6();

void prblm7();

Primes *factor(int);

void prtPrms(const Primes *);

bool isPrime(int);

void updPrme(Primes *, int, unsigned int &);

void resize(Primes *, unsigned int &);

void dealloc(Primes *);

//Execution Begins Here
int main(int argc, char **argv) {
    //Declare Variables
    char choice;

    //Loop and Display menu
    do {
        menu();
        cin >> choice;
        cin.ignore();
        //Process/Map inputs to outputs
        switch (choice) {
            case '1':
                prblm1();
                break;
            case '2':
                prblm2();
                break;
            case '3':
                prblm3();
                break;
            case '4':
                prblm4();
                break;
            case '5':
                prblm5();
                break;
            case '6':
                prblm6();
                break;
            case '7':
                prblm7();
                break;
            default:
                cout << "Exiting Menu" << endl;
        }
    } while (choice >= '1' && choice <= '7');

    //Exit stage right!
    return 0;
}

//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
//                         Menu
//Input:  -> Parameters in Argument List, Description/Range/Units
//Output: -> Return, Description/Range/Units
//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
void menu() {
    //Display menu
    cout << endl << "Choose from the following Menu" << endl;
    cout << "Type 1 for Problem 1" << endl;
    cout << "Type 2 for Problem 2" << endl;
    cout << "Type 3 for Problem 3" << endl;
    cout << "Type 4 for Problem 4" << endl;
    cout << "Type 5 for Problem 5" << endl;
    cout << "Type 6 for Problem 6" << endl;
    cout << "Type 7 for Problem 7" << endl << endl;
}

//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
//                         Problem 1
//Input:  -> Parameters in Argument List, Description/Range/Units
//Output: -> Return, Description/Range/Units
//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
void prblm1() {
    // Set random number seed

    // Declare Variables
    cstmAct *cstmr;
    int newBal;

    // Initialize Variables
    cstmr = newCstm();

    // Map/Process the Inputs -> Outputs
    newBal = clcNBal(cstmr);

    // Display Inputs/Outputs
    pntCstm(cstmr, newBal);

    // Clean up memory and files
    dealloc(cstmr);

    // Exit the Program
}

cstmAct *newCstm() {
    // Arbitrary starting size, resizes when needed
    unsigned int size = 10;
    cstmAct *cstmr = new cstmAct;
    float usrInpt;

    cstmr->nChkWr = 0;
    cstmr->chkWrit = new unsigned int[size];
    cstmr->nDepCdt = 0;
    cstmr->depCdt = new unsigned int[size];

    cout << "Enter customer name: ";
    getline(cin, cstmr->name);

    cout << "Enter your address: ";
    getline(cin, cstmr->address);

    cout << "Enter 5-digit account number: ";
    cin >> cstmr->acctNum;
    while (cstmr->acctNum < 10000 || cstmr->acctNum > 99999) {
        cout << "Invalid account number, account number must be 5-digits long. Enter new account number: ";
        cin >> cstmr->acctNum;
    }

    cout << "Enter your starting account balance: ";
    cin >> usrInpt;
    while (cnvToP(usrInpt) <= 0) {
        cout << "Invalid starting balance, starting balance must be greater than 0. Enter a new starting balance: ";
        cin >> usrInpt;
    }
    cstmr->balance = cnvToP(usrInpt);

    do {
        cout << "Enter amount of check written (Enter -1 to stop): ";
        cin >> usrInpt;
        while (cnvToP(usrInpt) <= 0 && cnvToP(usrInpt) != -100) {
            cout << "Invalid check amount, check amount must be greater than 0. Enter new amount: ";
            cin >> usrInpt;
        }
        if (cnvToP(usrInpt) != -100) {
            if (cstmr->nChkWr >= size)
                cstmr->chkWrit = resize(cstmr->chkWrit, size, cstmr->nChkWr);
            cstmr->chkWrit[cstmr->nChkWr++] = cnvToP(usrInpt);
        }
    } while (cnvToP(usrInpt) != -100);

    size = 10;
    do {
        cout << "Enter deposit amount (Enter -1 to stop): ";
        cin >> usrInpt;
        while (cnvToP(usrInpt) <= 0 && cnvToP(usrInpt) != -100) {
            cout << "Invalid deposit amount, deposit amount must be greater than 0. Enter new amount: ";
            cin >> usrInpt;
        }
        if (cnvToP(usrInpt) != -100) {
            if (cstmr->nDepCdt >= size)
                cstmr->depCdt = resize(cstmr->depCdt, size, cstmr->nDepCdt);
            cstmr->depCdt[cstmr->nDepCdt++] = cnvToP(usrInpt);
        }
    } while (cnvToP(usrInpt) != -100);

    return cstmr;
}

int cnvToP(float val) {
    return static_cast<int>(val * 100);
}

float cnvToD(int val) {
    return static_cast<float>(val) / 100;
}

int clcNBal(const cstmAct *const cstmr) {
    int bal{cstmr->balance};

    for (unsigned int i{0}; i < cstmr->nChkWr; bal -= cstmr->chkWrit[i++]);

    for (unsigned int i{0}; i < cstmr->nDepCdt; bal += cstmr->depCdt[i++]);

    return bal - (bal < 0 ? cnvToP(20.0f) : 0);
}

void pntCstm(const cstmAct *const cstmr, const int remBal) {
    // Do not have to calculate this inside the clcNBal() function
    // If the remaining balance is under 0, we can infer that account has been overdrawn
    // Otherwise it wasn't overdrawn if not negative
    bool ovrdft{remBal < 0};

    cout << fixed << showpoint << '\n';
    cout << cstmr->name << '\n';
    cout << "Account Number: " << cstmr->acctNum << '\n';
    cout << "Address: " << cstmr->address << '\n';
    cout << "Initial Balance at Beginning of Month: $" << setprecision(2) << cnvToD(cstmr->balance) << '\n';
    cout << "Check Amounts Written this Month: ";
    pntArry(cstmr->chkWrit, cstmr->nChkWr);
    cout << "Deposits Credited to Account: ";
    pntArry(cstmr->depCdt, cstmr->nDepCdt);
    cout << '\n';

    if (ovrdft)
        cout << "Account was overdrawn, a $20 overdraft fee was applied to your account.\n";
    cout << "Remaining Balance at End of Month: $" << setprecision(2) << cnvToD(remBal) << '\n';
}

void pntArry(const unsigned int *const array, const unsigned int size) {
    for (unsigned int i{0}; i < size; i++)
        cout << '$' << setprecision(2) << cnvToD(array[i]) << (i < size - 1 ? ", " : "");
    cout << '\n';
}

unsigned int *resize(unsigned int *array, unsigned int &size, const unsigned int utilsze) {
    unsigned int *newArry = new unsigned int[++size];
    for (unsigned int i{0}; i < utilsze; newArry[i] = array[i], i++);

    delete []array;
    return newArry;
}

void dealloc(cstmAct *cstmr) {
    delete []cstmr->chkWrit;
    delete []cstmr->depCdt;
    delete cstmr;
}


//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
//                         Problem 2
//Input:  -> Parameters in Argument List, Description/Range/Units
//Output: -> Return, Description/Range/Units
//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
void prblm2() {
    // Set random number seed

    // Declare Variables
    string compNme;
    string compAdd;
    int numEmp;
    empInfo **empData;

    // Initialize Variables
    cout << "Enter company name: ";
    getline(cin, compNme);

    cout << "Enter company address: ";
    getline(cin, compAdd);

    cout << "Enter how many employees you would like to get a weekly check for (Greater than 0): ";
    cin >> numEmp;
    while (numEmp < 1) {
        cout << "Invalid number of employees, number of employees must be greater than 0. Enter a new number of employees: ";
        cin >> numEmp;
    }
    empData = new empInfo *[numEmp];
    cout << '\n';

    // Map/Process the Inputs -> Outputs
    for (int i{0}; i < numEmp; i++)
        empData[i] = newEmp(i + 1);

    // Display Inputs/Outputs
    cout << fixed << showpoint << '\n';
    for (int i{0}; i < numEmp; i++)
        prntChk(empData[i], compNme, compAdd);

    // Clean up memory and files
    dealloc(empData, numEmp);

    // Exit the Program
}

int calcPay(const empInfo *const info) {
    return cnvToP(cnvToD(info->payRate) * (info->hrsWork <= 40 ? info->hrsWork : info->hrsWork < 50 ? 40 + (info->hrsWork - 40) * 2 : 60 + (info->hrsWork - 50) * 3));
}

empInfo *newEmp(const unsigned int empNum) {
    empInfo *empData = new empInfo;
    float usrInpt;

    cout << "Enter Employee #" << empNum << "'s Name: ";
    cin.ignore();
    getline(cin, empData->name);

    cout << "Enter Employee #" << empNum << "'s Hours Worked this Week: ";
    cin >> empData->hrsWork;
    while (empData->hrsWork < 0 || empData->hrsWork > 168) {
        cout << "Hours worked must be between 0 and 168, enter new number of hours worked: ";
        cin >> empData->hrsWork;
    }

    cout << "Enter Employee #" << empNum << "'s Pay Rate: ";
    cin >> usrInpt;
    while (usrInpt < 0) {
        cout << "Pay rate cannot be negative, enter a new pay rate: ";
        cin >> usrInpt;
    }
    empData->payRate = cnvToP(usrInpt);

    cout << '\n';
    return empData;
}

string engVal(const int pay) {
    string onesWrd[]{"One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    string tens[]{"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    string tensWrd[]{"Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

    string englVal;
    int decPart{pay / 100};
    int frcPart{pay % 100};

    unsigned int nDigits;
    unsigned int toCalc;

    while (decPart > 0) {
        nDigits = numDig(decPart);

        if (nDigits == 3)
            englVal += onesWrd[decPart / 100 - 1] + " Hundred ";
        else if (nDigits == 6)
            englVal += onesWrd[decPart / 1000 / 100 - 1] + " Hundred ";
        else if (nDigits == 9)
            englVal += onesWrd[decPart / 1000000 / 100 - 1] + " Hundred ";

        toCalc = decPart / (nDigits <= 3 ? 1 : nDigits <= 6 ? 1000 : 1000000) % 100;
        if (toCalc > 0)
            englVal += (toCalc < 10 ? onesWrd[toCalc - 1] : toCalc < 20 ? tens[toCalc - 10]
                                                                : tensWrd[toCalc / 10 - 2] + (toCalc % 10 == 0 ? "" : " " + onesWrd[toCalc % 10 - 1])) + " ";

        decPart %= nDigits <= 3 ? 1 : nDigits <= 6 ? 1000 : 1000000;
        englVal += nDigits > 3 && nDigits <= 6 ? "Thousand " : nDigits > 6 && nDigits <= 9 ? "Million " : "";
    }
    if (pay / 100 > 0)
        englVal += "and ";
    englVal += frcPart == 0 ? "None/100" : to_string(frcPart) + "/100";

    return englVal;
}

unsigned int numDig(unsigned int val) {
    unsigned int count{0};
    for (; val > 0; count++, val /= 10);
    return count;
}

void prntChk(const empInfo *const data, const string &compNme, const string &compAdd) {
    int pay{calcPay(data)};

    cout << compNme << '\n';
    cout << compAdd << '\n';
    cout << "Pay to the Order Of: " << setw(30) << left << data->name << '$' << setprecision(2) << cnvToD(pay) << '\n';
    cout << engVal(pay) << '\n';
    cout << setw(51) << "For: Paycheck" << "Signature: " << compNme << "\n\n";
}

void dealloc(empInfo **data, const unsigned int numEmp) {
    for (unsigned int i{0}; i < numEmp; delete data[i++]);
    delete []data;
}

//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
//                         Problem 3
//Input:  -> Parameters in Argument List, Description/Range/Units
//Output: -> Return, Description/Range/Units
//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
void prblm3() {
    cout << "Included in StatStructureStub_V1_Problem_3 folder\n";
}

//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
//                         Problem 4
//Input:  -> Parameters in Argument List, Description/Range/Units
//Output: -> Return, Description/Range/Units
//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
void prblm4() {
    // Set random number seed

    // Declare Variables
    string usrInpt;
    string encMess;
    string decMess;

    // Initialize Variables
    cout << "Enter four-digit message you would like to encrypt (0-7 only): ";
    cin >> usrInpt;
    while (!valdMes(usrInpt) || usrInpt.length() != 4) {
        cout << "Invalid message. Enter new message: ";
        cin >> usrInpt;
    }

    // Map/Process the Inputs -> Outputs
    encMess = encrypt(usrInpt);
    decMess = decrypt(encMess);

    // Display Inputs/Outputs
    cout << "\nOriginal Message: " << usrInpt << '\n';
    if (valdMes(encMess)) {
        cout << "Encryted Message: " << encMess << '\n';
        if (valdMes(decMess))
            cout << "Decrypted Message: " << decMess << '\n';
    }

    // Clean up memory and files

    // Exit the Program
}

string encrypt(const string &message) {
    string encrMes{message};

    for (unsigned int i{0}; i < encrMes.length(); i++)
        encrNum(encrMes[i]);
    swap(encrMes[0], encrMes[2]);
    swap(encrMes[1], encrMes[3]);

    if (valdMes(encrMes))
        return encrMes;
    cout << "Encrypted message contains invalid digits. Cannot encrypt message.\n";
    return message;
}

void encrNum(char &num) {
    num -= 48;
    num = (num + 3) % 8;
    num += 48;
}

string decrypt(const string &encMess) {
    string decMess{encMess};

    swap(decMess[1], decMess[3]);
    swap(decMess[0], decMess[2]);
    for (unsigned int i{0}; i < decMess.length(); i++)
        decrNum(decMess[i]);

    if (valdMes(decMess))
        return decMess;
    cout << "Decrypted message contains invalid digits. Message cannot be decrypted.\n";
    return encMess;
}

void decrNum(char &num) {
    num -= 48;
    num = (num + 5) % 8;
    num += 48;
}

bool valdMes(const string &input) {
    for (unsigned int i{0}; i < input.length(); i++)
        if (input[i] < '0' || input[i] > '7')
            return false;
    return true;
}

void swap(char &a, char &b) {
    char temp{a};
    a = b;
    b = temp;
}


//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
//                         Problem 5
//Input:  -> Parameters in Argument List, Description/Range/Units
//Output: -> Return, Description/Range/Units
//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
void prblm5() {
    // Set random number seed

    // Declare Variables
    int b{1};

    // Initialize Variables

    // Map/Process the Inputs -> Outputs

    // Display Inputs/Outputs
    for (long a{1}; a <= 127 / b; a *= ++b);
    cout << "'signed char' max n for n!: " << b << '\n';
    b = 1;
    for (unsigned long a{1}; a <= 255 / b; a *= ++b);
    cout << "'unsigned char' max n for n!: " << b << "\n\n";

    b = 1;
    for (long a{1}; a <= 32'767 / b; a *= ++b);
    cout << "'signed short' max n for n!: " << b << '\n';
    b = 1;
    for (unsigned long a{1}; a <= 65'535 / b; a *= ++b);
    cout << "'unsigned short' max n for n!: " << b << "\n\n";

    b = 1;
    for (long a{1}; a <= 2'147'483'647 / b; a *= ++b);
    cout << "'signed int' max n for n!: " << b << '\n';
    b = 1;
    for (unsigned long a{1}; a <= 4'294'967'295 / b; a *= ++b);
    cout << "'unsigned int' max n for n!: " << b << "\n\n";

    b = 1;
    // 'long' is 64 bits on macOS, which is what I am using
    // It is 32 bits on Windows, which is the same as for 'int'
    for (long a{1}; a <= 9'223'372'036'854'775'807 / b; a *= ++b);
    cout << "'signed long int' max n for n!: " << b << '\n';
    b = 1;
    for (unsigned long a{1}; a <= 18'446'744'073'709'551'615ULL / b; a *= ++b);
    cout << "'unsigned long int' max n for n!: " << b << "\n\n";

    b = 1;
    for (long long a{1}; a <= 9'223'372'036'854'775'807 / b; a *= ++b);
    cout << "'signed long long int' max n for n!: " << b << '\n';
    b = 1;
    for (unsigned long long a{1}; a <= 18'446'744'073'709'551'615U / b; a *= ++b);
    cout << "'unsigned long long int' max n for n!: " << b << '\n';

    b = 1;
    for (long long a{1}; a <= 9'223'372'036'854'775'807 / b; a *= ++b);
    cout << "'signed long long int' max n for n!: " << b << '\n';
    b = 1;
    for (unsigned long long a{1}; a <= 18'446'744'073'709'551'615U / b; a *= ++b);
    cout << "'unsigned long long int' max n for n!: " << b << "\n\n";

    b = 1;
    for (float a{1}; a <= 3.402'823'4e38f / b; a *= ++b);
    cout << "'float' max n for n!: " << b << '\n';
    b = 1;
    for (double a{1}; a <= 1.797'693'134'862'315'7e308 / b; a *= ++b);
    cout << "'double' max n for n!: " << b << '\n';

    // 'long double' is 64 bits on macOS ARM64, which is what I am using
    // On x86 macOS, it is 80 bits
    // On Windows, it is 64 or 128 bits depending on the compiler
    b = 1;
    for (long double a{1}; a <= 1.797'693'134'862'315'7e308L / b; a *= ++b);
    cout << "'long double' max n for n!: " << b << '\n';


    // Clean up memory and files

    // Exit the Program
}

//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
//                         Problem 6
//Input:  -> Parameters in Argument List, Description/Range/Units
//Output: -> Return, Description/Range/Units
//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
void prblm6() {
    // Set random number seed

    // Declare Variables

    // Initialize Variables

    // Map/Process the Inputs -> Outputs

    // Display Inputs/Outputs
    cout << "1a. Decimal: 49.1875\n";
    cout << "Binary: 110001.0011\n";
    cout << "Hexadecimal: 31.3\n";
    cout << "Octal: 61.14\n";
    cout << "NASA Float: 0.1100010 01100000 00000000 00000110\n";
    cout << "NASA Hex: 62 60 00 06\n\n";

    cout << "1b. Decimal: 3.07421875\n";
    cout << "Binary: 11.00010011\n";
    cout << "Hexadecimal: 3.13\n";
    cout << "Octal: 3.046\n";
    cout << "NASA Float: 0.1100010 01100000 00000000 00000010\n";
    cout << "NASA Hex: 62 60 00 02\n\n";


    cout << "1c. Decimal: 0.2\n";
    cout << "Binary: 0.0011...\n";
    cout << "Hexadecimal: 0.4...\n";
    cout << "Octal: 0.1463...\n";
    cout << "NASA Float: 0.0011001 10011001 10011001 00000000\n";
    cout << "NASA Hex: 19 99 99 00\n\n";

    cout << "2a. Decimal: -49.1875\n";
    cout << "Binary: 111111001110.1101 \n";
    cout << "Hexadecimal: FCE.D\n";
    cout << "Octal: 7716.64\n";
    cout << "NASA Float: 1.0011001 10100000 00000000 00000110\n";
    cout << "NASA Hex: 99 A0 00 06\n\n";

    cout << "2b. Decimal: -3.07421875\n";
    cout << "Binary: 11111100.11101101\n";
    cout << "Hexadecimal: FC.ED\n";
    cout << "Octal: 374.732\n";
    cout << "NASA Float: 1.0011101 10100000 00000000 00000010\n";
    cout << "NASA Hex: 9D A0 00 02\n\n";

    cout << "2c. Decimal: -0.2\n";
    cout << "Binary: 1111.110011001101\n";
    cout << "Hexadecimal: F.CCD\n";
    cout << "Octal: 7.6315\n";
    cout << "NASA Float: 1.1100110 01100110 01100111 00000000\n";
    cout << "NASA Hex: E6 66 67 00\n\n";

    cout << "3a. NASA Hex: 69 99 99 02\n";
    cout << "Decimal: 3.30\n\n";

    cout << "3b. NASA Hex: 69 99 99 03\n";
    cout << "Decimal: 6.6\n\n";

    cout << "3c. NASA Hex: 96 66 67 FF\n";
    cout << "Decimal: -0.4125\n\n";

    // Clean up memory and files

    // Exit the Program
}

//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
//                         Problem 7
//Input:  -> Parameters in Argument List, Description/Range/Units
//Output: -> Return, Description/Range/Units
//000000011111111112222222222333333333344444444445555555555666666666677777777778
//345678901234567890123456789012345678901234567890123456789012345678901234567890
void prblm7() {
    // Set random number seed

    // Declare Variables
    int usrInpt;
    Primes *fctr;

    // Map/Process the Inputs -> Outputs
    cout << "Enter the number you would like to calculate the prime factorization for [2, 65000]: ";
    cin >> usrInpt;
    while (usrInpt < 2 || usrInpt > 65000) {
        cout << "Number must be between 2 and 65,000, enter a new number: ";
        cin >> usrInpt;
    }

    fctr = factor(usrInpt);

    // Display Inputs/Outputs
    prtPrms(fctr);

    // Clean up memory and files
    dealloc(fctr);

    // Exit the Program
}

Primes *factor(int value) {
    unsigned int size = 2;
    Primes *primes = new Primes{static_cast<unsigned short>(value), 0, new Prime[size]};

    // Prime Factorization
    int factor{1};
    while (!isPrime(value)) {
        while (value % ++factor != 0);
        updPrme(primes, factor, size);
        value /= factor;
        factor = 1;
    }
    updPrme(primes, value, size);

    return primes;
}

void prtPrms(const Primes *const primes) {
    cout << primes->n << " = ";
    for (int i{0}; i < primes->nPrimes; i++)
        cout << primes->pStrAry[i].prime << '^' << static_cast<int>(primes->pStrAry[i].power) << (i < primes->nPrimes - 1 ? " * " : "");
    cout << '\n';
}

bool isPrime(const int num) {
    if (num <= 1)
        return false;
    if (num == 2 || num == 3 || num == 5)
        return true;
    if (num % 2 == 0 || num % 3 == 0 || num % 5 == 0)
        return false;
    for (int i{7}; i <= static_cast<int>(sqrt(num)); i += 6)
        if (num % i == 0 || num % (i + 4) == 0)
            return false;
    return true;
}

void updPrme(Primes *const primes, const int target, unsigned int &size) {
    bool found{false};

    for (int i{0}; i < primes->nPrimes && !found; i++)
        if (primes->pStrAry[i].prime == target) {
            primes->pStrAry[i].power++;
            found = true;
        }
    if (!found) {
        if (primes->nPrimes >= size)
            resize(primes, size);
        primes->pStrAry[primes->nPrimes].prime = target;
        primes->pStrAry[primes->nPrimes++].power = 1;
    }
}

void resize(Primes *const primes, unsigned int &size) {
    Prime *newData = new Prime[++size];
    for (int i{0}; i < primes->nPrimes; i++)
        newData[i] = primes->pStrAry[i];

    delete []primes->pStrAry;
    primes->pStrAry = newData;
}

void dealloc(Primes *primes) {
    delete []primes->pStrAry;
    delete primes;
}
