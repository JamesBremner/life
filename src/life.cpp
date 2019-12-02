#include <vector>
#include <iostream>
#include "life.h"

int livingNeighbours(  const world& theWorld, int col, int row  )
{
    int alive = 0;
    for( int c = col-1; c <=col+1; c++ )
    {
        for( int r = row-1; r <= row+1; r++ )
        {
            if( r != row || c != col )
                if( theWorld.isAlive( c, r ) )
                    alive++;
        }
    }

    //std::cout << row <<" "<<col << " living neighbours " << alive << "\n";

    return alive;
}
