#include <iostream>
#include <cmath> // for pow

#include "Memory.h"
#include "Cache.h"

using namespace std;

int main(int argc, char *argv[]) {
    cout << "*** Welcome to the cache simulator ***" << endl;
    cout << "initialize the RAM:" << endl;
    cout << "init-ram 0x00 0xFF" << endl;

    Memory Ram(ADDRESS_WIDTH);

    Ram.initializeMemory(argv[1]);
    if (Ram.isEmpty()) {
        cout << "Unable to initialize RAM" << endl;
        cout << "Please rerun the program with a valid file" << endl;
        return 0;
    }

    cout << "ram successfully initialized!" << endl;
    cout << endl;

    Cache cache;
    // will handle setting the private data members the cache
    cache.configureCache(Ram, ADDRESS_WIDTH);
    
    string selection = "";
    while (selection != "quit") {
        selection = cache.cacheMenu();
    }

    return 0;
}
