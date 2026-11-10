#include "Player.h"

Player *newPlyr() {
    // Todo: Load player from file
    Player *player = new Player;
    player->nWins = 0;
    player->nLoss = 0;

    cout << "Enter your name (35 Characters or Less): ";
    cin.ignore();
    getline(cin, player->name);
    while (player->name.length() > 35) {
        cout << "Your name is too long. Enter a shorter name: ";
        getline(cin, player->name);
    }

    return player;
}

void dealloc(Player *player) {
    delete player;
}
