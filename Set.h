#ifndef SET_H
#define SET_H

#include <iostream>
#include <vector>

#include "CacheLine.h"

using namespace std;

class Set {
    public:
        Set();
        Set(int associativity, int blockSize);
        bool Contains(int tag);
        void dumpSet();
        void viewSet();
        void flushSet();
    private:
        int E; // number of lines per set (associativity)
        int B; // for creation of the CacheLine
        vector<CacheLine> lines;
};

#endif