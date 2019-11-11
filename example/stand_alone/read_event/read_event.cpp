/*
o   This is an example of reading a data file
    with the only one event recorded.
    It demonstrates how to use Event's member
    functions to get information about an
    event. 
 */
#include <iostream>

//#define N6742

#include "CaenParser.h"
#include "CaenEvent.h"


int main()
{
    caen::Parser parser( caen::Board::N6720 );
        parser.SetPathToFile( "../../../data/single/single.dat" );
    caen::Event event;

    while( parser.ReadEvent( event ) )
    {
        //Print the event by hand using getters
        std::cout << "Board ID:         " << event.GetBoardID() << "\n";
        std::cout << "TestPattern:      " << event.GetPattern() << "\n";  
        std::cout << "Channel:          " << event.GetChannel() << "\n";
        std::cout << "Event counter:    " << event.GetEventCounter() << "\n"; 
        std::cout << "TriggerTimeTag:   " << event.GetTriggerTimeTag() << "\n";
        std::cout << "Size (# points):  " << event.GetSize() << "\n";
        std::cout << "Length [us]:      " << event.GetLength() << "\n";
        std::cout << "Polarity:         " << event.GetPolarity() << "\n"; 
        //Additional info: where the event starts and ends in the file
        std::cout << std::hex;
        std::cout << "Start position:   " << std::showbase << event.GetStartPosition() << "\n";
        std::cout << "End position:     " << event.GetEndPosition() << "\n";
        std::cout << "Time step [us]:   " << event.GetTimeStep() << "\n";
        std::cout << std::dec;

        //Print the event using built-in printing function
        event.Print();
    } 

    //Print the parser object by hand using its getters
    std::cout << "\n\n";
    std::cout << std::hex;
    std::cout << "Current position: " << std::showbase << parser.GetCurrentPosition() << "\n";
    std::cout << std::dec;
    std::cout << "Path to file:     " << parser.GetPathToFile() << "\n";
    std::cout << "Number of events: " << parser.GetNEvents() << "\n";

    //Print the parser object using built-in printing function
    parser.Print();

    return 0;
}
