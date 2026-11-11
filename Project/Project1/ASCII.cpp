#include "ASCII.h"

/*
 * Utility
 */
size_t clcLftW(size_t width) {
    return width % 2 == 0 ? width / 2 : width / 2 + 1;
}

size_t clcRgtW(size_t width) {
    return width / 2;
}

string getBlnk(const size_t width, const bool ligtCel) {
    return string(width, ligtCel ? '#' : ' ');
}

string getBlnk(const size_t width, const char fillChr) {
    return string(width, fillChr);
}

void drwBlRw(const bool lghtCel) {
    cout << '|' << getBlnk(23, lghtCel);
}

void drClmRw(const char *content, const bool lghtCel) {
    static const size_t width{23};
    size_t remWdth{width - strlen(content) - 2};
    size_t lftWdth{clcLftW(remWdth)};
    size_t rgtWdth{clcRgtW(remWdth)};

    // Print cell row
    cout << '|' << getBlnk(lftWdth, lghtCel) << ' ' << content << ' ' << getBlnk(rgtWdth, lghtCel);
}

void drawNum(const char *content, const size_t width) {
    size_t remWdth{width - strlen(content) - 1};
    size_t lftWdth{clcLftW(remWdth)};
    size_t rgtWdth{clcRgtW(remWdth)};

    // Print cell row
    cout << getBlnk(lftWdth, false) << ' ' << content << ' ' << getBlnk(rgtWdth, false);
}

void drClmRw(const char *left, const char *right, const size_t inrWdth, const bool lghtCel, const char filChar) {
    static const size_t width{23};
    size_t remWdth{width - inrWdth - strlen(left) - strlen(right) - 2};
    size_t lftWdth{clcLftW(remWdth)};
    size_t rgtWdth{clcRgtW(remWdth)};

    // Print cell row
    cout << '|' << getBlnk(lftWdth, lghtCel) << ' ' << left << getBlnk(inrWdth, filChar) << right << ' ' << getBlnk(rgtWdth, lghtCel);
}

void drClmRw(const char *left, const char *right, const size_t inrWdth, const bool lghtCel, const PlyrClr &player) {
    static const size_t width{23};
    size_t remWdth{width - inrWdth - strlen(left) - strlen(right) - 2};
    size_t lftWdth{clcLftW(remWdth)};
    size_t rgtWdth{clcRgtW(remWdth)};

    // Print cell row
    cout << '|' << getBlnk(lftWdth, lghtCel) << ' ' << left << (player == PlyrClr::WHITE ? getBlnk(inrWdth, '#') : getBlnk(inrWdth, ' ')) << right << ' ' <<
            getBlnk(rgtWdth, lghtCel);
}

void drClmRw(const char *left, const char *right, const size_t inrWdth, const bool lghtCel, const PlyrClr &player, const char filChar) {
    static const size_t width{23};
    size_t remWdth{width - inrWdth - strlen(left) - strlen(right) - 2};
    size_t lftWdth{clcLftW(remWdth)};
    size_t rgtWdth{clcRgtW(remWdth)};

    // Print cell row
    cout << '|' << getBlnk(lftWdth, lghtCel) << ' ' << left << (player == PlyrClr::WHITE ? getBlnk(inrWdth, '#') : getBlnk(inrWdth, filChar)) << right << ' ' <<
            getBlnk(rgtWdth, lghtCel);
}

/*
 * Letters
 * https://www.asciiart.eu/text-to-ascii-art
 */
void drawA(const size_t row) {
    switch (row) {
        case 3:
            drawNum("_");
            break;
        case 4: //
            drawNum("/ \\");
            break;
        case 5:
            drawNum("/ _ \\");
            break;
        case 6:
            drawNum("/ ___ \\");
            break;
        case 7:
            drawNum("/_/   \\_\\");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void drawB(const size_t row) {
    switch (row) {
        case 3:
            drawNum("____");
            break;
        case 4: //
            drawNum("| __ )");
            break;
        case 5:
            drawNum("|  _ \\");
            break;
        case 6:
            drawNum("| |_) |");
            break;
        case 7:
            drawNum("|____/");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void drawC(const size_t row) {
    switch (row) {
        case 3:
            drawNum("____");
            break;
        case 4: //
            drawNum("/ ___|");
            break;
        case 5:
            drawNum("| |     ");
            break;
        case 6:
            drawNum("| |___  ");
            break;
        case 7:
            drawNum("\\____|");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void drawD(const size_t row) {
    switch (row) {
        case 3:
            drawNum("____");
            break;
        case 4: //
            drawNum("|  _ \\");
            break;
        case 5:
            drawNum("| | | |");
            break;
        case 6:
            drawNum("| |_| |");
            break;
        case 7:
            drawNum("|____/");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void drawE(const size_t row) {
    switch (row) {
        case 3:
            drawNum("_____");
            break;
        case 4: //
            drawNum("| ____|");
            break;
        case 5:
            drawNum("|  _| ");
            break;
        case 6:
            drawNum("| |___");
            break;
        case 7:
            drawNum("|_____|");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void drawF(const size_t row) {
    switch (row) {
        case 3:
            drawNum("_____");
            break;
        case 4: //
            drawNum("|  ___|");
            break;
        case 5:
            drawNum("| |_  ");
            break;
        case 6:
            drawNum("|  _| ");
            break;
        case 7:
            drawNum("|_|   ");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void drawG(const size_t row) {
    switch (row) {
        case 3:
            drawNum("____");
            break;
        case 4: //
            drawNum("/ ___|");
            break;
        case 5:
            drawNum("| |  _  ");
            break;
        case 6:
            drawNum("| |_| |  ");
            break;
        case 7:
            drawNum("\\____|");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void drawH(const size_t row) {
    switch (row) {
        case 3:
            drawNum("_   _");
            break;
        case 4: //
            drawNum("| | | |");
            break;
        case 5:
            drawNum("| |_| |");
            break;
        case 6:
            drawNum("|  _  |");
            break;
        case 7:
            drawNum("|_| |_|");
            break;
        default:
            cout << getBlnk(24, false);
    }
}


/*
 * Numbers
 */
void draw1(const size_t row) {
    switch (row) {
        case 3:
            drawNum(" _ ");
            break;
        case 4: //
            drawNum("/ |");
            break;
        case 5:
        case 6:
            drawNum("| |");
            break;
        case 7:
            drawNum("|_|");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void draw2(const size_t row) {
    switch (row) {
        case 3:
            drawNum(" ____  ");
            break;
        case 4: //
            drawNum("|___ \\ ");
            break;
        case 5:
            drawNum("  __) |");
            break;
        case 6:
            drawNum(" / __/ ");
            break;
        case 7:
            drawNum("|_____|");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void draw3(const size_t row) {
    switch (row) {
        case 3:
            drawNum(" _____ ");
            break;
        case 4: //
            drawNum("|___ / ");
            break;
        case 5:
            drawNum("  |_ \\ ");
            break;
        case 6:
            drawNum(" ___) |");
            break;
        case 7:
            drawNum("|____/ ");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void draw4(const size_t row) {
    switch (row) {
        case 3:
            drawNum(" _  _   ");
            break;
        case 4: //
            drawNum("| || |  ");
            break;
        case 5:
            drawNum("| || |_ ");
            break;
        case 6:
            drawNum("|__   _|");
            break;
        case 7:
            drawNum("   |_|  ");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void draw5(const size_t row) {
    switch (row) {
        case 3:
            drawNum(" ____  ");
            break;
        case 4: //
            drawNum("| ___| ");
            break;
        case 5:
            drawNum("|___ \\ ");
            break;
        case 6:
            drawNum(" ___) |");
            break;
        case 7:
            drawNum("|____/ ");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void draw6(const size_t row) {
    switch (row) {
        case 3:
            drawNum("  __   ");
            break;
        case 4: //
            drawNum(" / /_  ");
            break;
        case 5:
            drawNum("| '_ \\ ");
            break;
        case 6:
            drawNum("| (_) |");
            break;
        case 7:
            drawNum(" \\___/ ");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void draw7(const size_t row) {
    switch (row) {
        case 3:
            drawNum(" _____ ");
            break;
        case 4: //
            drawNum("|___  |");
            break;
        case 5:
            drawNum("   / / ");
            break;
        case 6:
            drawNum("  / /  ");
            break;
        case 7:
            drawNum(" /_/   ");
            break;
        default:
            cout << getBlnk(24, false);
    }
}

void draw8(const size_t row) {
    switch (row) {
        case 3:
            drawNum("  ___  ");
            break;
        case 4: //
            drawNum(" ( _ ) ");
            break;
        case 5:
            drawNum(" / _ \\ ");
            break;
        case 6:
            drawNum("| (_) |");
            break;
        case 7:
            drawNum(" \\___/ ");
            break;
        default:
            cout << getBlnk(24, false);
    }
}
