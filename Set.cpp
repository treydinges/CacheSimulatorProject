#include <iostream>
#include <vector>

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
    for (int i = 0; i < E; i++) {
        lines[i].dumpLine();
        cout << endl;
    }
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

void Set::setTag(int tag, int line) {
    lines[line].setTag(tag);
}
void Set::setValid(int line) {
    lines[line].setValid();
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

void Set::writeData(int line, int offset, string data) {
    lines[line].writeData(offset, data);
}

void Set::makeDirty(int line) {
    lines[line].makeDirty();
}

int Set::getLine(int tag) {
    for (int i = 0; i < E; i++) {
        if (lines[i].Contains(tag)) {
            return i;
        }
    }
}