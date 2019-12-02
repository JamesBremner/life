#include <mutex>

class world
{
public:
    int ncols;
    int nrows;
    std::vector< bool > grid;
    int generation;

    world( int c, int r )
        : ncols( c )
        , nrows( r )
        , grid( c * r )
        , generation( 0 )
    {
    }
    world()
    : world( 1, 1 )
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
    /// Next column and row in grid
    void increment( int& col, int& row )
    {
        col += 1;
        if( col == ncols )
        {
            row += 1;
            col = 0;
        }
    }
    void ThreadSafeCopy( world& newWorld )
    {
        static std::mutex M;
        std::lock_guard<std::mutex> lck ( M );
        newWorld = *this;
    }
};

void NextGeneration( world& theWorld );
void NextGenerationParrallel( world& theWorld );
