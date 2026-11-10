#include "Array.h"

Array *newArry(const size_t size) {
    Array *array = new Array;
    array->size = size;
    array->utilSze = 0;
    array->data = new Coord *[size];

    return array;
}

void pntArry(const Array *const array) {
    for (size_t i{0}; i < array->utilSze; i++)
        cout << toChsNt(array->data[i]) << ' ';
    cout << '\n';
}

void cpyArry(Array *const to, const Array *const from) {
    appDta(to, from);
}

void appDta(Array *const array, const Coord *const coord) {
    if (search(array, coord) == -1) {
        if (array->utilSze >= array->size)
            resize(array);
        array->data[array->utilSze++] = copyCord(coord);
    }
}

// Creates a copy of the coord - Appends duplicates
void appDta(Array *const to, const Array *const from) {
    size_t fnlSize{to->utilSze + from->utilSze};
    if (to->size < fnlSize)
        resize(to, fnlSize);
    for (unsigned int i{to->utilSze}; i < fnlSize; to->data[i] = copyCord(from->data[i - to->utilSze]), i++);
    to->size = fnlSize;
}

void pop(Array *const array, const int idx = -1) {
    if (idx < 0 || idx == array->utilSze - 1)
        delete []array->data[--array->utilSze];
    else if (idx < array->utilSze) {
        Coord **newData = new Coord *[array->size];
        for (size_t i{0}; i < idx; newData[i] = array->data[i], i++);
        for (size_t i{static_cast<size_t>(idx) + 1}; i < array->utilSze; newData[i - 1] = array->data[i], i++);
        delete []array->data;
        array->data = newData;
        array->utilSze--;
    }
}

void resize(Array *array, const size_t newCap) {
    // Increments size by 1
    if (newCap == 0) {
        Coord **newData = new Coord *[++array->size];
        for (size_t i{0}; i < array->utilSze; newData[i] = array->data[i], i++);
        delete []array->data;
        array->data = newData;
    } else if (newCap > array->size) {
        // Resize to new specified size
        array->size = newCap;
        Coord **newData = new Coord *[array->size];
        for (size_t i{0}; i < array->utilSze; newData[i] = array->data[i], i++);
        delete []array->data;
        array->data = newData;
    } else if (newCap < array->size) {
        Coord **newData = new Coord *[newCap];
        // [0, newCap] - Ignoring anything past the new size
        for (size_t i{0}; i < newCap; newData[i] = array->data[i], i++);
        // Deallocate all Coord structures past new size inside the old array
        for (size_t i{newCap}; i < array->size; i++)
            dealloc(array->data[i]);
        array->size = newCap;

        delete []array->data;
        array->data = newData;
    }
}

void clear(Array *array) {
    for (int i{0}; i < array->utilSze; i++)
        dealloc(array->data[i]);
    delete []array->data;
    array->utilSze = 0;
    array->data = new Coord *[array->size];
}

void shrink(Array *const array) {
    resize(array, array->utilSze);
}

void dealloc(Array *array) {
    if (array->data != nullptr) {
        for (size_t i{0}; i < array->utilSze; i++)
            dealloc(array->data[i]);
        delete []array->data;
    }
    delete array;
}

int search(const Array *const array, const Coord *const target) {
    for (size_t i{0}; i < array->utilSze; i++)
        if (isEqual(array->data[i], target))
            return i;
    return -1;
}
