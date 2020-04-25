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
        vector<string> getBlock(int line);
        void setTag(int tag, int line);
        void setValid(int line);
        void setInvalid(int line);
        bool isValid(int line);
        string getByte(int line, int offset);
        string getByte(int tag, int offset, bool hit);
        bool Contains(int tag);
        int findLRU();
        int findLRU(vector<int> tieLines);
        int findLFU();
        void writeData(int line, int offset, string data);
        void makeDirty(int line);
        void makeClean(int line);
        bool isDirty(int line);
        int getLine(int tag);
        void setAddress(int line, int address);
        int getAddress(int line);
    private:
        int E; // number of lines per set (associativity)
        int B; // for creation of the CacheLine
        vector<CacheLine> lines;
};

#endif