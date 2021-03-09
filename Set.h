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
	int curSize;

	std::vector<Block> blocks;
		
	// Constructor
	Set(int blocks, int bytes, bool lru);
	// Destructor
	~Set();

	// could use a tuple (int, bool)
	


	bool load(uint32_t tagBits, long &cycles);

	void evictAndLoad(uint32_t tagBits, long &cycles);

	void updateOrders(int orderPartition);

	void loadFromEmpty(uint32_t tagBits);

	// Nested class to represent a block
	class Block {
		uint32_t tag;	// Tag for block
		int order;	// Keep track of order based on FIFO or LRU
		bool dirty;	// Relevant for write-back protocol
		bool valid;	// Valid bit

		// Constructor for block
		Block() : tag(0), order(blocks - 1), dirty(false), valid(false) { }
	};
};

#endif
