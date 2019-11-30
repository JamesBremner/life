# life
Conway's Game of Life

The code can loop over every cell in series to calculate the next generation, or divide the grid up into sunserction and process them in parrallel.  Running a 500 by 500 grid for 100 generations takes 367 milliseconds using serial processing while the same test using two thread parallel processing takes 263 msecs.

Here are the results for different sized grids:

500 by 500 == 0.3 secs
1000 by 1000 == 1 sec
2000 by 2000 == 4 secs

Grids were initially populated with 25% live cells and ran for 100 generations

Here are the timing results for parrallel computation with two threads:

500 by 500 == 0.2 secs
1000 by 1000 == 0.6 sec
2000 by 2000 == 2.1 secs
