#include <iostream>
#include <vector>
#include <fstream>

#include "Set.h"

using namespace std;

Set::Set() {
    // no code
}

Set::Set(int associativity, int blockSize) {
    E = associativity;
    B = blockSize;

    lines.resize(E);
    for (int i = 0; i < E; i++) {
        CacheLine newLine(B);
        lines[i] = newLine;
    }
}

void Set::dumpSet() {
    // ofstream outfile;
    // outfile.open("cache-dump.txt");
    for (int i = 0; i < E; i++) {
        lines[i].dumpLine();
        cout << endl;
        // outfile << lines[i].dumpLineToFile() << endl;
    }
    // outfile.close();
}

string Set::dumpSetToFile() {
    string set = "";
    for (int i = 0; i < E; i++) {
        set += lines[i].dumpLineToFile() + "\n";
    }
    return set;
}

void Set::viewSet() {
    for (int i = 0; i < E; i++) {
        lines[i].viewLine();
        cout << endl;
    }
}

void Set::flushSet() {
    for (int i = 0; i < E; i++) {
        lines[i].flushLine();
    }
}

void Set::setBlock(vector<string> block, int line) {
    lines[line].setBlock(block);
}

vector<string> Set::getBlock(int line) {
    return lines[line].getBlock();
}

void Set::setTag(int tag, int line) {
    lines[line].setTag(tag);
}

void Set::setValid(int line) {
    lines[line].setValid();
}

void Set::setInvalid(int line) {
    lines[line].setInvalid();
}

bool Set::isValid(int line) {
    if (line < 0 || line >= lines.size()) {
        return false;
    }
    return lines[line].isValid();
}

string Set::getByte(int line, int offset) {
    return lines[line].getByte(offset);
}

string Set::getByte(int tag, int offset, bool hit) {
    for (int i = 0; i < E; i++) {
        if (tag == lines[i].getTag()) {
            return lines[i].getByte(offset);
        }
    }
    return "--";
}

bool Set::Contains(int tag) {
    bool contains = false;
    for (int i = 0; i < E; i++) {
        if (lines[i].Contains(tag)) {
            contains = true;
        }
    }
    return contains;
}

int Set::findLRU() {
    int index = 0;

    double max = 0;
    time_t currentTime = time(NULL);
    for (int i = 0; i < E; i++) {
        double diffTime = difftime(currentTime, lines[i].getTime());
        if(diffTime > max) {
            max = diffTime;
            index = i;
        }
    }

    return index;
}

int Set::findLRU(vector<int> tieLines) {
    int index = 0;
    double max = 0;

    time_t currentTime = time(NULL);
    for (int i = 0; i < tieLines.size(); i++) {
        double diffTime = difftime(currentTime, lines[tieLines[i]].getTime());
        if(diffTime > max) {
            max = diffTime;
            index = i;
        }
    }

    return index;
}

int Set::findLFU() {
    vector<int> tieLines;
    int index = 0;
    int min = INT_MAX;
    bool tie = false;
    for (int i = 0; i < E; i++) {
        int frequency = lines[i].getFrequency();
        // cout << "frequency: " << frequency << endl;
        if(frequency < min) {
            min = frequency;
            index = i;
            tie = false;
            tieLines.clear();
        } else if (frequency == min) {
            tieLines.push_back(i);
            tie = true;
        }
    }

    if (tie) {
        return findLRU(tieLines);
    }

    return index;
}

void Set::writeData(int line, int offset, string data) {
    lines[line].writeData(offset, data);
}

void Set::makeDirty(int line) {
    lines[line].makeDirty();
}

void Set::makeClean(int line) {
    lines[line].makeClean();
}

bool Set::isDirty(int line) {
    return lines[line].isDirty();
}

int Set::getLine(int tag) {
    for (int i = 0; i < E; i++) {
        if (lines[i].Contains(tag)) {
            return i;
        }
    }
    return -1;
}

void Set::setAddress(int line, int address) {
    lines[line].setAddress(address);
}

int Set::getAddress(int line) {
    return lines[line].getAddress();
}