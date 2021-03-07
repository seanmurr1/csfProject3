// Set.h

#ifndef _SET_H
#define _SET_H

// Includes go here:
#include <vector>

// Class to represent a set in a Cache
class Set {

	int blocks;
	int bytes;
	bool lru;

	std::vector<Block> blocks;
		
	// Constructor
	Set(int blocks, int bytes, bool lru);
	// Destructor
	~Set();

	// could use a tuple (int, bool)
	


	bool load(int offsetBits, int tagBits, long &cycles);

	// Nested class to represent a block
	class Block {
		uint32_t tag;	// Tag for block
		int order;	// Keep track of order based on FIFO or LRU
		bool dirty;	// Relevant for write-back protocol
		std::vector<uint32_t> data;	// vector of 4-byte values
	};
};

#endif
