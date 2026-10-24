/*
* File: main.cpp
 * Author: Anthony Morales
 * Created on October 9, 2026, 10:52 AM
 * Purpose: Structure Drink Machine Simulator
 */

//System Libraries
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//User Libraries
struct drnkIfo {
    const char *name;
    unsigned int cost;
    unsigned int nDrinks;
};

struct drnkMch {
    drnkIfo *drinks;
    unsigned int nDrinks;
};

//Function Prototypes
void dealloc(drnkIfo *);

void prntVals(const drnkMch &);

// From Problem 1
int cnvToP(float);

float cnvToD(int);

int main() {
    //Declare Variable Data Types and Constants
    string usrInpt;
    int intInpt;
    unsigned int nDrinks = 5;
    unsigned int amtEarn{0};

    drnkIfo *drinks = new drnkIfo[nDrinks];
    drnkMch machine = drnkMch{drinks, nDrinks};

    //Initialize Variables
    drinks[0] = drnkIfo{"Cola", 75, 20};
    drinks[1] = drnkIfo{"Root Beer", 75, 20};
    drinks[2] = drnkIfo{"Lemon-Lime", 75, 20};
    drinks[3] = drnkIfo{"Grape Soda", 80, 20};
    drinks[4] = drnkIfo{"Cream Soda", 80, 20};

    //Display Outputs
    do {
        int idx{0};
        bool drinkFd{false};

        prntVals(machine);
        getline(cin, usrInpt);

        if (usrInpt != "Quit") {
            do {
                if (usrInpt == machine.drinks[idx].name) {
                    if (machine.drinks[idx].nDrinks == 0)
                        cout << "The machine is out of " << machine.drinks[idx].name << "enter a new drink option from the menu.\n";
                    else {
                        do {
                            cin >> intInpt;
                        } while (intInpt <= 0 || intInpt > 100);
                        // Ignore whatever remains in buffer - used when mixing getline and cin
                        cin.ignore();

                        machine.drinks[idx].nDrinks--;
                        amtEarn += machine.drinks[idx].cost;
                        drinkFd = true;
                        cout << intInpt - machine.drinks[idx].cost << '\n';
                    }
                }
            } while (usrInpt != machine.drinks[idx++].name && idx < nDrinks);
            if (!drinkFd)
                cout << "Invalid drink option, enter a new drink option from the menu.\n";
        }
    } while (usrInpt != "Quit");
    cout << amtEarn << '\n';

    // Deallocate Memory
    dealloc(drinks);

    //Exit stage right!
    return 0;
}

void dealloc(drnkIfo *machine) {
    delete []machine;
}

void prntVals(const drnkMch &machine) {
    for (int i{0}; i < machine.nDrinks; i++)
        cout << setw(11) << left << machine.drinks[i].name << setw(4) << machine.drinks[i].cost << machine.drinks[i].nDrinks << '\n';
    cout << "Quit\n";
}

int cnvToP(const float val) {
    return static_cast<int>(val * 100);
}

float cnvToD(const int val) {
    return static_cast<float>(val) / 100;
}
