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

Player *newPlyr(fstream &, bool);

void toFile(fstream &, Player *);

void dealloc(Player *);

#endif
