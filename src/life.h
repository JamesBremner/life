class world
{
public:
    int ncols;
    int nrows;
    std::vector< bool > grid;
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

void NextGeneration( world& theWorld );
void NextGenerationParrallel( world& theWorld );
