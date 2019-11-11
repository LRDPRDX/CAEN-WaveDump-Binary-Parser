#ifndef CAEN_PARSER_H
#define CAEN_PARSER_H

#include <string>
#include <fstream>

#include "CaenBoard.h"


namespace caen
{
    class Event;

    class Parser
    {
        //This class does all work in the read-and-parse procedure
        public :
            typedef typename std::fstream::pos_type pos_t;

        protected :
            Board                   board;//board model

            pos_t                   currentPosition;//input position indicator
            std::string             pathToFile;//file to parse
            size_t                  nEvents;//number of processed events


        public :
            Parser( Board board ) :
                board( board ),
                currentPosition( 0 ),
                pathToFile( "" ),
                nEvents( 0 )
            { }

            bool                    ReadEventAt( pos_t pos, Event& event ) const;
            bool                    ReadEvent( Event& event );

            pos_t                   GetCurrentPosition() const { return currentPosition; }
            std::string             GetPathToFile() const { return pathToFile; }
            size_t                  GetNEvents() const { return nEvents; }

            void                    Reset();
            void                    SetPathToFile( const std::string& newPathToFile );

            //bool                    Check( const std::string& pathToConfigFile ) const;
            void                    PrintCurrentPosition() const;
            void                    Print() const;
    };
}
#endif
