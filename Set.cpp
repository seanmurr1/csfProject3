// Set.cpp

#include "Set.h"

using std::vector;


// Constructor
Set::Set(int blocks, int bytes, bool writeAl, bool writeTh, bool lru) : blocks(blocks), bytes(bytes), writeAllocate(writeAl), writeThrough(writeTh), lru(lru) {

	curSize = 0;			// We start with 0 valid blocks
	blockVec.reserve(blocks);	// Vector of blocks

	// Adding starting blocks to set
	for (int i = 0; i < blocks; i++) {
		blockVec.push_back(Block());
	}	
}

// Destructor
Set::~Set() {
	// TODO?
}

bool Set::store(uint32_t tagBits, long &cycles) {
	// TODO
	// Place holder to get rid of compiler warning
	if (tagBits > 0) {
		cycles++;
	}
	
	return false;
}


// Loads data into a set
bool Set::load(uint32_t tagBits, long &cycles) {
	// Initial overhead for accessing cache: 1 cycle
	cycles++;

	// Checking all blocks. TODO maybe change this to iterator later if needed
	for (int i = 0; i < blocks; i++) {
		// Case: we have a load/read hit. Don't need to alter cache
		if (blockVec[i].tag == tagBits && blockVec[i].valid) {
			// Update order values according to protocol
			if (lru) {
				updateOrders(blockVec[i].order);
			}
			// Signify load/read hit
			return true;
		}
	}

	// At this point we have a load/read miss. We must evict a block to load new block
	evictAndLoad(tagBits, cycles); // Evicting and loading new block

	// Overhead for passing load back to processor
	// TODO is this necessary?
	cycles++;

	// Signify load/read miss
	return false;
}

// Loads after a load miss. Fills in invalid block or evicts according to protocol
void Set::evictAndLoad(uint32_t tagBits, long &cycles) {
	// Case: we have unused blocks
	if (curSize != blocks) {
		// Loading into first empty block
		loadIntoEmpty(tagBits);
		// Overhead for loading block
		cycles += (bytes / 4) * 100;
		return;
	}

	// Case: all blocks are used, we must evict one
	
	for (int i = 0; i < blocks; i++) {
		// Found block to evict (regardless of FIFO or LRU)
		if (blockVec[i].order == blocks - 1) {
			updateOrders(blockVec[i].order);	// Update orders, should be fine for FIFO or LRU
			blockVec[i].tag = tagBits;		// Update block tag
			// Checking if block was dirty
			if (blockVec[i].dirty) {
				// Overhead for writing dirty block back to main memory
				cycles += (bytes / 4) * 100;
			}
			// Overhead for loading new block
			cycles += (bytes / 4) * 100;
			return;
		}
	}
}


// Loads a block into set, assuming that there are invalid blocks (AKA unused ones)
void Set::loadIntoEmpty(uint32_t tagBits) {
	// Have we inserted the new block yet?
	bool inserted = false;
	// Checking all blocks
	for (int i = 0; i < blocks; i++) {
		// Case: we found first unused block
		if (!blockVec[i].valid && !inserted) {
			blockVec[i].tag = tagBits;	// Updating tag
			blockVec[i].valid = true;		// Setting to valid
			blockVec[i].order = 0;		// Order is 0 (regardless of FIFO or LRU)
			inserted = true;		// Prevent further insertions
		} 
		// Updating all other valid blocks, incrementing order by 1
		else if (blockVec[i].valid) {
			blockVec[i].order++;
		}
	}
	// Update size (number of valid blocks in set)
	curSize++;
}


// Updates orders of blocks, should work for both FIFO or LRU
void Set::updateOrders(int orderPartition) {
	// Checking all blocks
	for (int i = 0; i < blocks; i++) {
		// Checking valid blocks
		if (blockVec[i].valid) {
			// Block that was a hit has order updated to 0
			if (blockVec[i].order == orderPartition) {
				blockVec[i].order = 0;
			} 
			// Other blocks with order below partition have order increased by 1
			else if (blockVec[i].order < orderPartition) {
				blockVec[i].order++;
			}
		}
	}
}


