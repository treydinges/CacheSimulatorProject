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
        data[i] = "---";
    }
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
        data[i] = "---";
    }
}

string CacheLine::decimalToHex(int decimalValue) {
    string hexValue = "";
    if (decimalValue < 10) {
        hexValue = "0";
    }

    stringstream ss;
    ss << std::hex << decimalValue;
    hexValue += ss.str();

    for (int i = 2; i < hexValue.length(); i++) {
        hexValue[i] = toupper(hexValue[i]);
    }

    return hexValue;
}

void CacheLine::setBlock(vector<string> block) {
    for (int i = 0; i < B; i++) {
        data[i] = block[i];
    }
}

bool CacheLine::Contains(int tag) {
    string target = "";
    for (int i = 0; i < t; i++) {
        target += data[i];
    }
    
    if (tag == target) {
        return true;
    } else {
        return false;
    }
}
