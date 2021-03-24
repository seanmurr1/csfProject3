Shelby Coe: scoe4

Sean Murray: smurra42

Part (b): Best cache, contributions

link to google sheet with data:
https://docs.google.com/spreadsheets/d/1oFNBdT1XzQt9Xwpo-aKODD9hl1OUaJxzQdgMhDp00D4/edit?usp=sharing 

Write back and no write allocate is not a possible combination so this is defnitely not the best overall cache configuration.

In our tests, we ran the simulations with a fixed storage capacity of 16384 bytes (16 KB) and then varied the set associativity, write policy, and eviction policy in order to perform thorough, consistent tests, covering all possible cases.
Taking into account a variety of factors such as the hit rate and cycles, fully associative caches with write back and write allocate seemed to be the best. The tests with fully associative cachesand write back and write allcoate achieved the highest hit rates. 
However, fully associative caches are diffult to create and costly. Thus, this efficiency is more of a theoretical standard.

In a more realistic setting, set associative caches are the most efficient. With the same write policy, these achieved hit rates similar to fully associative (97%) and similar total cycles (around 9,000,000 to 10,000,000). Direct mapped caches had much higher cycles but similar hit rates for the most part.

In terms of write policies, write through and no write allocate yielded the worst hit rates, hovering just above 90%. Cycles were also almost double that of write back and write allocate. Write through and write allocate had similar hit rates to write back and write allocate, but double the cycles.

In terms of eviction policies, there was not a major difference in hit rate for FIFO vs. LRU. Usually the total cycles would be less for LRU though.

In terms of optimal and realistic combination, we conclude that a set-associative cache with Write-Back and Write-Allocate and LRU yields the best results in terms of hit rates and total cycles. The overall best specific combination we tested in this category was 128 sets with 8 blocks per set and 16 bytes per block. This had a 97.58% hit rate and 9,859,994 total cycles. 


Contributions:

Sean:
 - Cache class
 - Set class
 - Cache analysis
 - Debugging and refactoring

Shelby:
 - Helper class
 - Main
 - Cycles
 - Cache analysis
 - Debugging and refactoring
