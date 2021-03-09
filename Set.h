// Set.h

#ifndef _SET_H
#define _SET_H

// Includes go here:
#include <vector>
#include <cstdint>

// Class to represent a set in a Cache
class Set {


	int blocks;		// Number of blocks per set
	int bytes;		// Number of bytes per block
	bool writeAllocate;	// write-allocate or no-write-allocate
	bool writeThrough;	// write-through or write-back
	bool lru;		// LRU if true, FIFO if false
	int curSize;		// Current number of valid blocks in set
	

	// Nested class to represent a block
	class Block {
		public:
			uint32_t tag;	// Tag for block
			int order;	// Keep track of order based on FIFO or LRU
			bool dirty;	// Relevant for write-back protocol
			bool valid;	// Valid bit

			// Constructor for block
			Block() : tag(0), order(0), dirty(false), valid(false) { }
	};


	/********** FIELDS: **************/
	// Vector of blocks in set
	std::vector<Block> blockVec;
		

	/********** FUNCTIONS: ************/

	public:
		// Constructor
		Set(int blocks, int bytes, bool writeAl, bool writeTh, bool lru);
		// Destructor
		~Set();

		// Load function	
		bool load(uint32_t tagBits, long &cycles);
		// Store function
		bool store(uint32_t tagBits, long &cycles);
	private:
		void loadIntoEmpty(uint32_t tagBits);

		void evictAndLoad(uint32_t tagBits, long &cycles);

		void updateOrders(int orderPartition);

};

#endif
