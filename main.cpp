/*
 * CSF Assignment 3
 * Simulating and evaluating caches
 * Shelby Coe scoe4
 * Sean Murray smurra42
 */
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> 

#include "Set.h"
#include "Cache.h"

bool posPowerOfTwo (int num);
bool validArgument (std::string argument, std::string option1, std::string option2);
// take in command line arguments

// check if they're valid (helper functions)
    // example FIFO or LRU else invalid (exit with warning)
    // same idea with values (power of 2 etc)

// after pass into cache constructor and instantiate an object
// should not exceed 30 lines. should not need to scroll (think 50 lines hard max)

int main (int argc, char * argv[]) {
    /*
    * EXAMPLE: 256 4 16 write-allocate write-back lru < sometracefile
    * number of sets in the cache (a positive power-of-2)
    * number of blocks in each set (a positive power-of-2)
    * number of bytes in each block (a positive power-of-2, at least 4)
    * write-allocate or no-write-allocate
    * write-through or write-back
    * lru (least-recently-used) or fifo evictions
    * tracefile
    */
    int numSets;
    int numBlocks;
    int numBytes;
    // const chars for the rest of the arguments? then set booleans when checking if valid?
    const char * writeAllocateOrNot;
    const char * writeThroughOrBack;
    // const char * lruOrFifo; // only declare and read in if associative cache
    // might be 6 depending on if associative cache
    if (argc < 7) {     // might be 8 depending on '<'
        std::cerr << "Error: Missing arguments" << std::endl;
        return 1;
    }
    
    numSets = atoi(argv[1]);
    numBlocks = atoi(argv[2]);
    numBytes = atoi(argv[3]);
    writeAllocateOrNot = argv[4];
    writeThroughOrBack = argv[5];
    // if determined to be an associative cache lruOrFifo = argv[6];

    // check to see if arguments are valid

    // number of sets in cache has to be a positive power of 2
    if(!posPowerOfTwo(numSets)){
        std::cerr << "Error: Not a valid number of sets" << std::endl;
        return 1;
    }

    // number of blocks in set has to be a positive power of 2
    if(!posPowerOfTwo(numBlocks)){
        std::cerr << "Error: Not a valid number of blocks" << std::endl;
        return 1;
    }

    // number of bytes in block has to be a positive power of 2 and at least 4
    if((numBytes < 4) | !posPowerOfTwo(numBytes)){
        std::cerr << "Error: Not a valid number of bytes" << std::endl;
        return 1;
    }

    validArgument(writeAllocateOrNot, "write-allocate", "no-write-allocate");
    validArgument(writeThroughOrBack, "write-through", "write-back");

    // reading in the tracefile should be like reading with cin

    return 0;
}

bool posPowerOfTwo (int num) {
    if (num <= 0) {
        return false;
    }
    while (num != 1) { 
        if (num % 2 == 1) {
            return false; 
        }
        num = num / 2; 
    } 
    return true; 
}

bool validArgument (std::string argument, std::string option1, std::string option2) {
    if (argument == option1 || argument == option2) {
        return true;
    }
    return false;
}