/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 19, 2026, 8:57 PM
 * Purpose:  Gaddis 9th Ed. Chapter 12 Problem 13 - Sports Training Records
 */

// System Libraries
#include <iostream> // Input Output Library
#include <fstream>  // File Handling Library
#include <iomanip>  // Output Formatting Library
using namespace std;

// User Libraries
struct sptRecd {
    unsigned char day;
    unsigned char month;
    unsigned short year;
    float dist;
    unsigned int time;
    unsigned char typeSze;
    // Maximum length - 26 Characters
    char *sptType;
};

// Global Constants not Variables
// Science, Math, Conversions, Dimensions

// Function Prototypes
sptRecd *newRecd(unsigned int &);

void wrteRec(fstream &, sptRecd *, unsigned int);

sptRecd *readRec(fstream &, unsigned int);

void editRec(fstream &, unsigned int);

void prntRec(sptRecd *);

void pntMenu();

void dealloc(sptRecd *);

// Execution begins here at main
int main(int argc, char **argv) {
    // Set random number seed

    // Declare Variables
    fstream recFile{"sports_training_records.bin", ios::in | ios::out | ios::binary};
    unsigned int numRecd{0};
    int usrInpt;

    // Initialize Variables

    // Map/Process the Inputs -> Outputs
    do {
        pntMenu();
        cin >> usrInpt;
        while (usrInpt < 0 || usrInpt > 4) {
            cout << "Invalid Option. Enter new Option: ";
            cin >> usrInpt;
        }

        switch (usrInpt) {
            case 1:
                wrteRec(recFile, newRecd(numRecd), numRecd);
                break;
            case 2:
                if (numRecd == 0)
                    cout << "No records to display.\n\n";
                else {
                    cout << "Input which sports training record you would like to display (1 - " << numRecd << "): ";
                    cin >> usrInpt;
                    while (usrInpt < 1 || usrInpt > numRecd) {
                        cout << "Invalid Option. Enter new Option: ";
                        cin >> usrInpt;
                    }
                    prntRec(readRec(recFile, usrInpt - 1));
                }
                break;
            case 3:
                if (numRecd == 0)
                    cout << "No records to edit.\n\n";
                else {
                    cout << "Input which sports training record you would like to edit (1 - " << numRecd << "): ";
                    cin >> usrInpt;
                    while (usrInpt < 1 || usrInpt > numRecd) {
                        cout << "Invalid Option. Enter new Option: ";
                        cin >> usrInpt;
                    }
                    editRec(recFile, usrInpt - 1);
                }
                break;
            default:
                cout << "Invalid Input.\n\n";
        }
    } while (usrInpt != 4);

    // Display Inputs/Outputs

    // Clean up memory and files

    // Exit the Program
    return 0;
}

sptRecd *readRec(fstream &recFile, const unsigned int index) {
    const int OFFSIZE{40};
    sptRecd *record = new sptRecd;

    recFile.seekg(index * OFFSIZE, ios::beg);
    recFile.read(reinterpret_cast<char *>(&record->day), sizeof(char));
    recFile.read(reinterpret_cast<char *>(&record->month), sizeof(char));
    recFile.read(reinterpret_cast<char *>(&record->year), sizeof(short));
    recFile.read(reinterpret_cast<char *>(&record->dist), sizeof(float));
    recFile.read(reinterpret_cast<char *>(&record->time), sizeof(int));
    recFile.read(reinterpret_cast<char *>(&record->typeSze), sizeof(char));
    recFile.read(reinterpret_cast<char *>(record->sptType), sizeof(char) * record->typeSze)
    )
    ;
    return record;
}

void editRec(fstream &recFile, const unsigned int index) {
    int usrInpt;
    string usrStr;
    sptRecd *record = readRec(recFile, index);

    cout << "1. Day\n";
    cout << "2. Month\n";
    cout << "3. Year\n";
    cout << "4. Distance\n";
    cout << "5. Time\n";
    cout << "6. Sport Type\n\n";
    cout << "Enter which record property you would like to edit: ";
    cin >> usrInpt;
    while (usrInpt < 1 || usrInpt > 6) {
        cout << "Invalid Option. Enter new Option: ";
        cin >> usrInpt;
    }
    switch (usrInpt) {
        case 1:
            cout << "Enter new day: ";
            cin >> usrInpt;
            while (usrInpt < 1 || usrInpt > 31) {
                cout << "Invalid month. Enter new month: ";
                cin >> usrInpt;
            }
            record->day = static_cast<unsigned char>(usrInpt);
            break;
        case 2:
            cout << "Enter new month: ";
            cin >> usrInpt;
            while (usrInpt < 1 || usrInpt > 12) {
                cout << "Invalid month. Enter new month: ";
                cin >> usrInpt;
            }
            record->month = static_cast<unsigned char>(usrInpt);
            break;
        case 3:
            cout << "Enter new year: ";
            cin >> record->year;
            while (record->year < 0) {
                cout << "Invalid year. Enter new year: ";
                cin >> record->year;
            }
            break;
        case 4:
            cout << "Enter new training distance: ";
            cin >> record->dist;
            while (record->dist < 0) {
                cout << "Invalid dist. Enter new training distance: ";
                cin >> record->dist;
            }
            break;
        case 5:
            cout << "Enter new training time: ";
            cin >> usrInpt;
            while (usrInpt < 0) {
                cout << "Invalid time. Enter new training time: ";
                cin >> usrInpt;
            }
            record->time = usrInpt;
            break;
        case 6:
            cout << "Enter new sport type: ";
            cin >> usrStr;
            while (usrStr.length() > 26) {
                cout << "Name of sport type is too long. Must be shorter than 27 characters. Enter new sport type: ";
                cin >> usrStr;
            }
            record->sptType = usrStr.c_str();
            break;
        default:
            cout << "Invalid Option.";
    }

    wrteRec(recFile, record, index);
    dealloc(record);
}

void prntRec(sptRecd *record) {
    cout << record->sptType << ' ' << static_cast<int>(record->month) << '/' << static_cast<int>(record->day) << '/' << record->year << '\n';
    cout << "Distance (mi): " << setprecision(2) << record->dist << '\n';
    cout << "Time (s): " << record->time << "\n\n";

    dealloc(record);
}

void pntMenu() {
    cout << "1. Add new record to file\n";
    cout << "2. Display record\n";
    cout << "3. Edit Record\n";
    cout << "4. Quit\n\n";

    cout << "Enter option: ";
}

void dealloc(sptRecd *record) {
    delete record;
}
