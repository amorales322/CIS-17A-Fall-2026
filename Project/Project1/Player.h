#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct Player {
    unsigned short nWins;
    unsigned short nLoss;
    string name;
};

Player *newPlyr(fstream &, bool, size_t);

void toFile(fstream &, Player *);

// Prints player statistics
void ptPlrSt(const Player *, const Player *);

void dealloc(Player *);

#endif
