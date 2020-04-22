#ifndef CACHELINE_H
#define CACHELINE_H

#include <iostream>
#include <vector>

using namespace std;

class CacheLine {
    public:
        CacheLine();
        CacheLine(int blockSize);
        bool Contains(int tag);
        void dumpLine();
        void viewLine();
        void flushLine();
        string decimalToHex(int decimalValue); 
    private:
        int B;
        int V; // valid
        int D; // dirty bit
        int T; // tag
        int timeStamp;
        vector<string> data;
};

#endif