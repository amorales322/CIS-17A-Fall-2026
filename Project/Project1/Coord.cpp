#include "Coord.h"

Coord *newCord(const unsigned char row, const unsigned char col) {
    Coord *tuple = new Coord;
    tuple->row = row;
    tuple->col = col;

    return tuple;
}

void incrmnt(Coord *const val, const Coord *const by) {
    val->row += by->row;
    val->col += by->col;
}

void incrmnt(Coord *const val, const char row, const char col) {
    val->row += row;
    val->col += col;
}

Coord *copyCord(const Coord *const toCopy) {
    return newCord(toCopy->row, toCopy->col);
}

void dealloc(const Coord *coord) {
    if (coord != nullptr)
        delete coord;
}

bool lessThn(const Coord *const a, const Coord *const b) {
    return a->row < b->row && a->col < b->col;
}

bool lessThn(const Coord *const a, const unsigned char bRow, const unsigned char bCol) {
    return a->row < bRow && a->col < bCol;
}

bool lessEq(const Coord *const a, const Coord *const b) {
    return a->row <= b->row && a->col <= b->col;
}

bool lessEq(const Coord *const a, const unsigned char bRow, const unsigned char bCol) {
    return a->row <= bRow && a->col <= bCol;
}

bool isEqual(const Coord *const a, const Coord *b) {
    return a->row == b->row && a->col == b->col;
}

bool isEqual(const Coord *const a, const unsigned char bRow, const unsigned char bCol) {
    return a->row == bRow && a->col == bCol;
}
