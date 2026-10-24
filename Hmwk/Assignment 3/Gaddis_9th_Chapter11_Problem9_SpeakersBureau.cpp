/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 14, 2026, 1:59 PM
 * Purpose:  Gaddis 9th Ed. Chapter 11 Problem 9 Speakers Bureau
 */

// System Libraries
#include <iostream> // Input Output Library
#include <string>   // String Library
#include <cctype>
using namespace std;

// User Libraries
struct speaker {
    string name;
    string number;
    string topic;
    int fee;
};

struct spkrDta {
    speaker *data;
    unsigned int size;
    unsigned int utilsze;
};

// Global Constants not Variables
// Science, Math, Conversions, Dimensions

// Function Prototypes
spkrDta initDta(int);

void newEtry(spkrDta &);

void modEtry(spkrDta &);

void delEtry(spkrDta &);

void rszeDta(spkrDta &);

void prtMenu(int);

void prntDta(const spkrDta &);

void dealloc(spkrDta &);

// Execution begins here at main
int main(int argc, char **argv) {
    // Set random number seed

    // Declare Variables
    const int initSze{10};
    char usrChce;

    spkrDta data = initDta(initSze);

    // Initialize Variables

    // Map/Process the Inputs -> Outputs

    // Display Inputs/Outputs
    do {
        prtMenu(data.utilsze);
        cin >> usrChce;
        usrChce = static_cast<char>(toupper(usrChce));

        switch (usrChce) {
            case 'N':
                newEtry(data);
                break;
            case 'E':
                modEtry(data);
                break;
            case 'P':
                prntDta(data);
                break;
            case 'D':
                delEtry(data);
                break;
            case 'X':
                break;
            default:
                cout << "Invalid option.\n\n";
        }
    } while (usrChce != 'X');

    // Clean up memory and files
    dealloc(data);

    // Exit the Program
    return 0;
}

spkrDta initDta(const int size) {
    spkrDta data;

    data.size = size;
    data.utilsze = 0;
    data.data = new speaker[size];

    return data;
}

void newEtry(spkrDta &data) {
    if (data.utilsze >= data.size)
        rszeDta(data);

    speaker newDta;
    cout << "Enter the name for the speaker: ";
    cin.ignore();
    getline(cin, newDta.name);
    cout << "Enter the telephone number for " << newDta.name << ": ";
    getline(cin, newDta.number);
    cout << "Enter " << newDta.name << "'s speaking topic: ";
    getline(cin, newDta.topic);
    cout << "Enter " << newDta.name << "'s fee: ";
    cin >> newDta.fee;
    while (newDta.fee < 0) {
        cout << "Fee cannot be less than 0. Enter a new amount: ";
        cin >> newDta.fee;
    }

    data.data[data.utilsze++] = newDta;
}

void modEtry(spkrDta &data) {
    char usrChr;
    int toMod;

    if (data.utilsze == 0)
        cout << "No entries to modify.\n";
    else {
        prntDta(data);
        cout << "Which entry would you like to modify: ";
        cin >> toMod;
        while (toMod < 1 || toMod > data.utilsze) {
            cout << "Invalid option. Please select an option between 1 and " << data.utilsze << ": ";
            cin >> toMod;
        }
        toMod--;

        cout << "Which datapoint would you like to modify (N: Name, P: Phone Number, T: Topic, F: Fee): ";
        cin >> usrChr;
        usrChr = static_cast<char>(toupper(usrChr));
        while (usrChr != 'N' && usrChr != 'P' && usrChr != 'T' && usrChr != 'F') {
            cout << "Invalid option. Enter a new option: ";
            cin >> usrChr;
            usrChr = static_cast<char>(toupper(usrChr));
        }

        switch (usrChr) {
            case 'N':
                cout << "Enter new name for speaker #" << toMod + 1 << ": ";
                cin.ignore();
                getline(cin, data.data[toMod].name);
                break;
            case 'P':
                cout << "Enter new phone number for " << data.data[toMod].name << ": ";
                cin.ignore();
                getline(cin, data.data[toMod].number);
                break;
            case 'T':
                cout << "Enter new topic for " << data.data[toMod].name << ": ";
                cin.ignore();
                getline(cin, data.data[toMod].topic);
                break;
            default:
                cout << "Enter new fee amount for " << data.data[toMod].name << ": ";
                cin >> data.data[toMod].fee;
                while (data.data[toMod].fee < 0) {
                    cout << "Fee cannot be less than 0. Enter a new amount: ";
                    cin >> data.data[toMod].fee;
                }
        }
    }
}

void delEtry(spkrDta &data) {
    int toDel;

    if (data.utilsze == 0)
        cout << "No entries to delete.\n";
    else {
        prntDta(data);
        cout << "Enter which entry you woud like to delete: ";
        cin >> toDel;
        while (toDel < 1 || toDel > data.utilsze + 1) {
            cout << "Invalid entry. Enter new entry: ";
            cin >> toDel;
        }

        for (int i{--toDel}; i < data.utilsze - 1; i++)
            data.data[i] = data.data[i + 1];
        data.utilsze--;
    }
}

void rszeDta(spkrDta &data) {
    speaker *newDta = new speaker[++data.size];
    for (int i{0}; i < data.utilsze; i++)
        newDta[i] = data.data[i];

    delete []data.data;
    data.data = newDta;
}

void prtMenu(const int numEtry) {
    cout << "Speakers' Bureau Information\n";
    cout << "\tN: New Entry (Current Entry Count: " << numEtry << ")\n";
    cout << "\tE: Edit Entry\n";
    cout << "\tD: Delete Entry\n";
    cout << "\tP: Print Entries\n";
    cout << "\tX: Exit\n\n";
    cout << "Enter Option: ";
}

void prntDta(const spkrDta &data) {
    if (data.utilsze == 0)
        cout << "No entries.";
    else {
        cout << "Speakers' Bureau Information\n";
        for (int i{0}; i < data.utilsze; i++) {
            cout << i + 1 << ". " << data.data[i].name << '\n';
            cout << "\tPhone Number: " << data.data[i].number << '\n';
            cout << "\tSpeaking Topic: " << data.data[i].topic << '\n';
            cout << "\tFee: " << data.data[i].fee << '\n';
        }
    }

    cout << '\n';
}

void dealloc(spkrDta &data) {
    delete []data.data;
}
