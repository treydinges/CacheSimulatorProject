#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

#include "CacheLine.h"

using namespace std;

CacheLine::CacheLine() {
    // no code
}

CacheLine::CacheLine(int blockSize) {
    B = blockSize;
    V = 0;
    D = 0;
    T = -1;
    data.resize(B);
    for (int i = 0; i < B; i++) {
        data[i] = "--";
    }
    this->setTime();
    frequency = 0;
}

void CacheLine::dumpLine() {
    for (int i = 0; i < B; i++) {
        cout << data[i] << " ";
    }
}

string CacheLine::dumpLineToFile() {
    string line;
    for (int i = 0; i < B; i++) {
        line += data[i] + " ";
    }
    return line;
}

void CacheLine::viewLine() {
    cout << V << " ";
    cout << D << " ";
    if (T == -1) {
        cout << "00 ";
    } else {
        cout << decimalToHex(T) << " ";
    }
    for (int i = 0; i < B; i++) {
        cout << data[i] << " ";
    }
}

void CacheLine::flushLine() {
    V = 0;
    D = 0;
    T = -1;
    for (int i = 0; i < B; i++) {
        data[i] = "--";
    }
    this->setTime();
    frequency = 0;
}

string CacheLine::decimalToHex(int decimalValue) {
    string hexValue = "0x";
    if (decimalValue < 10) {
        hexValue += "0";
    }

    stringstream ss;
    ss << std::hex << decimalValue;
    hexValue += ss.str();

    for (int i = 2; i < hexValue.length(); i++) {
        hexValue[i] = toupper(hexValue[i]);
    }

    if (hexValue.length() != 4) {
        char lastNum = hexValue[2];
        hexValue.erase(2,1);
        hexValue += "0";
        hexValue += lastNum;
    }

    hexValue.erase(0,2);
    return hexValue;
}

void CacheLine::setBlock(vector<string> block) {
    for (int i = 0; i < B; i++) {
        data[i] = block[i];
    }
    // this->setTime();
    // frequency++;
}

vector<string> CacheLine::getBlock() {
    return data;
}

void CacheLine::setTag(int tag) {
    T = tag;
}

void CacheLine::setValid() {
    V = 1;
}

void CacheLine::setInvalid() {
    V = 0;
}

bool CacheLine::isValid() {
    if (V == 1) {
        return true;
    }
    return false;
}

void CacheLine::setTime() {
    lastUsed = time(NULL);
}

time_t CacheLine::getTime() {
    return lastUsed;
}

int CacheLine::getFrequency() {
    return frequency;
}

string CacheLine::getByte(int offset) {
    this->setTime();
    frequency++;
    return data[offset];
}

int CacheLine::getTag() {
    return T;
}

bool CacheLine::Contains(int tag) {
    return tag == T;
}

void CacheLine::writeData(int offset, string data) {
    this->data[offset] = data;
    // this->setTime();
    // frequency++;
}

void CacheLine::makeDirty() {
    D = 1;
}

void CacheLine::makeClean() {
    D = 0;
}

bool CacheLine::isDirty() {
    if (D == 1) {
        return true;
    }
    return false;
}

void CacheLine::setAddress(int address) {
    A = address;
}

int CacheLine::getAddress() {
    return A;
}