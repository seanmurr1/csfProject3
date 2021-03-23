// Helper functions for main


#include <string>


uint32_t hexAddressToDecimal(std::string hexAddress);

bool posPowerOfTwo(int num);

void validArgument(std::string argument, std::string option1, std::string option2);

int processArgs(int argc, char* argv[]);

void checkValidArgs(int numSets, int numBlocks, int numBytes, std::string writeAllocateOrNot, std::string writeThroughOrBack, bool &writeAllocate, bool &writeThrough);

int processCache(int numSets, int numBlocks, int numBytes, bool writeAllocate, bool writeThrough, bool lru);
