Shelby Coe: scoe4

Sean Murray: smurra42

Part (b): Best cache, contributions

link to google sheet with data:
https://docs.google.com/spreadsheets/d/1oFNBdT1XzQt9Xwpo-aKODD9hl1OUaJxzQdgMhDp00D4/edit?usp=sharing 

Write back and no write allocate is not a possible combination so this is defnitely not the best overall cache configuration.

In our tests, we ran the simulations with a fixed storage capacity of 16384 bytes (16 KB) and then varied the set associativity and write policies in order to perform thorough, consistent tests.
Taking into account a variety of factors such as the hit rate and cycles, fully associative caches seemed to be the best. 
However, fully associative caches are diffult to create and costly so taking simplicity into account, set associative caches are probably the best since according to the data we found, they are almost as good as fully associative caches.



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
