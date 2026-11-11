#include "moveCalculations.h"

void kingMov(const Board *const board, const Coord *const initPos, Array *const data) {
    // Order: Top-Left (clockwise)
    static const Coord offsets[] = {Coord{-1, -1}, Coord{-1, 0}, Coord{-1, 1}, Coord{0, -1}, Coord{0, 1}, Coord{1, -1}, Coord{1, 0}, Coord{1, 1}};
    Piece *initPce{getPce(board, initPos)};

    for (size_t i{0}; i < sizeof(offsets) / sizeof(offsets[0]); i++) {
        Coord *curPos{copyCord(initPos)};
        incrmnt(curPos, &offsets[i]);
        if (!isOOB(curPos) && vldPcMv(board, initPce, curPos))
            appDta(data, curPos);
        dealloc(curPos);
    }
}

void lineMov(const Board *const board, const bool tgtMode, const bool intrpse, const Coord *const initPos, Array *const data, const PlyrClr &player) {
    // Order: Up, Down, Left, Right
    static const Coord offsets[] = {Coord{-1, 0}, Coord{1, 0}, Coord{0, -1}, Coord{0, 1}};
    Piece *initPce{getPce(board, initPos)};

    for (size_t i{0}; i < sizeof(offsets) / sizeof(offsets[0]); i++) {
        Coord *curPos{walkPth(board, initPos, offsets[i].row, offsets[i].col)};
        if (!isOOB(curPos)) {
            Piece *tgtPce{getPce(board, curPos)};
            if (tgtMode) {
                if (tgtChk(intrpse, initPce, tgtPce, player)) {
                    if (tgtPce->pieceID == PieceID::QUEEN || tgtPce->pieceID == PieceID::ROOK)
                        appDta(data, curPos);
                }
            } else {
                // Not in target mode: checking if the piece can move to the target location
                if (vldPcMv(board, getPce(board, initPos), curPos))
                    appDta(data, curPos);
            }
        }
        dealloc(curPos);
    }
}

void diagMov(const Board *const board, const bool tgtMode, const bool intrpse, const Coord *const initPos, Array *const data, const PlyrClr &player) {
    // Order: Top-Left, Top-Right, Bottom-Left, Bottom-Right
    static const Coord offsets[] = {Coord{-1, -1}, Coord{-1, 1}, Coord{1, -1}, Coord{1, 1}};
    Piece *initPce{getPce(board, initPos)};

    for (size_t i{0}; i < sizeof(offsets) / sizeof(offsets[0]); i++) {
        Coord *curPos{walkPth(board, initPos, offsets[i].row, offsets[i].col)};
        if (!isOOB(curPos)) {
            Piece *tgtPce{getPce(board, curPos)};
            if (tgtMode) {
                if (tgtChk(intrpse, initPce, tgtPce, player)) {
                    if (tgtPce->pieceID == PieceID::QUEEN || tgtPce->pieceID == PieceID::BISHOP)
                        appDta(data, curPos);
                }
            } else {
                // Not in target mode: checking if the piece can move to the final position
                if (vldPcMv(board, getPce(board, initPos), curPos))
                    appDta(data, curPos);
            }
        }
        dealloc(curPos);
    }
}

void knitMov(const Board *const board, const bool tgtMode, const bool intrpse, const Coord *const initPos, Array *const data, const PlyrClr &player) {
    // Order: Top-Left (clockwise)
    static const Coord offsets[] = {Coord{-2, -1}, Coord{-2, 1}, Coord{-1, 2}, {1, 2}, Coord{2, 1}, Coord{2, -1}, Coord{1, -2}, Coord{-1, -2}};
    Piece *initPce{getPce(board, initPos)};

    for (int i{0}; i < sizeof(offsets) / sizeof(offsets[0]); i++) {
        Coord *curPos{copyCord(initPos)};
        incrmnt(curPos, &offsets[i]);
        if (!isOOB(curPos)) {
            Piece *tgtPce{getPce(board, curPos)};
            if (tgtMode) {
                if (tgtChk(intrpse, initPce, tgtPce, player)) {
                    if (tgtPce->pieceID == PieceID::KNIGHT)
                        appDta(data, curPos);
                }
            } else {
                // Not in target mode: checking if the piece can move to the final position
                if (vldPcMv(board, initPce, curPos))
                    appDta(data, curPos);
            }
        }
        dealloc(curPos);
    }
}

void pawnMov(const Board *const board, const bool tgtMode, const bool intrpse, const Coord *const initPos, Array *const data, const PlyrClr &player) {
    // {+-2, 0} offsets are calculated if the pawn has not moved yet
    // Order: (White) 2 Space Forward, 1 Space Forward, Diagonal Left, Diagonal Right, (Black) Diagonal Right, Diagonal Left, 1 Space Forward, 2 Space Forward
    static const Coord offsets[] = {Coord{-2, 0}, Coord{-1, 0}, Coord{-1, -1}, Coord{-1, 1}, Coord{1, -1}, Coord{1, 1}, Coord{1, 0}, Coord{2, 0}};
    const Piece *const initPce{board->board[initPos->row][initPos->col]};
    Coord *curPos;
    size_t start;
    size_t end;


    // tgtMode does not need to account for forward (one or two space) because pawns cannot capture forward and cannot move forward to a space if there is a piece occupying that space
    if (tgtMode) {
        start = player == PlyrClr::WHITE ? 2 : 4;
        end = player == PlyrClr::WHITE ? 4 : 6;

        for (size_t i{start}; i < end; i++) {
            curPos = copyCord(initPos);
            incrmnt(curPos, &offsets[i]);
            Piece *tgtPce{getPce(board, curPos)};
            if (!isOOB(curPos) && tgtChk(intrpse, initPce, tgtPce, player))
                if (tgtPce->pieceID == PieceID::PAWN)
                    appDta(data, curPos);
            dealloc(curPos);
        }
    } else {
        // Not in target mode: checking if the piece can move to the final position
        start = initPce->pceClr == PlyrClr::WHITE ? (initPce->fstMove ? 0 : 1) : 4;
        end = initPce->pceClr == PlyrClr::WHITE ? 4 : (initPce->fstMove ? 8 : 7);
        for (size_t i{start}; i < end; i++) {
            curPos = copyCord(initPos);
            incrmnt(curPos, &offsets[i]);
            if (vldPcMv(board, getPce(board, initPos), curPos))
                appDta(data, curPos);
            dealloc(curPos);
        }
    }
}

// Castling does not apply when trying to calculate safe spaces for the king to move
// so this function doesn't need the tgtMode or intrpse variables
void castle(const Board *const board, const Coord *const initPos, Array *const data) {
    static const Coord offsets[] = {Coord{8, 1}, Coord{8, 3}, Coord{8, 8}, Coord{8, 7}, Coord{1, 1}, Coord{1, 3}, Coord{1, 8}, Coord{1, 7}};
    Piece *initPce{board->board[initPos->row][initPos->col]};

    if (initPce->pieceID == PieceID::KING && initPce->fstMove) {
        size_t start = initPce->pceClr == PlyrClr::WHITE ? 0 : 4;
        size_t end = initPce->pceClr == PlyrClr::WHITE ? 4 : 8;
        for (size_t i{start}; i < end; i += 2) {
            Piece *offPce{getPce(board, &offsets[i])};
            // Todo: Verify that sfeSpce received the correct player color parameter
            if (offPce->pieceID == PieceID::ROOK && offPce->fstMove && sfeSpce(board, &offsets[i + 1], initPce->pceClr) && unObPth(board, initPos, &offsets[i]))
                appDta(data, &offsets[i + 1]);
        }
    }
}

bool pceIntr(const Board *const board, const Coord *const kingPos, const Coord *const enmyPos, Array *const pceLoc, Array *const toWhere, const PlyrClr &player) {
    //If the positions are the same
    if (isEqual(kingPos, enmyPos))
        return false;

    // Checks if a valid path exists between the two points
    if (!unObPth(board, kingPos, enmyPos))
        return false;

    Array *path = calcPth(board, kingPos, enmyPos);
    for (int i{0}; i < path->utilSze; i++) {
        size_t initSze{pceLoc->utilSze};
        lineMov(board, true, true, path->data[i], pceLoc, player);
        diagMov(board, true, true, path->data[i], pceLoc, player);
        size_t fnlSize{pceLoc->utilSze};

        // Interposing pieces were found
        if (fnlSize > initSze)
            for (size_t j{0}; j < fnlSize - initSze; appDta(toWhere, path->data[i]), j++);
    }


    dealloc(path);
    return !pceLoc->empty;
}

bool sfeSpce(const Board *const board, const Coord *const tgtPos, const bool iposeMde, Array *const data, const PlyrClr &player) {
    bool isSafe;

    lineMov(board, true, iposeMde, tgtPos, data, player);
    diagMov(board, true, iposeMde, tgtPos, data, player);
    knitMov(board, true, iposeMde, tgtPos, data, player);
    pawnMov(board, true, iposeMde, tgtPos, data, player);


    isSafe = data->empty;
    return isSafe;
}

bool sfeSpce(const Board *const board, const Coord *const tgtPos, const PlyrClr &player) {
    Array *posData = newArry();
    bool isSafe;
    lineMov(board, true, false, tgtPos, posData, player);
    diagMov(board, true, false, tgtPos, posData, player);
    knitMov(board, true, false, tgtPos, posData, player);
    pawnMov(board, true, false, tgtPos, posData, player);

    isSafe = posData->empty;
    dealloc(posData);
    return isSafe;
}

Array *sfeMves(const Board *board, const Coord *kingPos) {
    Array *vldMves{newArry()};
    Array *whoChk{newArry()};

    Piece *kingPce{getPce(board, kingPos)};

    // Determines the locations of the pieces that are putting the king in check
    sfeSpce(board, board->wKngPos, false, whoChk, kingPce->pceClr);

    // Determine which spaces the king can move to, not yet accounting for spaces where the king would still be in check
    kingMov(board, board->wKngPos, vldMves);

    // Eliminate surrounding spaces the king cannot move to, accounting for ones where the king would still be in check
    for (size_t i{vldMves->utilSze - 1}; i > 0; i--)
        if (!sfeSpce(board, vldMves->data[i], kingPce->pceClr))
            pop(vldMves, i);
    if (!sfeSpce(board, vldMves->data[0], kingPce->pceClr))
        pop(vldMves, 0);

    return vldMves;
}

Array *calcPth(const Board *const board, const Coord *const initPos, const Coord *const tgtPos, const bool incBnds) {
    Array *path = newArry();

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


Coord *walkPth(const Board *const board, const Coord *const initPos, const char rowOfst, const char colOfst) {
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

    if (!path->empty)
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

bool vldPcMv(const Board *const board, const Piece *const init, const Coord *const curPos) {
    Piece *tgt{getPce(board, curPos)};
    return !isOOB(curPos) && (tgt->empty || tgt->pceClr != init->pceClr);
}

bool tgtChk(const bool intrpse, const Piece *const init, const Piece *const tgt, const PlyrClr &player) {
    /*
     * For interpose mode, three criteria must be met
     * 1. The target space must not be empty
     * 2. The piece at the target space must be the player's piece
     * 3. The initial position must be empty
     */

    /*
     * For target mode, these criteria must be met
     * 1. The target space must not be empty
     * 2. The target space must be an enemy piece (checked with two different criteria based on if the initial space is empty or not)
     */
    if (intrpse)
        return !tgt->empty && init->empty && tgt->pceClr == player;
    return !tgt->empty && tgt->pceClr != player;
}
