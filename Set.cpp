// Set.cpp

#include "Set.h"

using std::vector;


Set::Set(int blocks, int bytes, bool lru) {
	// TODO
}



bool Set::load(uint32_t tagBits, long &cycles) {
	// TODO
	
	// Initial overhead for accessing cache: 1 cycle
	cycles++;

	// Checking all blocks. TODO maybe change this to iterator later if needed
	for (int i = 0; i < blocks.size(); i++) {
		// Case: we have a load/read hit. Don't need to alter cache
		if (blocks[i].tag == tagBits && blocks[i].valid) {
			// Update order values according to protocol
			if (lru) {
				updateOrders(blocks[i].order);
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

void Set::evictAndLoad(uint32_t tagBits, long &cycles) {
	// Case: we have unused blocks
	if (curSize != blocks) {
		// Loading into first empty block
		loadFromEmpty(tagBits);
		// Overhead for loading block
		cycles += (bytes / 4) * 100;
		return;
	}

	// Case: all blocks are used, we must evict one
	
	for (int i = 0; i < blocks.size(); i++) {
		// Found block to evict (regardless of FIFO or LRU)
		if (blocks[i].order == blocks - 1) {
			updateOrders(blocks[i].order);	// Update orders, should be fine for FIFO or LRU
			blocks[i].tag = tagBits;		// Update block tag
			// Checking if block was dirty
			if (blocks[i].dirty) {
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
void Set::loadFromEmtpy(uint32_t tagBits) {
	// Have we inserted the new block yet?
	bool inserted = false;
	// Checking all blocks
	for (int i = 0; i < blocks.size(); i++) {
		// Case: we found first unused block
		if (!blocks[i].valid && !inserted) {
			blocks[i].tag = tagBits;	// Updating tag
			blocks[i].valid = true;		// Setting to valid
			blocks[i].order = 0;		// Order is 0 (regardless of FIFO or LRU)
			inserted = true;		// Prevent further insertions
		} 
		// Updating all other valid blocks, incrementing order by 1
		else if (blocks[i].valid) {
			blocks[i].order++;
		}
	}
	// Update size (number of valid blocks in set)
	curSize++;
}

// Updates orders of blocks, should work for both FIFO or LRU
void Set::updateOrders(int orderPartition) {
	// Checking all blocks
	for (int i = 0; i < blocks.size(); i++) {
		// Checking valid blocks
		if (blocks[i].valid) {
			// Block that was a hit has order updated to 0
			if (blocks[i].order == orderPartition) {
				blocks[i].order = 0;
			} 
			// Other blocks with order below partition have order increased by 1
			else if (blocks[i].order < orderPartition) {
				blocks[i].order++;
			}
		}
	}
}


