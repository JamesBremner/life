#include "wex.h"

#include "life.h"

void visualizer( world& theWorld, int refreshRateMsecs )
{
    using namespace wex;

    // construct graphics display
    gui& form = maker::make();
    form.move({ 50,50,400,400});

    // handle drawing request events
    form.events().draw([&]( PAINTSTRUCT& ps )
    {
        world worldcopy;
        theWorld.ThreadSafeCopy( worldcopy );
        form.text("Life generation "+ std::to_string( worldcopy.generation )
                  + " alive " + std::to_string( theWorld.aliveCount() ));

        shapes S( ps );
        S.color( 0x0000FF );

        // loop over the grid
        int col = 0;
        int row = 0;
        for( auto&& c : worldcopy.grid )
        {
            // if cell is alive, color pixel red
            if( c )
                S.pixel( col, row );

            worldcopy.increment( col, row );
        }
    });

    if( refreshRateMsecs > 0 )
    {
        // create timer handler to update display
        form.events().timer([&]
        {
            form.update();
        });
        timer t( form, 1000 );
    }

    // display
    form.show();
    form.run();
}
