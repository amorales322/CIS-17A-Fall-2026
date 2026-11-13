/*
* File:   Player.h
 * Author: Anthony Morales
 * Created on October 24, 2026, 1:54 PM
 * Purpose:  Project 1 - Chess
 */

#ifndef PLAYER_H
#define PLAYER_H

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
