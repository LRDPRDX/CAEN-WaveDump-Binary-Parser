#include "ROOT/CaenTreeCreator.h"
#include "CaenParser.h"


void CreateTree()
{
    CaenTreeCreator tc( caen::Board::N6720, //N6720 
                        "../../../data/",   //data dir
                        "./",               //place the TTree in the current dir
                        "myFirstTree" );    //name the TTree as "myFirstTree"

    tc.SetIntervals( 0.1, 0.1, 2 );//baseline - from 0 to 100 ns; integral - from 100ns to 2us 

    //create a TTree only from the one directory "NaITl" in the data directory
    tc.CreateTree( CaenTreeCreator::INCLUDE, "NaITl" );
}
