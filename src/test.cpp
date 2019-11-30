#include <iostream>
#include <vector>

#include "life.h"

using namespace std;

void test()
{
    try
    {
        world theWorld( 5, 5 );
        theWorld.born( 2, 2 );
        if( theWorld.aliveCount() != 1 )
            throw 1;
        NextGeneration( theWorld );
        if( theWorld.aliveCount() != 0 )
            throw 2;
        theWorld.clear();
        theWorld.born( 2, 2 );
        theWorld.born( 2, 3 );
        if( theWorld.aliveCount() != 2 )
            throw 3;
        NextGeneration( theWorld );
        if( theWorld.aliveCount() != 0 )
            throw 4;
        theWorld.clear();
        // two neigbours
        theWorld.born( 2, 2 );
        theWorld.born( 2, 1 );
        theWorld.born( 2, 3 );
        if( theWorld.aliveCount() != 3 )
            throw 5;
        NextGeneration( theWorld );
        if( theWorld.aliveCount() != 1 )
            throw 6;
        if( ! theWorld.isAlive( 2, 2 ) )
            throw 7;
        // three neigbours
        theWorld.born( 2, 2 );
        theWorld.born( 2, 1 );
        theWorld.born( 2, 3 );
        theWorld.born( 1, 2 );
        if( theWorld.aliveCount() != 4 )
            throw 8;
        NextGeneration( theWorld );
        if( theWorld.aliveCount() != 1 )
            throw 9;
        if( ! theWorld.isAlive( 2, 2 ) )
            throw 10;
        // four neigbours
        theWorld.born( 2, 2 );
        theWorld.born( 2, 1 );
        theWorld.born( 2, 3 );
        theWorld.born( 1, 2 );
        theWorld.born( 3, 2 );
        if( theWorld.aliveCount() != 5 )
            throw 11;
        NextGeneration( theWorld );
        if( theWorld.aliveCount() != 0 )
            throw 12;
        if( theWorld.isAlive( 2, 2 ) )
            throw 13;
    }
    catch( int i )
    {
        std::cout << "failed " << i << "\n";
    }
    cout << "single thread tests passed\n";
}

void testParrallel()
{
    try
    {
        world theWorld( 5, 5 );
        theWorld.born( 2, 2 );
        if( theWorld.aliveCount() != 1 )
            throw 1;
        NextGenerationParrallel( theWorld );
        if( theWorld.aliveCount() != 0 )
            throw 2;
        theWorld.clear();
        theWorld.born( 2, 2 );
        theWorld.born( 2, 3 );
        if( theWorld.aliveCount() != 2 )
            throw 3;
        NextGenerationParrallel( theWorld );
        if( theWorld.aliveCount() != 0 )
            throw 4;
        theWorld.clear();
        // two neigbours
        theWorld.born( 2, 2 );
        theWorld.born( 2, 1 );
        theWorld.born( 2, 3 );
        if( theWorld.aliveCount() != 3 )
            throw 5;
        NextGenerationParrallel( theWorld );
        if( theWorld.aliveCount() != 1 )
            throw 6;
        if( ! theWorld.isAlive( 2, 2 ) )
            throw 7;
        // three neigbours
        theWorld.born( 2, 2 );
        theWorld.born( 2, 1 );
        theWorld.born( 2, 3 );
        theWorld.born( 1, 2 );
        if( theWorld.aliveCount() != 4 )
            throw 8;
        NextGenerationParrallel( theWorld );
        if( theWorld.aliveCount() != 1 )
            throw 9;
        if( ! theWorld.isAlive( 2, 2 ) )
            throw 10;
        // four neigbours
        theWorld.born( 2, 2 );
        theWorld.born( 2, 1 );
        theWorld.born( 2, 3 );
        theWorld.born( 1, 2 );
        theWorld.born( 3, 2 );
        if( theWorld.aliveCount() != 5 )
            throw 11;
        NextGenerationParrallel( theWorld );
        if( theWorld.aliveCount() != 0 )
            throw 12;
        if( theWorld.isAlive( 2, 2 ) )
            throw 13;
    }
    catch( int i )
    {
        std::cout << "failed " << i << "\n";
    }
    cout << "multi-thread tests passed\n";
}

