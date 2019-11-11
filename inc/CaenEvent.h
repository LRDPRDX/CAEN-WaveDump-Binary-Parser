#ifndef CAEN_EVENT_H
#define CAEN_EVENT_H

#include <fstream>
#include <ostream>
#include <vector>
#include <cstddef>

#include "CaenADC.h"


namespace caen
{

    class Parser;

    struct Point
    {
        //This structure represents one data point in a waveform
        double time;//real time (in nanosecs)
        double voltage;//real voltage (in volts)

        Point( double time, double voltage ) : time( time ), voltage( voltage ) { }
    };

    inline std::ostream& operator<<( std::ostream& os, const Point& point )
    {
        os << "( " << point.time << ", " << point.voltage << " )";
        return os;
    }


    class Event
    {
        //This class represents a single event
        public :
            enum                    POLARITY { NEGATIVE, POSITIVE };
            friend std::ostream& operator<<( std::ostream& os, const POLARITY& pol )
            {
                switch( pol )
                {
                    case( NEGATIVE ) : os << "NEGATIVE"; break;
                    case( POSITIVE ) : os << "POSITIVE"; break;
                } 

                return os;
            }

            typedef typename        std::fstream::pos_type pos_t;


        protected :
            pos_t                   startPos;//position (in bytes) when this event starts in a binary file 
            pos_t                   endPos;//position (in bytes) next to the last byte of this event

            Header                  header;//header of an event (see WaveDump documentation) 
            std::vector<Point>      points;//data points (waveform) 
            POLARITY                polarity;//signal polarity
            double                  timeStep;//time difference between two neighboring points [us]


        public :
            typedef typename std::vector<Point>::const_iterator const_point_iterator;
            const_point_iterator cbegin() const { return points.cbegin(); }
            const_point_iterator cend() const { return points.cend(); }

            Event() :
                startPos( 0 ),
                endPos( 0 ),
                polarity( NEGATIVE ),
                timeStep( 0 )
            {
                header.BOARD_ID = 0;
                header.CHANNEL = 0;
                header.EVENT_COUNTER = 0;
                header.EVENT_SIZE = 0;
                header.PATTERN = 0;
                header.TRIGGER_TIME_TAG = 0;
            }

            void Clear();

            void        SetPolarity( POLARITY pol ) { polarity = pol; }

            pos_t       GetStartPosition() const    { return startPos; }
            pos_t       GetEndPosition() const      { return endPos; }
            size_t      GetSize() const             { return points.size(); }
            double      GetLength() const           { return points.size() * timeStep; }
            POLARITY    GetPolarity() const         { return polarity; }
            double      GetTimeStep() const         { return timeStep; }

            //Header info
            uint32_t    GetBoardID() const          { return header.BOARD_ID; }
            uint32_t    GetPattern() const          { return header.PATTERN; }
            uint32_t    GetChannel() const          { return header.CHANNEL; }
            uint32_t    GetEventCounter() const     { return header.EVENT_COUNTER; }
            uint32_t    GetTriggerTimeTag() const   { return header.TRIGGER_TIME_TAG; }

            void        Print() const;

            friend class Parser;
    };
}
#endif
