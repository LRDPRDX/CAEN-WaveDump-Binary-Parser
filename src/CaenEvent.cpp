#include <iostream>

#include "CaenEvent.h"
#include "CaenAuxiliary.h"


namespace caen
{
    void Event::Clear()
    {
        startPos = 0;
        endPos = 0;
        
        points.clear();
        header.BOARD_ID = 0;
        header.CHANNEL = 0;
        header.EVENT_COUNTER = 0;
        header.EVENT_SIZE = 0;
        header.PATTERN = 0;
        header.TRIGGER_TIME_TAG = 0;

        timeStep = 0.;
    }


    void Event::Print() const
    {
        PrintHeader( "EVENT", 65 );
        PrintParam<uint32_t>        ( "Event size [bytes]", header.EVENT_SIZE, 30 ); 
        PrintParam<uint32_t>        ( "Board ID", header.BOARD_ID, 30 ); 
        PrintParam<uint32_t>        ( "Pattern (ONLY for VME boards)", header.PATTERN, 30 ); 
        PrintParam<uint32_t>        ( "Channel", header.CHANNEL, 30 ); 
        PrintParam<uint32_t>        ( "Event counter", header.EVENT_COUNTER, 30 ); 
        PrintParam<uint32_t>        ( "Trigger time tag", header.TRIGGER_TIME_TAG, 30 ); 
        PrintParam<size_t>          ( "Number of points", GetSize(), 30 );
        PrintParam<double>          ( "Time step [us]", GetTimeStep(), 30 );
        PrintParam<double>          ( "Length [us]", GetLength(), 30 );
        PrintParam<Event::POLARITY> ( "Polarity", GetPolarity(), 30 );
        PrintHRule( 65 );
    }
}
