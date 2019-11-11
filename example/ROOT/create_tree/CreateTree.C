#include "ROOT/CaenTreeCreator.h"
#include "CaenParser.h"


void CreateTree()
{
    CaenTreeCreator tc( caen::Board::N6720,
                        "../../../data/",
                        "./",
                        "myFirstTree" );

    tc.SetIntervals( 0.03, 0.03, 1 );

    tc.CreateTree();
}
