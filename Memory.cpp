#include <iostream>
#include <vector>
#include <cmath> // for pow
#include <sstream>
#include <fstream>

#include "Memory.h"

using namespace std;

Memory::Memory() {
    // no code
}

Memory::Memory(int addressSize) {
    int ramSize = pow(2, addressSize);
    ram.resize(ramSize);
    for (int i = 0; i < ram.size(); i++) {
        ram[i] = "--";
    }
}

Memory::~Memory() {
    makeEmpty();
}

void Memory::initializeMemory(string inFileName) {
    ifstream ifs(inFileName);

    //error check file name
	if (!ifs.is_open())
    {
		cout << "Unable to open file: " << inFileName << endl;
		return;
	}

    int lineNumber = 0;
	while (true) 
    {
		string line;
		getline(ifs, line);
		istringstream ss(line);

        //empty line or line with whitespace
		if (line.length() == 0)
        {
			break;
		}

		if (!ss.fail())
        {
            for (int i = 0; i < line.length(); i++) {
                line[i] = toupper(line[i]);
            }

            ram[lineNumber] = line;
            lineNumber++;
		}

        //check for end of file
		if (ifs.eof())
        {
			break;
		}
	}

    if (isEmpty()) {
        cout << "Could not find any data in file: " << inFileName << endl; 
        return;
    }
}

vector<string> Memory::getBlock(int address, int blockSize) {
    vector<string> block;
    // string startByte = ram[address];
    int index = address % blockSize;
    address = address - index;
    for (int i = address; i < address + blockSize; i++) {
        block.push_back(ram[i]);
    }
    return block;
}

void Memory::setBlock(int address, vector<string> block, int blockSize) {
    int index = address % blockSize;
    address = address - index;
    int count = 0;
    for (int i = address; i < address + blockSize; i++) {
        ram[i] = block[count];
        count++;
    }
}

void Memory::writeData(int address, string data) {
    ram[address] = data;
}

void Memory::makeEmpty() {
    for (int i = 0; i < ram.size(); i++) {
        ram[i] = "--";
    }
}

void Memory::viewRam() {
    int address = 0;
    while (address < ram.size()) {
        if (address % ADDRESS_WIDTH == 0) {
            cout << endl;
            cout << decimalToHex(address) << ":";
        }
        cout << ram[address] << " ";
        address++;
    }
    cout << endl;
}
void Memory::dumpRam() {
    for (int i = 0; i < ram.size(); i++) {
        cout << ram[i] << endl;
    }
}

bool Memory::isEmpty() {
    for (int i = 0; i < ram.size(); i++) {
        if (ram[i] != "--") {
            return false;
        }
    }
    return true;
}

string Memory::decimalToHex(int decimalValue) {
    string hexValue = "0x";
    if (decimalValue < 10) {
        hexValue = "0x0";
    }

    stringstream ss;
    ss << std::hex << decimalValue;
    hexValue += ss.str();

    for (int i = 2; i < hexValue.length(); i++) {
        hexValue[i] = toupper(hexValue[i]);
    }

    return hexValue;
}
