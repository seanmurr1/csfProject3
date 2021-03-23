// Helper functions for main
// helper.h

#ifndef _HELPER_H
#define _HELPER_H

// Includes go here:
#include "Set.h"
#include "Cache.h"
#include <string>

// Class for helper functions
class helper {

    public:
        helper();

        uint32_t hexAddressToDecimal(std::string hexAddress);

        bool posPowerOfTwo(int num);

        void validArgument(std::string argument, std::string option1, std::string option2);

        int processArgs(int argc, char* argv[]);

        void checkValidArgs(int numSets, int numBlocks, int numBytes, std::string writeAllocateOrNot, std::string writeThroughOrBack, bool &writeAllocate, bool &writeThrough);

        int processCache(int numSets, int numBlocks, int numBytes, bool writeAllocate, bool writeThrough, bool lru);

};

#endif
