#ifndef CACHELINE_H
#define CACHELINE_H

#include <iostream>
#include <vector>
#include <ctime>

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
        void setTag(int tag);
        void setValid();
        void setTime();
        time_t getTime();
        string getByte(int offset);
        int getTag();
        bool Contains(int tag);
    private:
        int B;
        int V;
        int D;
        int T;
        time_t lastUsed;
        vector<string> data;
};

#endif