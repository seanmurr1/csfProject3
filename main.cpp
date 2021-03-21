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

uint32_t hexAddressToDecimal (std::string hexAddress);
bool posPowerOfTwo (int num);
void validArgument (std::string argument, std::string option1, std::string option2);

int main (int argc, char * argv[]) {

    int numSets, numBlocks, numBytes;   // Command-line argument
    bool writeAllocate;	                // write-allocate or no-write-allocate
	bool writeThrough;              	// write-through or write-back
	bool lru = true;	            	// LRU if true, FIFO if false

    if (argc < 6) {    // Might be 7 depending on if associative cache
        std::cerr << "Error: Missing arguments" << std::endl;
        return 1;
    }
    
    numSets = atoi(argv[1]);
    numBlocks = atoi(argv[2]);
    numBytes = atoi(argv[3]);
    std::string writeAllocateOrNot( argv[4]); // Command-line argument
    std::string writeThroughOrBack( argv[5]); // Command-line argument

    // Check to see if arguments are valid
    if(!posPowerOfTwo(numSets)){  // Number of sets in cache has to be a positive power of 2
        std::cerr << "Error: Not a valid number of sets" << std::endl;
        return 1;
    }

    if(!posPowerOfTwo(numBlocks)){     // Number of blocks in set has to be a positive power of 2
        std::cerr << "Error: Not a valid number of blocks" << std::endl;
        return 1;
    }

    if((numBytes < 4) | !posPowerOfTwo(numBytes)){ // Number of bytes in block has to be a positive power of 2 and at least 4
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
    Cache* cache = new Cache (numSets, numBlocks, numBytes, writeAllocate, writeThrough, lru);
    std::string line;
    std::string load;
    std::string hexAddress;
    while (getline(std::cin, line)) {
        // break up the line into arguments
        load = line.substr(0,1);
        hexAddress = line.substr(4, 8);
        uint32_t binaryAddress = hexAddressToDecimal(hexAddress);

        if (load.compare("l") == 0) {
            cache->load(binaryAddress);
        } else if (load.compare("s") == 0) {
            cache->store(binaryAddress);
        } else {
            std::cerr << "Error: Not 'l' or 's'" << std::endl;
        }
    }
    cache->printSummary();
    return 0;
}

uint32_t hexAddressToDecimal (std::string hexAddress) {
    uint32_t binaryAddress = 0;
    int i = 0;

    while(hexAddress[i]) {
        // Multiply by 2^4 to make space for new bits
        binaryAddress = binaryAddress * 16;

        // Find binary representation of hex char
        // Add it to end of binary address
        char hex_char = hexAddress[i];
        
        // if hex is 0-9 
	    if(hex_char >= '0' && hex_char <= '9') {
		    binaryAddress = binaryAddress + (hex_char - '0');
	    }

	    // if A-F
	    if(hex_char >= 'A' && hex_char <= 'F') {
	    	binaryAddress = binaryAddress + (hex_char - 'A' + 10);
	    }

	    // if a-f
	    if(hex_char >= 'a' && hex_char <= 'f') {
	    	binaryAddress = binaryAddress + (hex_char - 'a' + 10);
	    }
    
        i++;
    }
    return binaryAddress;
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
