/*
 * File: main.cpp
 * Author: Anthony Morales
 * Created on September 9th, 2026, 1:41 PM
 * Purpose:  Searching for multiple occurrence of patterns
 * Note:  cout proceeds to null terminator, cin reads to end of line
 *        for character arrays
 *
 */

//System Libraries Here
#include <iostream>//cin,cout,getline()
#include <cstring> //strlen()
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//PI, e, Gravity, or conversions

//Function Prototypes Begins Here
//srch1 utility function Input->start position, Output->position found or not
//srch1 is a simple linear search function, repeat in srchAll till all found
//srch1 Input->sentence, pattern, start position Output-> position found
//Remember arrays start at index/position 0
//srchAll Input->sentence, pattern Output->position array
int srch1(const char [], const char [], int); //Search for 1 occurrence
void srchAll(const char [], const char [], int []); //Search for all occurrences
void print(const char []); //Print the character arrays
void print(const int []); //Print the array of indexes where the pattern found

//Program Execution Begins Here
int main(int argc, char **argv) {
    //Declare all Variables Here
    const int LINE = 81; //Size of sentence or pattern to find
    char sntnce[LINE], pattern[LINE]; //80 + null terminator
    int match[LINE]; //Index array where pattern was found

    //Input a sentence and a pattern to match
    cout << "Match a pattern in a sentence." << endl;
    cout << "Input a sentence" << endl;
    cin.getline(sntnce, LINE);
    cout << "Input a pattern." << endl;
    cin.getline(pattern, LINE);

    //Search for the pattern
    //Input the sentence and pattern, Output the matching positions
    //Remember, indexing starts at 0 for arrays.
    srchAll(sntnce, pattern, match);

    //Display the inputs and the Outputs
    cout << endl << "The sentence and the pattern" << endl;
    print(sntnce);
    print(pattern);
    cout << "The positions where the pattern matched" << endl;
    print(match);

    //Exit
    return 0;
}

int srch1(const char sntnce[], const char pattern[], int strtIdx) {
    int ptrnLen{static_cast<int>(strlen(pattern))};
    int stceLen{static_cast<int>(strlen(sntnce))};
    int i{strtIdx};

    // This for loop follows two conditions
    // 1. The loop stays within the bounds of the potential substring (i < startingIndex + patternLength)
    // 2. The loop does not attempt index outside the bounds of the sentence (i < sentenceLength)
    for (int j{0}; i < strtIdx + ptrnLen && i < stceLen; i++, j++) {
        // Exit loop early if match is not found
        // Sets the index equal to sentence length + 1, so if a potential substring runs up to the end of the sentence
        // If the last character in substring and sentence do not match, it will not return a false positive
        if (sntnce[i] != pattern[j])
            i = stceLen + 1;
    }
    if (i == strtIdx + ptrnLen)
        return 1;
    return 0;
}

void srchAll(const char sntnce[], const char pattern[], int matches[]) {
    int srchLen{static_cast<int>(strlen(sntnce))};
    int numMchs{0};
    int match;

    matches[0] = -1;

    for (int i{0}; i < srchLen; i++) {
        if (sntnce[i] == pattern[0]) {
            match = srch1(sntnce, pattern, i);

            if (match == 1) {
                matches[numMchs++] = i;
                matches[numMchs] = -1;
            }
        }
    }
}

void print(const char subStr[]) {
    cout << subStr << '\n';
}

void print(const int array[]) {
    int i{0};
    if (array[0] == -1)
        cout << "None\n";
    else {
        while (array[i] != -1)
            cout << array[i++] << '\n';
    }
}
