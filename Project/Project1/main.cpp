/*
* File:   main.cpp
 * Author: Anthony Morales
 * Created on October 24, 2026, 1:54 PM
 * Purpose:  Project 1 - Chess
 */

// System Libraries
#include <iostream> // Input Output Library
using namespace std;

// User Libraries
#include "main.h" // Contains function prototypes - will be removed and included here for my final submission

// Global Constants not Variables
// Science, Math, Conversions, Dimensions

// Function Prototypes

// Execution begins here at main
int main(int argc, char **argv) {
    // Set random number seed

    // Declare Variables

    // Initialize Variables

    // Map/Process the Inputs -> Outputs

    // Display Inputs/Outputs

    // Clean up memory and files

    // Exit the Program
    return 0;
}

Array *alloc(const unsigned int size) {
    Array *array = new Array;
    array->size = size;
    array->data = new unsigned char[size];

    return array;
}

void appDta(Array *array, unsigned char newDta) {
    if (array->utilSze >= array->size)
        resize(array);
    array->data[array->utilSze++] = newDta;
}

void appDta(Array *to, Array *from, bool dstryFm) {
    if (to->size < to->utilSze + from->utilSze)
        resize(to, to->utilSze + from->utilSze);
    for (unsigned int i{to->utilSze}; i < to->utilSze + from->utilSze; to->data[i] = from->data[i - to->utilSze], i++);
    if (dstryFm)
        dealloc(from);
}

void resize(Array *array, int newCap) {
    if (newCap == -1) {
        unsigned char *newData = new unsigned char[array->size++];
        for (unsigned int i{0}; i < array->utilSze; newData[i] = array->data[i], i++);
        delete []array->data;
        array->data = newData;
    } else if (newCap > array->size) {
        array->size = newCap;
        unsigned char *newData = new unsigned char[array->size];
        for (unsigned int i{0}; i < array->utilSze; newData[i] = array->data[i], i++);
        delete []array->data;
        array->data = newData;
    }
}

void dealloc(Array *array) {
    delete []array->data;
    delete array;
}

void dealloc(Board *board) {
    for (unsigned int i{0}; i < board->vertSze * board->horznSz; i++)
        dealloc(*(board->board + i / board->horznSz) + i % board->horznSz);
}

void dealloc(Player *player) {
    delete player;
}

void dealloc(Piece *piece) {
    if (piece->vldMove != nullptr)
        dealloc(piece->vldMove);
    if (piece->capPth != nullptr)
        dealloc(piece->capPth);
}
