// Cache.h

#ifndef _CACHE_H
#define _CACHE_H

// Includes go here:
#include "Set.h"
#include "Cache.h"
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
		std::vector<Set> setVec;
			
	// Public functions
	public:
		// Constructor
		Cache(int sets, int blocks, int bytes, bool writeAl, bool writeTh, bool lru);
		// Destructor (not sure if needed, but maybe for vectors)
		~Cache();		

		// Load function
		void load(uint32_t address);

		// Store function
		void store(uint32_t address);

		// Print statistics
		void printSummary();

	// Helper functions
	private:
		// Obtain various address bits of address	
		void obtainAddressBits(uint32_t address, uint32_t &indexBits, uint32_t &tagBits);
};

#endif
