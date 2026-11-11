#include "Player.h"
#include "fileUtil.h"

Player *newPlyr(fstream &file, const bool frmFile) {
    Player *player = new Player;
    if (frmFile) {
        file.seekp(0, ios::beg);
        read(file, player->nWins);
        read(file, player->nWins);
        read(file, player->name);
    } else {
        player->nWins = 0;
        player->nLoss = 0;
        cout << "Enter your name: ";
        getline(cin, player->name);
    }
    return player;
}

void toFile(fstream &file, Player *player) {
    file.seekp(0, ios::beg);
    write(file, player->nWins);
    write(file, player->nLoss);
    write(file, player->name);
}

void dealloc(Player *player) {
    delete player;
}
