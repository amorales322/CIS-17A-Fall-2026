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
        bool vldInpt{true};
        player->nWins = 0;
        player->nLoss = 0;
        cout << "Enter your name (a-z, A-Z, and space only): ";
        getline(cin, player->name);
        do {
            vldInpt = true;
            for (size_t i{0}; i < player->name.length(); i++)
                if (!(toupper(player->name[i]) >= 65 && toupper(player->name[i]) <= 90) && player->name[i] != 32)
                    vldInpt = false;

            if (!vldInpt) {
                cout << "Invalid name, enter new name: ";
                getline(cin, player->name);
            }
        } while (!vldInpt);
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
