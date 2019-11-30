#include "wex.h"

#include "life.h"

void visualizer( world& theWorld)
{
    using namespace wex;

    // construct graphics display
    gui& form = maker::make();
    form.move({ 50,50,400,400});

    // handle drawing request events
    form.events().draw([&]( PAINTSTRUCT& ps )
    {
        shapes S( ps );
        S.color( 0x0000FF );

        // loop over the grid
        int col = 0;
        int row = 0;
        for( auto&& c : theWorld.grid )
        {
            // if cell is alive, color pixel red
            if( c )
                S.pixel( col, row );

            theWorld.increment( col, row );
        }
    });

    // display
    form.show();
    form.run();
}
