#include "moveCalculations.h"

void kingMov(const Board *const board, const Coord *const initPos, Array *const data) {
    static const size_t nOffset{8};
    // Order: Top-Left (clockwise)
    static const Coord offsets[nOffset]{Coord{-1, -1}, Coord{-1, 0}, Coord{-1, 1}, Coord{0, -1}, Coord{0, 1}, Coord{1, -1}, Coord{1, 0}, Coord{1, 1}};
    Piece *initPce{getPce(board, initPos)};

    for (size_t i{0}; i < nOffset; i++) {
        Coord *fnlPos{copyCord(initPos)};
        incrmnt(fnlPos, &offsets[i]);
        if (!isOOB(fnlPos) && vldPcMv(board, initPce, fnlPos))
            appDta(data, fnlPos);
        dealloc(fnlPos);
    }
}

void lineMov(const Board *const board, const bool tgtMode, const bool intrpse, const Coord *const initPos, Array *const data, const PlyrClr &player = NONE) {
    static const size_t nOffset{4};
    // Order: Up, Down, Left, Right
    static const Coord offsets[nOffset]{Coord{-1, 0}, Coord{1, 0}, Coord{0, -1}, Coord{0, 1}};
    Piece *initPce{getPce(board, initPos)};

    for (size_t i{0}; i < nOffset; i++) {
        Coord *fnlPos{walkPth(board, initPos, offsets[i].row, offsets[i].col)};
        if (!isOOB(fnlPos)) {
            Piece *tgtPce{getPce(board, fnlPos)};
            if (tgtMode) {
                if (tgtChk(intrpse, initPce, tgtPce, player)) {
                    if (tgtPce->pieceID == QUEEN || tgtPce->pieceID == ROOK)
                        appDta(data, fnlPos);
                }
            } else {
                if (vldPcMv(board, getPce(board, initPos), fnlPos))
                    // Not in target mode: checking if the piece can move to the target location
                    appDta(data, fnlPos);
            }
        }
        dealloc(fnlPos);
    }
}

void diagMov(const Board *const board, const bool tgtMode, const bool intrpse, const Coord *const initPos, Array *const data, const PlyrClr &player = NONE) {
    static const size_t nOffset{4};
    // Order: Top-Left, Top-Right, Bottom-Left, Bottom-Right
    static const Coord offsets[nOffset]{Coord{-1, -1}, Coord{-1, 1}, Coord{1, -1}, Coord{1, 1}};
    Piece *initPce{getPce(board, initPos)};

    for (size_t i{0}; i < nOffset; i++) {
        Coord *fnlPos{walkPth(board, initPos, offsets[i].row, offsets[i].col)};
        if (!isOOB(fnlPos)) {
            Piece *tgtPce{getPce(board, fnlPos)};
            if (tgtMode) {
                if (tgtChk(intrpse, initPce, tgtPce, player)) {
                    if (tgtPce->pieceID == QUEEN || tgtPce->pieceID == BISHOP)
                        appDta(data, fnlPos);
                }
            } else {
                if (vldPcMv(board, getPce(board, initPos), fnlPos))
                    // Not in target mode: checking if the piece can move to the final position
                    appDta(data, fnlPos);
            }
        }
        dealloc(fnlPos);
    }
}

void knitMov(const Board *const board, const bool tgtMode, const bool intrpse, const Coord *const initPos, Array *const data, const PlyrClr &player = NONE) {
    static const size_t nOffset{8};
    // Order: Top-Left (clockwise)
    static const Coord offsets[nOffset]{Coord{-2, -1}, Coord{-2, 1}, Coord{-1, 2}, {1, 2}, Coord{2, 1}, Coord{2, -1}, Coord{1, -2}, Coord{-1, -2}};
    Piece *initPce{getPce(board, initPos)};

    for (int i{0}; i < nOffset; i++) {
        Coord *fnlPos{copyCord(initPos)};
        incrmnt(fnlPos, &offsets[i]);
        if (!isOOB(fnlPos)) {
            Piece *tgtPce{getPce(board, fnlPos)};
            if (tgtMode) {
                if (tgtChk(intrpse, initPce, tgtPce, player)) {
                    if (tgtPce->pieceID == KNIGHT)
                        appDta(data, fnlPos);
                }
            } else {
                if (vldPcMv(board, initPce, fnlPos))
                    appDta(data, fnlPos);
            }
        }
        dealloc(fnlPos);
    }
}

void pawnMov(const Board *const board, const bool tgtMode, const bool intrpse, const Coord *const initPos, Array *const data, const PlyrClr &player = NONE) {
    // {+-2, 0} offsets are calculated if the pawn has not moved yet
    static const size_t nOffset{8};
    static const Coord offsets[nOffset]{Coord{-2, 0}, Coord{-1, -1}, Coord{-1, 0}, Coord{-1, 1}, Coord{1, -1}, Coord{1, 0}, Coord{1, 1}, Coord{2, 0}};
    static const size_t diagMov[4]{1, 3, 6, 4};
    const Piece *const initPce{board->board[initPos->row][initPos->col]};
    Coord *fnlPos;
    size_t start;
    size_t end;


    if (initPce->pieceID == PAWN) {
        // tgtMode does not need to account for forward (one or two space) because pawns cannot capture forward and cannot move forward to a space if there is a piece occupying that space
        if (tgtMode) {
            start = initPce->isWhite ? 0 : 2;
            end = initPce->isWhite ? 2 : 4;
            for (size_t i{start}; i < end; i++) {
                fnlPos = copyCord(initPos);
                incrmnt(fnlPos, &offsets[diagMov[i]]);
                Piece *tgtPce{getPce(board, fnlPos)};
                if (!isOOB(fnlPos) && tgtChk(intrpse, initPce, tgtPce, player))
                    appDta(data, fnlPos);
                dealloc(fnlPos);
            }
        } else {
            start = initPce->isWhite ? (initPce->fstMove ? 0 : 1) : 4;
            end = initPce->isWhite ? 4 : (initPce->fstMove ? 8 : 7);
            for (size_t i{start}; i < end; i++) {
                fnlPos = copyCord(initPos);
                incrmnt(fnlPos, &offsets[i]);
                if (vldPcMv(board, getPce(board, initPos), fnlPos))
                    appDta(data, fnlPos);
                dealloc(fnlPos);
            }
        }
    }
}

// Castling does not apply when trying to calculate safe spaces for the king to move
// so this function doesn't need the tgtMode or intrpse variables
void castle(const Board *const board, const Coord *const initPos, Array *const data) {
    static const size_t nPos{8};
    static const Coord pos[nPos]{Coord{8, 1}, Coord{8, 3}, Coord{8, 8}, Coord{8, 7}, Coord{1, 1}, Coord{1, 3}, Coord{1, 8}, Coord{1, 7}};
    Piece *initPce{board->board[initPos->row][initPos->col]};

    if (initPce->pieceID == KING && initPce->fstMove) {
        size_t start = initPce->isWhite ? 0 : 4;
        size_t end = initPce->isWhite ? 4 : 8;
        for (size_t i{start}; i < end; i += 2) {
            Coord *newInit{copyCord(initPos)};
            incrmnt(newInit, 0, -1);
            if (board->board[pos[i].row][pos[i].col]->pieceID == ROOK && board->board[pos[i].row][pos[i].col]->fstMove && sfeSpce(board, &pos[i + 1]) && unObPth(
                    board, newInit, &pos[i]))
                appDta(data, &pos[i + 1]);
            dealloc(newInit);
        }
    }
}

bool pceIntr(const Board *const board, const Coord *const kingPos, const Coord *const enmyPos, Array *const pceLoc, Array *const toWhere) {
    //If the positions are the same
    if (isEqual(kingPos, enmyPos))
        return false;

    // Checks if the path between the two pieces is a straight line
    if (!unObPth(board, kingPos, enmyPos))
        return false;

    // For Each Position
    // 1. Check each spot and determine if the

    Array *path = calcPth(board, kingPos, enmyPos);
    for (int i{0}; i < path->utilSze; i++) {
        lineMov(board, true, true, path->data[i], pceLoc);
        diagMov(board, true, true, path->data[i], pceLoc);
    }
    for (size_t i{path->utilSze - 1}; i > 0; i--)
        if (board->board[path->data[i]->row][path->data[i]->col]->isWhite != board->board[kingPos->row][kingPos->col]->isWhite) {
            pop(pceLoc, i);
        }
    if (board->board[pceLoc->data[0]->row][pceLoc->data[0]->col]->isWhite != board->board[kingPos->row][kingPos->col]->isWhite) {
        pop(pceLoc, 0);
    }


    dealloc(path);
    return pceLoc->utilSze > 0;
}

bool sfeSpce(const Board *const board, const Coord *const tgtPos, const bool iposeMde, Array *const data) {
    bool isSafe;
    lineMov(board, true, iposeMde, tgtPos, data);
    diagMov(board, true, iposeMde, tgtPos, data);
    knitMov(board, true, iposeMde, tgtPos, data);
    pawnMov(board, true, iposeMde, tgtPos, data);

    isSafe = data->utilSze == 0;
    return isSafe;
}

// This overload only checks if the space is safe, uses interpose mode to check that another enemy piece cannot move to the target positioin
bool sfeSpce(const Board *const board, const Coord *const tgtPos) {
    Array *posData = newArry(15);
    bool isSafe;
    lineMov(board, true, true, tgtPos, posData);
    diagMov(board, true, true, tgtPos, posData);
    knitMov(board, true, true, tgtPos, posData);
    pawnMov(board, true, true, tgtPos, posData);

    isSafe = posData->utilSze == 0;
    dealloc(posData);
    return isSafe;
}

// Calculates a straight line path between two points, returns an empty array if there is no straight line path
// For a full calculated path, the bounds are exclusive
Array *calcPth(const Board *const board, const Coord *const initPos, const Coord *const tgtPos, const bool incBnds) {
    Array *path = newArry(10);

    if (initPos != tgtPos) {
        const Coord *start{lessEq(initPos, tgtPos) ? initPos : tgtPos};
        const Coord *end{lessEq(initPos, tgtPos) ? tgtPos : initPos};
        Coord *incAmt{nullptr};
        Piece *curPce;

        if (abs(initPos->row - tgtPos->row) == abs(initPos->col - tgtPos->col)) // Diagonal Path
            incAmt = lessEq(start, end) ? newCord(1, 1) : newCord(1, -1);
        else if (initPos->row == tgtPos->row) // Horizontal Path
            incAmt = newCord(0, 1);
        else if (initPos->col == tgtPos->col) // Vertical Path
            incAmt = newCord(1, 0);
        if (incAmt != nullptr) {
            if (incBnds)
                appDta(path, lessEq(initPos, tgtPos) ? initPos : tgtPos);

            Coord *curPos{copyCord(start)};
            incrmnt(curPos, incAmt);
            curPce = getPce(board, curPos);
            while (!isEqual(curPos, end) && curPce->empty) {
                appDta(path, curPos);
                incrmnt(curPos, incAmt);
                curPce = getPce(board, curPos);
            }
            if (incBnds)
                appDta(path, lessEq(initPos, tgtPos) ? tgtPos : initPos);

            dealloc(incAmt);
            dealloc(curPos);
        }
    }
    return path;
}


Coord *walkPth(const Board *const board, const Coord *const initPos, const unsigned char rowOfst, const unsigned char colOfst) {
    Coord *curPos{copyCord(initPos)};
    Piece *tgtPce;

    do {
        incrmnt(curPos, rowOfst, colOfst);
        tgtPce = getPce(board, curPos);
    } while (!isOOB(curPos) && tgtPce->empty);

    return curPos;
}


bool unObPth(const Board *const board, const Coord *const initPos, const Coord *const tgtPos) {
    if (initPos == tgtPos)
        return true;

    const Coord *start{lessEq(initPos, tgtPos) ? initPos : tgtPos};
    const Coord *end{lessEq(initPos, tgtPos) ? tgtPos : initPos};
    Array *path = calcPth(board, initPos, tgtPos, true);
    bool uobsPth{false};

    if (path->utilSze != 0)
        uobsPth = isEqual(path->data[0], start) && isEqual(path->data[path->utilSze - 1], end);

    dealloc(path);
    return uobsPth;
}

bool vldMove(const Coord *const coord, const Array *const vldMves) {
    for (int i{0}; i < vldMves->utilSze; i++)
        if (isEqual(vldMves->data[i], coord))
            return true;
    return false;
}

bool vldPcMv(const Board *const board, const Piece *const init, const Coord *const fnlPos) {
    Piece *tgt{getPce(board, fnlPos)};
    return !isOOB(fnlPos) && (tgt->empty || tgt->isWhite != init->isWhite);
}

bool tgtChk(const bool intrpse, const Piece *const init, const Piece *const tgt, const PlyrClr &player) {
    /*
     * To interpose, three criteria must be met
     * 1. The target space must not be empty
     * 2. The piece at the target space must be the player's piece
     * 3. The initial position must be empty
     */

    if (intrpse)
        return !tgt->empty && init->empty && tgt->isWhite == player;
    return !tgt->empty && (init->empty || tgt->isWhite != init->isWhite);
}
