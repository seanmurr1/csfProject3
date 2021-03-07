// Cache.h

#ifndef _CACHE_H
#define _CACHE_H

// Includes go here:
#include "Set.h"
#include <vector>

// Class to represent a Cache
class Cache {
		// Statistics:
		long loads;	// Total loads
		long stores;	// Total stores
		long lHits;	// Load hits
		long lMisses;	// Load misses
		long sHits;	// Store hits
		long sMisses;	// Store misses
		long cycles;	// Total cycles

		// Cache parameters:
		int sets;	// Number of sets per cache
		int blocks;	// Number of blocks per set
		int bytes;	// Number of bytes per block

		// Address information:
		int offset;	// Off-set bits
		int index;	// Index bits	
		int tag; 	// Tag bits
		
		// Vector of sets:
		std::vector<Set> sets;
			
		// Parameters for specific behavior: 
		bool writeAllocate;	// If false, then no-write-allocate
		bool writeThrough;	// If false, then write-back
		bool lru;		// If false, then fifo

	// Public functions
	public:
		// Constructor
		Cache(int sets, int blocks, int bytes, bool writeAl, bool writeTh, bool lru);
		// Destructor (not sure if needed, but maybe for vectors)
		~Cache();		

		// Load function
		void load(uint32_t address);

		// load for FIFO

		// load for LRU

		// method to handle eviction

		// Store function
		void store(uint32_t address);

		// Print statistics
		void printSummary();

	// Helper functions
	private:
		// Store with write allocate and write through
		void storeWriteAlTh(uint32_t address);

		// Store with write allocate and write back
		void storeWriteAlBa(uint32_t address);

		// Store with no write allocate (assumes write through)
		void storeNoWriteAl(uint32_t address);
		// Obtain various address bits of address	
		void obtainAddressBits(uint32_t address, int &offsetBits, int &indexBits, int &tagBits);
};

#endif
