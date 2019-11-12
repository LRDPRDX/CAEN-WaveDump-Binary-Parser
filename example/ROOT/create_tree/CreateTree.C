#include "ROOT/CaenTreeCreator.h"
#include "CaenParser.h"


void CreateTree()
{
<<<<<<< HEAD
    CaenTreeCreator tc( caen::Board::N6720, //N6720 
                        "../../../data/",   //data dir
                        "./",               //place the TTree in the current dir
                        "myFirstTree" );    //name the TTree as "myFirstTree"

    tc.SetIntervals( 0.1, 0.1, 2 );//baseline - from 0 to 50 ns; integral - from 100 to 2000 ns

    //create a TTree only from the one directory "mult" in the data directory
    tc.CreateTree( CaenTreeCreator::INCLUDE, "mult" );
=======
    CaenTreeCreator tc( caen::Board::N6720,
                        "../../../data/",
                        "./",
                        "myFirstTree" );

    tc.SetIntervals( 0.03, 0.03, 1 );

    tc.CreateTree();
>>>>>>> 8cb2038e5750cfb36560e640fc80ff40503f2d94
}
