#include "ROOT/CaenTreeCreator.h"
#include "CaenParser.h"


void CreateTree()
{
    CaenTreeCreator tc( caen::Board::N6720, //N6720 
                        "../../../data/",   //data dir
                        "./",               //place the TTree in the current dir
                        "myFirstTree" );    //name the TTree as "myFirstTree"

    tc.SetIntervals( 0.1, 0.1, 2 );//baseline - from 0 to 50 ns; integral - from 100 to 2000 ns

    //create a TTree only from the one directory "mult" in the data directory
    tc.CreateTree( CaenTreeCreator::INCLUDE, "mult" );
}
