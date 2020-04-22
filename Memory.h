#ifndef MEMORY_H
#define MEMORY_H

#define ADDRESS_WIDTH 8

#include <iostream>
#include <vector>

using namespace std;

class Memory {
    public:
        Memory();
        Memory(int addressSize);
        ~Memory();
        void initializeMemory(string inFileName);
<<<<<<< Updated upstream
=======
        vector<string> getBlock(int address, int blockSize);
>>>>>>> Stashed changes
        void makeEmpty();
        void viewRam();
        void dumpRam();
        bool isEmpty();
        int getSize() { return ram.size(); };
        string decimalToHex(int decimalValue);
    private:
        vector<string> ram;
};

#endif