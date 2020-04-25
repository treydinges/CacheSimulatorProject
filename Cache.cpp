#include <iostream>
#include <vector>
#include <cmath> // for pow
#include <cstdlib> // for rand()
#include <sstream>

#include "Cache.h"

using namespace std;

Cache::Cache() {
    cacheHits = 0;
    cacheMisses = 0;
}

void Cache::configureCache(Memory Ram, int addressWidth) {
    string cacheSizeString;
    string blockSizeString;
    string associativityString;
    string replacementPolicyString;
    string hitPolicyString;
    string missPolicyString;

    int cacheSize;
    int blockSize;
    int associativity;
    int replacementPolicy;
    int hitPolicy;
    int missPolicy;

    cout << "configure the cache:" << endl;
    cout << "cache size: ";
    while (true) {
        cin >> cacheSizeString;

        bool valid = true;
        for (int i = 0; i < cacheSizeString.length(); i++) {
            if (!isdigit(cacheSizeString[i])) {
                valid = false;
            }
        }

        if (valid) {
            cacheSize = stoi(cacheSizeString);
            if (cacheSize >= 8 && cacheSize <= 256 && valid) {
                break;
            } else {
                cout << "Please enter a valid cache size: ";
            }
        } else {
            cout << "Please enter a valid cache size: ";
        }
    }
    
    cout << "data block size: ";
    while (true) {
        cin >> blockSizeString;

        bool valid = true;
        for (int i = 0; i < blockSizeString.length(); i++) {
            if (!isdigit(blockSizeString[i])) {
                valid = false;
            }
        }

        if (valid) {
            blockSize = stoi(blockSizeString);
            if (blockSize == 2 || blockSize == 4 || blockSize == 8) {
                break;
            } else {
                cout << "Please enter a valid block size: ";
            }
        } else {
            cout << "Please enter a valid block size: ";
        }
    }

    cout << "associativity: ";
    while (true) {
        cin >> associativityString;
        bool valid = true;
        for (int i = 0; i < associativityString.length(); i++) {
            if (!isdigit(associativityString[i])) {
                valid = false;
            }
        }

        if (valid) {
            associativity = stoi(associativityString);
            if (associativity == 1 || associativity == 2 || associativity == 4) {
                break;
            } else {
                cout << "Please enter a valid associativity: ";
            }
        } else {
            cout << "Please enter a valid associativity: ";
        }
    }

    cout << "replacement policy: ";
    while (true) {
        cin >> replacementPolicyString;
        bool valid = true;
        for (int i = 0; i < replacementPolicyString.length(); i++) {
            if (!isdigit(replacementPolicyString[i])) {
                valid = false;
            }
        }

        if (valid) {
            replacementPolicy = stoi(replacementPolicyString);
            if (replacementPolicy == 1 || replacementPolicy == 2 || replacementPolicy == 3) {
                break;
            } else {
                cout << "Please enter a valid replacement policy: ";
            }
        } else {
            cout << "Please enter a valid replacement policy: ";
        }
    }

    cout << "write hit policy: ";
    while (true) {
        cin >> hitPolicyString;
        bool valid = true;
        for (int i = 0; i < hitPolicyString.length(); i++) {
            if (!isdigit(hitPolicyString[i])) {
                valid = false;
            }
        }

        if (valid) {
            hitPolicy = stoi(hitPolicyString);
            if (hitPolicy == 1 || hitPolicy == 2) {
                break;
            } else {
                cout << "Please enter a valid write hit policy: ";
            }
        } else {
            cout << "Please enter a valid write hit policy: ";
        }
    }

    cout << "write miss policy: ";
    while (true) {
        cin >> missPolicyString;
        bool valid = true;
        for (int i = 0; i < missPolicyString.length(); i++) {
            if (!isdigit(missPolicyString[i])) {
                valid = false;
            }
        }

        if (valid) {
            missPolicy = stoi(missPolicyString);
            if (missPolicy == 1 || missPolicy == 2) {
                break;
            } else {
                cout << "Please enter a valid write miss policy: ";
            }
        } else {
            cout << "Please enter a valid write miss policy: ";
        }
    }
    cout << "cache successfully configured!" << endl;

    // set private data members of the cache
    C = cacheSize;
    B = blockSize;
    E = associativity;
    replacement = replacementPolicy;
    writeHit = hitPolicy;
    writeMiss = missPolicy;

    S = C / (B * E);
    s = log2(S);
    b = log2(B);
    M = pow(2, addressWidth);
    m = log2(M);
    t = m - (s + b);

    // reset the size and initialize the sets
    sets.resize(S);
    for (int i = 0; i < S; i++) {
        Set newSet(E, B);
        sets[i] = newSet;
    }

    RAM = Ram;
}

string Cache::cacheMenu() {
    cout << endl;
    cout << "*** Cache simulator menu ***" << endl;
    cout << "type one command:" << endl;
    cout << "1. cache-read" << endl;
    cout << "2. cache-write" << endl;
    cout << "3. cache-flush" << endl;
    cout << "4. cache-view" << endl;
    cout << "5. memory-view" << endl;
    cout << "6. cache-dump" << endl;
    cout << "7. memory-dump" << endl;
    cout << "8. quit" << endl;
    cout << "****************************" << endl;

    string selection = "";
    cin >> selection;

    if (selection == "cache-read") cacheRead();
    else if (selection == "cache-write") cacheWrite();
    else if (selection == "cache-flush") cacheFlush();
    else if (selection == "cache-view") cacheView();
    else if (selection == "memory-view") memoryView();
    else if (selection == "cache-dump") cacheDump();
    else if (selection == "memory-dump") memoryDump();
    else if (selection == "quit");
    else cout << "Please enter a valid menu selection" << endl;

    return selection;
}

int Cache::hexToDecimal(string hexValue) {
    if (hexValue[2] == '-') {
        return -1;
    }

    int decimalValue = -1;
    stringstream ss;

    ss << hexValue;
    ss >> hex >> decimalValue;

    return decimalValue;
}

int Cache::binaryToDecimal(string binaryValue) {
    int decimal = 0;
    int exponent = 0;
    for (int i = binaryValue.length()-1; i >= 0; i--) {
        if (binaryValue[i] == '1') {
            decimal += pow(2, exponent);
        }
        exponent++;
    }
    return decimal;
}

string Cache::decimalToBinary(int decimalValue) {
    string binary = "";
    for (int i = 0; i < m; i++) {
        binary += '0';
    }

    int i = 0;
    while (decimalValue > 0) {
        int digit = decimalValue % 2;

        int index = (binary.length() - 1) - i;
        if (digit == 1) {
            binary[index] = '1';
        }

        decimalValue = decimalValue / 2;
        i++;
    }

    return binary;
}

string Cache::hexToBinary(string hexValue) {
    if (hexValue[2] == '-') {
        return "";
    }

    string binaryValue = "";
    int tempValue = hexToDecimal(hexValue);
    binaryValue = decimalToBinary(tempValue);

    return binaryValue;
}

void Cache::cacheRead() {
    // cache-read 0x18
    // set:3
    // tag:0
    // hit:no
    // eviction_line:0
    // ram_address:0x18
    // data:0x84

    string address = "";
    int addressIndex = 0;
    while (true) {
        cin >> address;

        bool valid = true;
        for (int i = 0; i < address.length(); i++) {
            if (!isalpha(address[i]) && !isdigit(address[i])) {
                valid = false;
            }
        }

        if (address[0] != '0' && address[1] != 'x') {
            valid = false;
        }

        addressIndex = hexToDecimal(address);
        if (addressIndex >= 0 && addressIndex < M && valid) {
            break;
        }
        else {
            cout << "Please enter a valid address: ";
        }
    }

    string binary = hexToBinary(address);

    string setString = "";
    string tagString = "";
    string offsetString = "";
    for (int i = 0; i < t; i++) {
        tagString += binary[i];
    }
    for (int i = t; i < t+s; i++) {
        setString += binary[i];
    }
    for (int i = t+s; i < t+s+b; i++) {
        offsetString += binary[i];
    }
    int set = binaryToDecimal(setString);
    int tag = binaryToDecimal(tagString);
    int offset = binaryToDecimal(offsetString);

    cout << "set:" << set << endl;
    cout << "tag:" << tag << endl;

    int hitLine = sets[set].getLine(tag);
    bool hit = false;
    int evictionLine = -1;
    string data = "--";
    if (sets[set].Contains(tag) && sets[set].isValid(hitLine)) {
        hit = true;
        cacheHits++;
        data = sets[set].getByte(tag, offset, hit);
    } else {
        hit = false;
        cacheMisses++;
        if (replacement == 1) {
            // random
            int random = rand() % E;
            evictionLine = random;
            // cout << random << endl;
        } else if (replacement == 2) {
            // LRU
            // find the least recently used
            evictionLine = sets[set].findLRU();
        } else if (replacement == 3) {
            // LFU
            // find the least frequently used
            evictionLine = sets[set].findLFU();
        }

        if (writeHit == 2 && sets[set].isDirty(evictionLine)) {
            vector<string> block = sets[set].getBlock(evictionLine);
            int oldAddress = sets[set].getAddress(evictionLine);
            RAM.setBlock(oldAddress, block, B);
            sets[set].makeClean(evictionLine);
            sets[set].setInvalid(evictionLine);
            sets[set].setTag(-1, evictionLine);
        }

        // get the block from memory & put it in the evicted line
        vector<string> block = RAM.getBlock(addressIndex, B);
        sets[set].setBlock(block, evictionLine);
        sets[set].setTag(tag, evictionLine);
        sets[set].setValid(evictionLine);
        sets[set].setAddress(evictionLine, addressIndex);
        // get the byte from the block
        data = sets[set].getByte(evictionLine, offset);
    }

    string hitString = "no";
    if (hit) {
        hitString = "yes";
    }
    cout << "hit:" << hitString << endl;
    cout << "eviction_line:" << evictionLine << endl;
    cout << "ram_address:" << address << endl;
    cout << "data:" << data << endl;
}

void Cache::cacheWrite() {
    // cache-write 0x10 0xAB
    // set:2
    // tag:0
    // write_hit:no
    // eviction_line:0
    // ram_address:0x10
    // data:0xAB
    // dirty_bit:1

    string address = "";
    int addressIndex = 0;
    while (true) {
        cin >> address;

        bool valid = true;
        for (int i = 0; i < address.length(); i++) {
            if (!isalpha(address[i]) && !isdigit(address[i])) {
                valid = false;
            }
        }

        if (address[0] != '0' && address[1] != 'x') {
            valid = false;
        }

        addressIndex = hexToDecimal(address);
        if (addressIndex >= 0 && addressIndex < M && valid) {
            break;
        } else {
            cout << "Please enter a valid address: ";
        }
    }

    string data = "";
    int dataInt = 0;
    while (true) {
        cin >> data;
        
        bool valid = true;
        for (int i = 0; i < data.length(); i++) {
            if (!isalpha(data[i]) && !isdigit(data[i])) {
                valid = false;
            }
        }

        if (data[0] != '0' && data[1] != 'x') {
            valid = false;
        }

        dataInt = hexToDecimal(data);
        if (dataInt >= 0 && dataInt < M && valid) {
            data.erase(0,2);
            break;
        } else {
            cout << "Please enter valid data: ";
        }
    }
    

    string binary = hexToBinary(address);

    string setString = "";
    string tagString = "";
    string offsetString = "";
    for (int i = 0; i < t; i++) {
        tagString += binary[i];
    }
    for (int i = t; i < t+s; i++) {
        setString += binary[i];
    }
    for (int i = t+s; i < t+s+b; i++) {
        offsetString += binary[i];
    }
    int set = binaryToDecimal(setString);
    int tag = binaryToDecimal(tagString);
    int offset = binaryToDecimal(offsetString);
    
    cout << "set:" << set << endl;
    cout << "tag:" << tag << endl;

    int hitLine = sets[set].getLine(tag);
    bool hit = false;
    int evictionLine = -1;
    int dirty = 0;
    if (sets[set].Contains(tag) && sets[set].isValid(hitLine)) {
        hit = true;
        cacheHits++;
        // int hitLine = sets[set].getLine(tag);
        if (writeHit == 1) {
            // write through
            RAM.writeData(addressIndex, data);
            sets[set].writeData(hitLine, offset, data);
        } else if (writeHit == 2) {
            // write back
            sets[set].writeData(hitLine, offset, data);
            sets[set].makeDirty(hitLine);
            dirty = 1;
        }
        data = sets[set].getByte(hitLine, offset);
        address = "-1";
    } else {
        hit = false;
        cacheMisses++;
        // find the eviction line
        if (replacement == 1) {
            // random
            int random = rand() % E;
            evictionLine = random;
            cout << random << endl;
        } else if (replacement == 2) {
            // LRU
            // find the least least recently used
            evictionLine = sets[set].findLRU();
        } else if (replacement == 3) {
            // LFU
            // find the least frequently used
            evictionLine = sets[set].findLFU();
        }

        if (writeHit == 2 && sets[set].isDirty(evictionLine)) {
            vector<string> block = sets[set].getBlock(evictionLine);
            int oldAddress = sets[set].getAddress(evictionLine);
            RAM.setBlock(oldAddress, block, B);
            sets[set].makeClean(evictionLine);
            sets[set].setInvalid(evictionLine);
            sets[set].setTag(-1, evictionLine);
        }
        
        if (writeMiss == 1) {
            // write allocate
            // put the block into cache
            vector<string> block = RAM.getBlock(addressIndex, B);
            sets[set].setBlock(block, evictionLine);
            sets[set].setTag(tag, evictionLine);
            sets[set].setValid(evictionLine);
            sets[set].setAddress(evictionLine, addressIndex);
            // followed by the write hit action
            if (writeHit == 1) {
                // write through
                RAM.writeData(addressIndex, data);
                sets[set].writeData(evictionLine, offset, data);
            } else if (writeHit == 2) {
                // write back
                sets[set].writeData(evictionLine, offset, data);
                sets[set].makeDirty(evictionLine);
                dirty = 1;
            }
            data = sets[set].getByte(evictionLine, offset);
        } else if (writeMiss == 2) {
            // no write allocate
            RAM.writeData(addressIndex, data);
        }
    }

    string hitString = "no";
    if (hit) {
        hitString = "yes";
    }
    cout << "write_hit:" << hitString << endl;
    cout << "eviction_line:" << evictionLine << endl;
    cout << "ram_address:" << address << endl;
    cout << "data:" << data << endl;
    cout << "dirty_bit:" << dirty << endl;
}

void Cache::cacheFlush() {
    // cache-flush
    // cache_cleared

    for (int set = 0; set < S; set++) {
        for (int line = 0; line < E; line++) {
            if (writeHit == 2 && sets[set].isDirty(line)) {
                vector<string> block = sets[set].getBlock(line);
                int addressIndex = sets[set].getAddress(line);
                RAM.setBlock(addressIndex, block, B);
            }
        }
    }

    for (int i = 0; i < S; i++) {
        sets[i].flushSet();
    }
    cout << "cache_cleared" << endl;
}

void Cache::cacheView() {
    // cache-view
    // cache_size:32
    // data_block_size:8
    // associativity:2
    // replacement_policy:random_replacement
    // write_hit_policy:write_through
    // write_miss_policy:write_allocate
    // number_of_cache_hits:2
    // number_of_cache_misses:6
    // cache_content:
    // 0 0 F0 F6 AB 01 22 A5 A6 44 DB
    // 0 0 01 DA FF 23 11 A5 10 29 87
    // 0 0 01 F6 AB CD 97 BB A6 72 DB
    // 0 0 01 F6 AB CD 97 BB A6 72 DB
    // .
    // .
    // .

    cout << "cache_size:" << C << endl;
    cout << "data_block_size:" << B << endl;
    cout << "associativity:" << E << endl;

    cout << "replacement_policy:";
    if (replacement == 1) cout << "random_replacement" << endl;
    else if (replacement == 2) cout << "least_recently_used" << endl;
    else if (replacement == 3) cout << "least_frequently_used" << endl;

    cout << "write_hit_policy:";
    if (writeHit == 1) cout << "write_through" << endl;
    else if (writeHit == 2) cout << "write_back" << endl;

    cout << "write_miss_policy:";
    if (writeMiss == 1) cout << "write_allocate" << endl;
    else if (writeMiss == 2) cout << "no_write_allocate" << endl;

    cout << "number_of_cache_hits:" << cacheHits << endl;
    cout << "number_of_cache_misses:" << cacheMisses << endl;
    cout << "cache_content:" << endl;

    for (int i = 0; i < S; i++) {
        sets[i].viewSet();
    }
}

void Cache::memoryView() {
    // memory-view
    // memory_size:256
    // memory_content:
    // Address:Data
    // 0x00:F6 AB 01 22 A5 A6 44 DB
    // 0x08:DA FF 23 11 A5 10 29 87
    // 0x10:F6 AB CD 97 BB A6 72 DB
    // .
    // .
    // .

    cout << "memory_size:" << RAM.getSize() << endl;
    cout << "memory_content:" << endl;
    cout << "Address:Data";
    RAM.viewRam();
}

void Cache::cacheDump() {
    // cache-dump
    // F6 AB 01 22 A5 A6 44 DB
    // DA FF 23 11 A5 10 29 87
    // F6 AB CD 97 BB A6 72 DB
    // F6 AB CD 97 BB A6 72 DB
    // .
    // .
    // .

    for (int i = 0; i < S; i++) {
        sets[i].dumpSet();
    }
}

void Cache::memoryDump() {
    // memory-dump
    // F6
    // AB
    // 01
    // 22
    // A5
    // A6
    // 44
    // DB
    // DA
    // FF
    // 23
    // 11
    // A5
    // .
    // .
    // .

    RAM.dumpRam();
}