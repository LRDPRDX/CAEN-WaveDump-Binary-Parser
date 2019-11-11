#include <iostream>

#include "CaenAuxiliary.h"
#include "CaenParser.h"
#include "CaenEvent.h"


namespace caen
{
    bool Parser::ReadEventAt( pos_t pos, Event& event ) const
    {
        //clear vector of points and set event's position to 0
        event.Clear();

        std::ifstream file;
        file.exceptions( std::ios::failbit | std::ios::badbit );
        try
        {
            file.open( pathToFile, std::ios::binary );
            //start reading from the first position after the last event read
            file.seekg( pos );
            //read event information first: board ID, trigger time tag, ...
            file.read( reinterpret_cast<char*>( &event.header ), sizeof( event.header ) ); 
            //dataSize is the size (in bytes) of a waveform = total size of event - size of header 
            uint32_t dataSize = (event.header.EVENT_SIZE - sizeof(event.header));
            //must contain whole number of points. 
            if( !(dataSize % sizeof(SAMPLE_SIZE)) )
            {
                //read wavefoem
                for( uint32_t i = 0; i < (dataSize / sizeof(SAMPLE_SIZE)); i++ )
                {
                    SAMPLE_SIZE adcValue;
                    file.read( reinterpret_cast<char*>( &adcValue ), sizeof( adcValue ) );
                    event.points.push_back( { RealTime( i, board ), RealVoltage( adcValue, board ) } );
                }
                event.startPos = pos;
                event.endPos = file.tellg();
                event.timeStep = board.GetSampleTime();
            }
            else//number of points is not a whole number
            {
                PrintWarning( "Data block seems to be corrupted. Number of points is not a whole number. Failure occurred reading an event at:" );
                PrintCurrentPosition();

                file.close();
                return false;
            }
            file.close();
        }
        catch( const std::ifstream::failure& e )
        {
            //make sure that before reaching the EOF
            //no data has been read
            if( file.eof() and !file.gcount() )
            {
                PrintInfo( "EOF has been reached. All data has been read successfully." );
            }
            else
            {
                PrintWarning( "Couldn't open/read/close binary. Check if\n\t a) You forgot to set path to binary file or it is incorrect. Use `Parser::SetPathToFile` member function to set path to binary.\n\t b) Data block is corrupted.\nFailure occurred reading an event at:" );
                PrintCurrentPosition();
                std::cout << "Path to file: '" << pathToFile << "'" << std::endl; 
            }
            return false;
        }
        return true;
    }


    bool Parser::ReadEvent( Event& event )
    {
        if( ReadEventAt( currentPosition, event ) )
        {
            //update input position indicator
            //next event will be being read from this point 
            currentPosition = event.endPos;
            //Increment number of successfully read events
            nEvents++;

            return true;
        }
        else
        {
            return false;
        }
    }


    void Parser::Reset()
    {
        currentPosition    = 0;
        nEvents            = 0;
    }


    void Parser::SetPathToFile( const std::string& newPathToFile )
    {
        Reset();
        pathToFile = newPathToFile; 
    }


//    bool Parser::Check( const std::string& pathToConfigFile ) const
//    {
//        return true;
//    }


    void Parser::PrintCurrentPosition() const
    {
        std::cout << "Current position: " << std::hex << std::showbase << currentPosition << "\n";
        std::cout << std::dec;
    }


    void Parser::Print() const
    {
        PrintHeader( "PARSER", 80 ); 
        PrintParam<std::string>( "Path to binary file", pathToFile, 40 ); 
        PrintParam<size_t>( "Number of successfully read events", nEvents, 40 ); 
        std::cout << "\n";
        PrintCurrentPosition();
        PrintHRule( 80 );
    }
}
