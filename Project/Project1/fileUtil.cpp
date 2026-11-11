#include "fileUtil.h"

void read(fstream &file, bool &data) {
    file.read(reinterpret_cast<char *>(&data), sizeof(bool));
}

void write(fstream &file, bool data) {
    file.write(reinterpret_cast<char *>(&data), sizeof(bool));
}

void read(fstream &file, PlyrClr &data) {
    file.read(reinterpret_cast<char *>(&data), sizeof(PlyrClr));
}

void write(fstream &file, PlyrClr data) {
    file.write(reinterpret_cast<char *>(&data), sizeof(PlyrClr));
}

void read(fstream &file, unsigned short &data) {
    file.read(reinterpret_cast<char *>(&data), sizeof(unsigned short));
}

void write(fstream &file, unsigned short data) {
    file.write(reinterpret_cast<char *>(&data), sizeof(unsigned short));
}

void read(fstream &file, size_t &data) {
    file.read(reinterpret_cast<char *>(&data), sizeof(size_t));
}

void write(fstream &file, size_t data) {
    file.write(reinterpret_cast<char *>(&data), sizeof(size_t));
}

void read(fstream &file, string &data) {
    size_t nameLen{};
    read(file, nameLen);
    data.resize(nameLen);
    file.read(data.data(), nameLen * sizeof(char));
}

void write(fstream &file, string data) {
    size_t nameLen{data.length() + 1};
    write(file, nameLen);
    file.write(data.data(), nameLen * sizeof(char));
}
