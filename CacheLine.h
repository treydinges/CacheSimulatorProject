#ifndef CACHELINE_H
#define CACHELINE_H

#include <iostream>
#include <vector>

using namespace std;

class CacheLine {
    public:
        CacheLine();
        CacheLine(int blockSize);
        void dumpLine();
        void viewLine();
        void flushLine();
        string decimalToHex(int decimalValue);
        void setBlock(vector<string> block);
        bool Contains(int tag);
    private:
        int B;
        int V;
        int D;
        int T;
        vector<string> data;
};

#endif