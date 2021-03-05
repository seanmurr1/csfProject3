// Set.h

#ifndef _SET_H
#define _SET_H

// Includes go here:
#include <vector>

// Class to represent a set in a Cache
class Set {
	std::vector<Block> blocks;


		
	// Constructor
	Set(int blocks, int bytes);
	// Destructor
	~Set();

	// could use a tuple (int, bool)

	// Nested class to represent a block
	class Block {
		int order;	// Keep track of order based on FIFO or LRU
		bool dirty;	// Relevant for write-back protocol
	};
};

#endif
