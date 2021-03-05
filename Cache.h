// Cache.h

#ifndef _CACHE_H
#define _CACHE_H

// Includes go here:
#include "Set.h"
#include <vector>

// Class to represent a Cache
class Cache {
		// Statistics
		long loads;	// Total loads
		long stores;	// Total stores
		long lHits;	// Load hits
		long lMisses;	// Load misses
		long sHits;	// Store hits
		long sMisses;	// Store misses
		long cycles;	// Total cycles

		// Cache parameters:
		// Number of sets per cache
		// Number of blocks per set
		// Number of bytes per block
		
		// Vector of sets
		std::vector<Set> sets;			
		// Parameters for specific behavior 
		bool write-allocate;	// If false, then no-write-allocate
		bool write-through;	// If false, then write-back
		bool lru;		// If false, then fifo

	// Public functions
	public:
		// Constructor
		Cache(int sets, int blocks, int bytes, bool writeAl, bool writeTh, bool lru);
		
		// Destructor (not sure if needed, but maybe for vectors)
		~Cache();		

		// Probably have a load function (what will parameter be)
		void load(uint32_t address);

		// load for FIFO

		// load for LRU

		// method to handle eviction

		// Probably have a store function
		void store(uint32_t address);

		// Print statistics
		void printSummary();

	// Helper functions
	private:
};

#endif
