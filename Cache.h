#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <vector>

#include "Memory.h"
#include "Set.h"

using namespace std;

class Cache {
    public:
        Cache();
        void configureCache(Memory Ram, int addressWidth);
        string cacheMenu();
        int hexToDecimal(string hexValue);
        int binaryToDecimal(string binaryValue);
        string decimalToBinary(int decimalValue);
        string hexToBinary(string hexValue);
        void cacheRead();
        void cacheWrite();
        void cacheFlush();
        void cacheView();
        void memoryView();
        void cacheDump();
        void memoryDump();
    private:
        int C; // Cache size
        int B; // Block size
        int E; // how many cache lines per set (associativity)
        int replacement; // replacement policy
        int writeHit; // write hit policy
        int writeMiss; // write miss policy

        int S; // number of sets
        int s; // number of set index bits
        int b; // number of block offset bits
        int M; // number of unique memory addresses
        int m; // number of memory address bits
        int t; // number of tag bits;

        int cacheHits;
        int cacheMisses;
        vector<Set> sets;
        Memory RAM;
};

#endif