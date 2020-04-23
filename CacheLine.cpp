#include <iostream>
#include <vector>
#include <sstream>

#include "CacheLine.h"

using namespace std;

CacheLine::CacheLine() {
    // no code
}

CacheLine::CacheLine(int blockSize) {
    B = blockSize;
    V = 0;
    D = 0;
    T = 0;
    data.resize(B);
    for (int i = 0; i < B; i++) {
        data[i] = "--";
    }
    this->setTime();
}

void CacheLine::dumpLine() {
    for (int i = 0; i < B; i++) {
        cout << data[i] << " ";
    }
}

void CacheLine::viewLine() {
    cout << V << " ";
    cout << D << " ";
    cout << decimalToHex(T) << " ";
    for (int i = 0; i < B; i++) {
        cout << data[i] << " ";
    }
}

void CacheLine::flushLine() {
    V = 0;
    D = 0;
    T = 0;
    for (int i = 0; i < B; i++) {
        data[i] = "--";
    }
    this->setTime();
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
        hexValue += "0";
    }

    hexValue.erase(0,2);
    return hexValue;
}

void CacheLine::setBlock(vector<string> block) {
    for (int i = 0; i < B; i++) {
        data[i] = block[i];
    }
    this->setTime();
}

void CacheLine::setTag(int tag) {
    T = tag;
}

void CacheLine::setValid() {
    V = 1;
}

void CacheLine::setTime() {
    lastUsed = time(NULL);
}

time_t CacheLine::getTime() {
    return lastUsed;
}

string CacheLine::getByte(int offset) {
    return data[offset];
}

int CacheLine::getTag() {
    return T;
}

bool CacheLine::Contains(int tag) {
    return tag == T;
}
