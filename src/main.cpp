#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <thread>         // std::thread

#include "life.h"

using namespace std;


void initRandom( world& theWorld, int nalive )
{
    /* initialize random seed: */
    srand (time(NULL));

    int k = 0;
    while( k < nalive )
    {
        int col = rand() % theWorld.ncols;
        int row = rand() % theWorld.nrows;
        if( ! theWorld.grid[col + col*row ] )
        {
            theWorld.born( col, row );
            k++;
        }
    }
}
int livingNeighbours(  const world& theWorld, int col, int row  )
{
    int alive = 0;
    col -= 1;
    if( col >= 0 )
        if( theWorld.isAlive( col, row ) )
            alive++;
    col += 2;
    if( col < theWorld.ncols )
        if( theWorld.isAlive( col, row ) )
            alive++;
    col -= 1;
    row -= 1;
    if( row >= 0 )
        if( theWorld.isAlive( col, row ) )
            alive++;
    row += 2;
    if( row < theWorld.nrows )
        if( theWorld.isAlive( col, row ) )
            alive++;
    return alive;
}
/// Calculate next generation for one cell
void NextGeneration( world& next, const world& theWorld, int col, int row )
{
    /*
    - Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
    - Any live cell with two or three live neighbours lives on to the next generation.
    - Any live cell with more than three live neighbours dies, as if by overpopulation.
    - Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
    */

    int nalive = livingNeighbours( theWorld, col, row );
    if( theWorld.isAlive( col, row ) )
    {
        switch( nalive )
        {
        case 2:
        case 3:
            next.born( col, row );
            break;
        case 4:
            next.die( col, row );
        }
    }
    else
    {
        if( nalive == 3 )
            next.born( col, row );
    }
}

/// Calculate next generation for entire wolrd
void NextGeneration( world& theWorld )
{
    // next generation
    world next( theWorld.ncols, theWorld.nrows );

    // loop over cells in grid
    int row = 0;
    int col = 0;
    for( int c = 0; c < (int) theWorld.grid.size(); c++ )
    {
        NextGeneration( next, theWorld, col, row );

        col += 1;
        if( col == theWorld.ncols )
        {
            row += 1;
            col = 0;
        }
    }

    // next generation replaces previous
    theWorld = next;
}

void NextGenerationSubset( world& next, world& theWorld, int first, int last )
{
    // loop over cells in grid subset assigned
    int row = first % theWorld.nrows;
    int col = first / theWorld.nrows;
    for( int c = 0; c < last - first + 1; c++ )
    {
        NextGeneration( next, theWorld, col, row );

        col += 1;
        if( col == theWorld.ncols )
        {
            row += 1;
            col = 0;
        }
    }
}

void NextGenerationParrallel( world& theWorld )
{
    // next generation
    world next( theWorld.ncols, theWorld.nrows );

    int first = 0;
    int last = theWorld.ncols * theWorld.nrows / 2;
    thread a (NextGenerationSubset,std::ref(next),std::ref(theWorld),first,last);
    first = theWorld.ncols * theWorld.nrows - last;
    last = theWorld.ncols * theWorld.nrows - 1 ;
    thread b (NextGenerationSubset,std::ref(next),std::ref(theWorld),first,last);
    a.join();
    b.join();

    // next generation replaces previous
    theWorld = next;
}



int main()
{
    void test();
    test();
    void testParrallel();
    testParrallel();

    world theWorld( 5, 5 );
    initRandom( theWorld, 10  );
    NextGeneration( theWorld );
    cout << "Hello world!" << endl;
    return 0;
}
