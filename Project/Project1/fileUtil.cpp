#include "fileUtil.h"

string getFPth(const string &comp1, const string &comp2) {
    string input{};
    cin >> input;
    // Make sure its just a filename, not a filepath
    if (input.find('.') == string::npos && input != comp1 && input != comp2) {
        cin.ignore();
        return input;
    }
    cout << "Invalid file, enter new filename: ";
    return getFPth(comp1, comp2);
}

void opnFile(fstream &file, const string &filePth, bool newFile) {
    if (newFile)
        file.open(filePth, ios::binary | ios::in | ios::out | ios::trunc);
    else {
        file.open(filePth, ios::binary | ios::in | ios::out);
        if (!file.is_open()) {
            cout << "File does not exist. Creating new file.\n";
            file.open(filePth, ios::binary | ios::in | ios::out | ios::trunc);
        } else
            file.seekg(0, ios::end);
    }
}

char *recast(bool &data) {
    return reinterpret_cast<char *>(&data);
}

void read(fstream &file, bool &data) {
    file.read(recast(data), sizeof(data));
}

void write(fstream &file, bool data) {
    file.write(recast(data), sizeof(data));
}

char *recast(PlyrClr &data) {
    return reinterpret_cast<char *>(&data);
}

void read(fstream &file, PlyrClr &data) {
    file.read(recast(data), sizeof(data));
}

void write(fstream &file, PlyrClr data) {
    file.write(recast(data), sizeof(data));
}

char *recast(unsigned short &data) {
    return reinterpret_cast<char *>(&data);
}

void read(fstream &file, unsigned short &data) {
    file.read(recast(data), sizeof(data));
}

void write(fstream &file, unsigned short data) {
    file.write(recast(data), sizeof(data));
}

char *recast(size_t &data) {
    return reinterpret_cast<char *>(&data);
}

void read(fstream &file, size_t &data) {
    file.read(recast(data), sizeof(data));
}

void write(fstream &file, size_t data) {
    file.write(recast(data), sizeof(data));
}

void read(fstream &file, string &data) {
    size_t nameLen{};
    read(file, nameLen);
    data.resize(nameLen);
    file.read(data.data(), nameLen * sizeof(data[0]));
}

void write(fstream &file, string data) {
    size_t nameLen{data.length()};
    write(file, nameLen);
    file.write(data.data(), nameLen * sizeof(data[0]));
}
