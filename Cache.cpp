// Cache.cpp

#include "Cache.h"
#include <cmath>

using std::vector;

// Constructor
Cache::Cache(int sets, int blocks, int bytes, bool writeAl, bool writeTh, bool lru) : sets(sets), blocks(blocks), bytes(bytes), writeAllocate(writeAl), writeThrough(writeTh), lru(lru), loads(0), stores(0), lHits(0), lMisses(0), sHits(0), sMisses(0), cycles(0) {

	// Off-set bits
	offset = log2(bytes);
	// Index bits
	index = log2(sets);
	// Tag bits
	tag = 32 - offset - index;

	// Vector of sets
	sets = new Vector<Set>;
	// Adding sets
	for (int i = 0; i < sets; i++) {
		sets.push_back(new Set(blocks, bytes, lru));
	}

}


// Destructor
Cache::~Cache() {

}
