/*
 * CSF Assignment 3
 * Simulating and evaluating caches
 * Shelby Coe scoe4
 * Sean Murray smurra42
 */
 
// Helper funtions for main.cpp

// Includes go here:
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

#include "helper.h"
#include "Set.h"
#include "Cache.h"

// using statements go here:
using std::string;

helper::helper() {

}

// Converts hex string to decimal address
uint32_t helper::hexAddressToDecimal(string hexAddress) {
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

// Checks if a number is a positive power of two
bool helper::posPowerOfTwo(int num) {
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

// Checks if a string argument is valid among two options
void helper::validArgument(string argument, string option1, string option2) {
	if (argument.compare(option1) == 0 || argument.compare(option2) == 0) {
		return;
	}
	std::cerr << "Error: Invalid argument" << std::endl;
}

// Checks validity of command line arguments
void helper::checkValidArgs(int numSets, int numBlocks, int numBytes, string writeAllocateOrNot, string writeThroughOrBack, bool &writeAllocate, bool &writeThrough) {
	// Checking sets
	if(!posPowerOfTwo(numSets)){  // Number of sets in cache has to be a positive power of 2
        	std::cerr << "Error: Not a valid number of sets" << std::endl;
        	exit(1);
    	}
	// Checking blocks
	if(!posPowerOfTwo(numBlocks)){     // Number of blocks in set has to be a positive power of 2
	        std::cerr << "Error: Not a valid number of blocks" << std::endl;
        	exit(1);
     	}
	// Checking bytes
	if((numBytes < 4) | !posPowerOfTwo(numBytes)){ // Number of bytes in block has to be a positive power of 2 and at least 4
        	std::cerr << "Error: Not a valid number of bytes" << std::endl;
        	exit(1);
    	}

	// Checking write allocate or not
	validArgument(writeAllocateOrNot, "write-allocate", "no-write-allocate");
	if (writeAllocateOrNot.compare("write-allocate") == 0) {
        writeAllocate = true;
    } else {
    	writeAllocate = false;
	}

	// Checking write through or back
    validArgument(writeThroughOrBack, "write-through", "write-back");
	if (writeThroughOrBack.compare("write-through") == 0){
    	writeThrough = true;
    } else {
        writeThrough = false;
   	 }

    	// If write back and no write allocate print error message
    if (!writeAllocate & !writeThrough) {
        std::cerr << "Error: Invalid combination, if miss, data will never make it to memory" << std::endl;
        exit(1);
    }
}

// Simulates cache
int helper::processCache(int numSets, int numBlocks, int numBytes, bool writeAllocate, bool writeThrough, bool lru) {
	// Create cache
    Cache cache = Cache (numSets, numBlocks, numBytes, writeAllocate, writeThrough, lru);
    string line;
    string load;
    string hexAddress;
	// Processing input
    while (getline(std::cin, line)) {
        // break up the line into arguments
        load = line.substr(0,1);
        hexAddress = line.substr(4, 8);
        uint32_t binaryAddress = hexAddressToDecimal(hexAddress);
		
		// Checking operation
        if (load.compare("l") == 0) {
            cache.load(binaryAddress);
        } else if (load.compare("s") == 0) {
       		cache.store(binaryAddress);
        } else {
            std::cerr << "Error: Not 'l' or 's'" << std::endl;
            exit(1);
        }
    }
	// Printing summary
    cache.printSummary();	
    return 0;
}

// Processes command-line arguments
int helper::processArgs(int argc, char* argv[]) {
	// Checking for correct number of args
	if (argc < 6) { 
        std::cerr << "Error: Missing arguments" << std::endl;
        exit(1);
    }
	// Obtaining arguments
	int numSets = atoi(argv[1]);
	int numBlocks = atoi(argv[2]);
	int numBytes = atoi(argv[3]);
	string writeAllocateOrNot(argv[4]);
	string writeThroughOrBack(argv[5]);
   
	bool writeAllocate;
	bool writeThrough;
	bool lru = true;	

	// Checking arguments
	checkValidArgs(numSets, numBlocks, numBytes, writeAllocateOrNot, writeThroughOrBack, writeAllocate, writeThrough);


	// A cache with n sets of 1 block each is direct-mapped (not associative)
   	 if (numBlocks != 1) {
        	// Cache is associative
        	if (argc < 7) {    // check to make sure enough arguments
        		std::cerr << "Error: Missing argument specifying eviction" << std::endl;
        		exit(1);
        	}
		// Obtaining eviction protocol 
        	string evictionType(argv[6]);
        	validArgument(evictionType, "lru", "fifo");
        	if (evictionType.compare("lru") == 0){
         		lru = true;
        	} else {
          		lru = false;
        	}
    	}


	// Processing cache
	return processCache(numSets, numBlocks, numBytes, writeAllocate, writeThrough, lru);
}

