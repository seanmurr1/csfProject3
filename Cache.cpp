// Cache.cpp

#include "Cache.h"
#include <cmath>

using std::vector;

// Constructor
Cache::Cache(int sets, int blocks, int bytes, bool writeAl, bool writeTh, bool lru) : loads(0), stores(0), lHits(0), lMisses(0), sHits(0), sMisses(0), cycles(0), sets(sets), blocks(blocks), bytes(bytes), writeAllocate(writeAl), writeThrough(writeTh), lru(lru) {

	// Off-set bits
	offset = log2(bytes);
	// Index bits
	index = log2(sets);
	// Tag bits
	tag = 32 - offset - index;


	setVec.reserve(sets);

	//setVec = new Set[sets];
	//for (int i = 0; i < sets; i++) {
	//	setVec[i] = new Set(blocks, bytes, writeAl, writeTh, lru);
	//}
	
	// Vector of sets
	//setVec = new vector<Set>;
	// Adding sets
	for (int i = 0; i < sets; i++) {
		setVec.push_back(Set(blocks, bytes, writeAl, writeTh, lru));
	}
	
}


// Destructor
Cache::~Cache() {
	// TODO?
//	delete [] setVec;
}

// Loads address
void Cache::load(uint32_t address) {
	// Address info
	uint32_t indexBits;
	uint32_t tagBits;
	// Obtain address bit information
	obtainAddressBits(address, indexBits, tagBits);	
	
	// Loading to set in question
	bool hit = setVec[indexBits].load(tagBits, cycles);

	// Updating statistics based on result
	if (hit) {
		lHits++;
	} else {
		lMisses++;
	}
	loads++;
}

// Stores address
void Cache::store(uint32_t address) {
	// Address info
	uint32_t indexBits;
	uint32_t tagBits;
	// Obtaining address bit info
	obtainAddressBits(address, indexBits, tagBits);

	// Storing to set in question
	bool hit = setVec[indexBits].store(tagBits, cycles);

	// Updating statistics based on result
	if (hit) {
		sHits++;
	} else {
		sMisses++;
	}
	stores++;
}

void Cache::obtainAddressBits(uint32_t address, uint32_t &indexBits, uint32_t &tagBits) {
	// Case: Fully-Associative
	if (index == 0) {
		indexBits = 0;
		//offsetBits = address & ~(~0U << offset);
		tagBits = address >> offset;
	} 
	// Case: Direct or Set-Associative
	else {
		indexBits = (address >> offset) & ~(~0U << index); 
		//offsetBits = address & ~(~0U << offset);
		tagBits = address >> (offset + index);
	}
}
