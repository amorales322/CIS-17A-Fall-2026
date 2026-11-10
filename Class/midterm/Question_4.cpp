/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 21, 2026, 2:59 PM
 * Purpose: CIS-17A Midterm: Problem 4
 */

// System Libraries
#include <iostream> // Input Output Library
#include <string>   // String Library
using namespace std;

// User Libraries

// Global Constants not Variables
// Science, Math, Conversions, Dimensions

// Function Prototypes
string encrypt(const string &);

void encrNum(char &);

string decrypt(const string &);

void decrNum(char &);

bool valdMes(const string &);

void swap(char &, char &);

// Execution begins here at main
int main(int argc, char **argv) {
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
    return 0;
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
