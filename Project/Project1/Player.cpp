#include "Player.h"
#include "fileUtil.h"

Player *newPlyr(fstream &file, const bool frmFile, const size_t plrNum) {
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
        cout << "Player " << plrNum << ", enter your name (a-z, A-Z, and space only): ";
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

void ptPlrSt(const Player *const plyr1, const Player *const plyr2) {
    cout << "\n\n";
    cout << plyr1->name << "'s Stats: ";
    cout << "# Wins: " << plyr1->nWins << '\n';
    cout << "# Losses: " << plyr1->nLoss << '\n';

    cout << plyr2->name << "'s Stats: ";
    cout << "# Wins: " << plyr2->nWins << '\n';
    cout << "# Losses: " << plyr2->nLoss << '\n';
    cout << "\n\n";
}

void dealloc(Player *player) {
    if (player != nullptr)
        delete player;
    player = nullptr;
}
