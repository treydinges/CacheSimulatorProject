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
        vector<string> getBlock();
        void setTag(int tag);
        void setValid();
        void setInvalid();
        bool isValid();
        void setTime();
        time_t getTime();
        int getFrequency();
        string getByte(int offset);
        int getTag();
        bool Contains(int tag);
        void writeData(int offset, string data);
        void makeDirty();
        void makeClean();
        bool isDirty();
        void setAddress(int address);
        int getAddress();

    private:
        int B;
        int V;
        int D;
        int T;
        time_t lastUsed;
        int frequency;
        vector<string> data;
        int A; // address for the use of cache-flush
};

#endif