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

bool Set::Contains(int tag) {
    for (int i = 0; i < E; i++) {
        if (lines[i].Contains(tag)) {
            return true;
        }
    }
    return false;
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