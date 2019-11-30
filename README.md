# life
Conway's Game of Life

The code can loop over every cell in series to calculate the next generation, or divide the grid up into sunserction and process them in parrallel.  Running a 500 by 500 grid for 100 generations takes 367 milliseconds using serial processing while the same test using two thread parallel processing takes 263 msecs.
