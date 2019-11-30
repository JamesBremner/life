#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


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
void NextGeneration( world& theWorld )
{
    // next generation
    world next( theWorld.ncols, theWorld.nrows );

    // loop over cells in grid
    int row = 0;
    int col = 0;
    for( int c = 0; c < (int) theWorld.grid.size(); c++ )
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


int main()
{
    void test();
    test();

    world theWorld( 5, 5 );
    initRandom( theWorld, 10  );
    NextGeneration( theWorld );
    cout << "Hello world!" << endl;
    return 0;
}
