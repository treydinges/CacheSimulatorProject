#ifndef SET_H
#define SET_H

#include <iostream>
#include <vector>
#include <ctime>

#include "CacheLine.h"

using namespace std;

class Set {
    public:
        Set();
        Set(int associativity, int blockSize);
        void dumpSet();
        void viewSet();
        void flushSet();
        void setBlock(vector<string> block, int line);
        void setTag(int tag, int line);
        void setValid(int line);
        string getByte(int line, int offset);
        string getByte(int tag, int offset, bool hit);
        bool Contains(int tag);
        int findLRU();
    private:
        int E; // number of lines per set (associativity)
        int B; // for creation of the CacheLine
        vector<CacheLine> lines;
};

#endif