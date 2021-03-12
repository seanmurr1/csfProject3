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
void validArgument (std::string argument, std::string option1, std::string option2);
// take in command line arguments

// check if they're valid (helper functions)
    // example FIFO or LRU else invalid (exit with warning)
    // same idea with values (power of 2 etc)

// after pass into cache constructor and instantiate an object
// should not exceed 30 lines. should not need to scroll (think 50 lines hard max)

int main (int argc, char * argv[]) {

    int numSets;                        // Command-line argument
    int numBlocks;                      // Command-line argument
    int numBytes;                       // Command-line argument    
    bool writeAllocate;	// write-allocate or no-write-allocate
	bool writeThrough;	// write-through or write-back
	bool lru = true;		// LRU if true, FIFO if false

    // Might be 7 depending on if associative cache
    if (argc < 6) {    
        std::cerr << "Error: Missing arguments" << std::endl;
        return 1;
    }
    
    numSets = atoi(argv[1]);
    numBlocks = atoi(argv[2]);
    numBytes = atoi(argv[3]);
    std::string writeAllocateOrNot( argv[4]); // Command-line argument
    std::string writeThroughOrBack( argv[5]); // Command-line argument


    // Check to see if arguments are valid

    // Number of sets in cache has to be a positive power of 2
    if(!posPowerOfTwo(numSets)){
        std::cerr << "Error: Not a valid number of sets" << std::endl;
        return 1;
    }

    // Number of blocks in set has to be a positive power of 2
    if(!posPowerOfTwo(numBlocks)){
        std::cerr << "Error: Not a valid number of blocks" << std::endl;
        return 1;
    }

    // Number of bytes in block has to be a positive power of 2 and at least 4
    if((numBytes < 4) | !posPowerOfTwo(numBytes)){
        std::cerr << "Error: Not a valid number of bytes" << std::endl;
        return 1;
    }

    validArgument(writeAllocateOrNot, "write-allocate", "no-write-allocate");
    if (writeAllocateOrNot.compare("write-allocate") == 0) {
        writeAllocate = true;
    } else {
        writeAllocate = false;
    }

    validArgument(writeThroughOrBack, "write-through", "write-back");
    if (writeThroughOrBack.compare("write-through") == 0){
        writeThrough = true;
    } else {
        writeThrough = false;
    }

    // If write back and no write allocate print error message
    if (!writeAllocate & !writeThrough) {
        std::cerr << "Error: Invalid combination, if miss, data will never make it to memory" << std::endl;
        return 1;
    }

    // A cache with n sets of 1 block each is direct-mapped (not associative)
    if (numBlocks != 1) {
        // Cache is associative
        if (argc < 7) {    // check to make sure enough arguments
        std::cerr << "Error: Missing argument specifying eviction" << std::endl;
        return 1;
        }
        std::string evictionType( argv[6]);
        validArgument(evictionType, "lru", "fifo");
        if (evictionType.compare("lru") == 0){
         lru = true;
        } else {
          lru = false;
        }
    }

    // Create cache

    std::string line;
    std::string load;
    std::string address;
    while (getline(std::cin, line)) {
        std::cout << line << std::endl; // testing
        // break up the line into arguments
        load = line.substr(0,1);
        address = line.substr(4, 8);
        std::cout << address << std::endl;

            
        // divide into index, tag, offset
        // need to calculate those
        // convert index, tag to decimal
        // use those as parameters
        // simulate cache on line
    }

   // Cache::printSummary();

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


// Hey, I don't think you can compare strings with ==. Might need to use .equals
// i think this should work for strings but fs should look at closer if it doesn't work
void validArgument (std::string argument, std::string option1, std::string option2) {
    if (argument == option1 || argument == option2) {
        return;
    }
    std::cerr << "Error: Invalid argument" << std::endl;
}
