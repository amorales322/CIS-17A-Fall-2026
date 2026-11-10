#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
using namespace std;

struct Player {
    unsigned short nWins;
    unsigned short nLoss;
    string name;
};

Player *newPlyr();

void dealloc(Player *);

#endif
