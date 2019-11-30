#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

class world
{
public:
    int ncols;
    int nrows;
    vector< bool > grid;
    world( int c, int r )
        : ncols( c )
        , nrows( r )
        , grid( c * r )
    {

    }
    bool isAlive( int col, int row ) const
    {
        return grid[col + ncols*row ] == true;
    }
    void born( int col, int row )
    {
        grid[ col + ncols * row ] = true;
    }
    void die( int col, int row )
    {
        grid[ col + ncols * row ] = false;
    }
    int aliveCount()
    {
        int count = 0;
        for( auto c : grid )
            if( c )
                count++;
        return count;
    }
    void clear()
    {
        grid.clear();
        grid.resize( ncols * nrows );
    }
};

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

void test()
{
    world theWorld( 5, 5 );
    theWorld.born( 2, 2 );
    if( theWorld.aliveCount() != 1 )
    {
        std::cout << "failed 1\n";
        exit(1);
    }
    NextGeneration( theWorld );
    if( theWorld.aliveCount() != 0 )
    {
        std::cout << "failed 2\n";
        exit(1);
    }
    theWorld.clear();
    theWorld.born( 2, 2 );
    theWorld.born( 2, 3 );
        if( theWorld.aliveCount() != 2 )
    {
        std::cout << "failed 3\n";
        exit(1);
    }
    NextGeneration( theWorld );
    if( theWorld.aliveCount() != 0 )
    {
        std::cout << "failed 4\n";
        exit(1);
    }
    theWorld.clear();
    theWorld.born( 2, 2 );
    theWorld.born( 2, 1 );
    theWorld.born( 2, 3 );
        if( theWorld.aliveCount() != 3 )
    {
        std::cout << "failed 5\n";
        exit(1);
    }
    NextGeneration( theWorld );
    if( theWorld.aliveCount() != 1 )
    {
        std::cout << "failed 6\n";
        exit(1);
    }
    cout << "all test passed\n";
}

int main()
{
    test();

    world theWorld( 5, 5 );
    initRandom( theWorld, 10  );
    NextGeneration( theWorld );
    cout << "Hello world!" << endl;
    return 0;
}
