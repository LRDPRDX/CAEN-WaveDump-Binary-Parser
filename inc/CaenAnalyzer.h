#ifndef CAEN_ANALYZER_H
#define CAEN_ANALYZER_H

#include <stdexcept>
#include <vector>

#include "CaenEvent.h"


namespace caen
{
    class Analyzer
    {
        public :
            enum        BASELINE { AVERAGE, MODE };
            friend std::ostream& operator<<( std::ostream& os, const BASELINE& bl )
            {
                switch( bl )
                {
                    case( AVERAGE ) : os << "AVERAGE"; break;
                    case( MODE )    : os << "MODE"; break;
                } 

                return os;
            }


        protected :
            double      integralStart;
            double      integralStop;
            double      baselineInterval;

            BASELINE    baselineMethod;

            double      baseline;
            Point       maxPoint;
            Point       minPoint;
            double      pkPk;
            double      integral;


        protected :
            double      FindMode( std::vector<double>::iterator first,
                                  std::vector<double>::iterator last );
            void        CalcBaselineMode( const Event& event );
            void        CalcBaselineAverage( const Event& event );
            void        Reset();


        public :
            Analyzer() :
                integralStart( 0. ),
                integralStop( 0. ),
                baselineInterval( 0. ),
                baselineMethod( AVERAGE ),
                baseline( 0. ),
                maxPoint( { 0., 0. } ),
                minPoint( { 0., 0. } ),
                pkPk( 0. ),
                integral( 0. )
            { }

            void    Analyze( const Event& event );

            void    SetGate( double start, double stop )
            {
                integralStart = start;
                integralStop  = stop;
            }
            void    SetBaselineInterval( double T )  { baselineInterval = T; }

            void    SetBaselineMethod( BASELINE method )    { baselineMethod = method; }

            double  GetGateInterval() const                 { return (integralStop - integralStart); }
            double  GetIntegralStart() const                { return integralStart; }
            double  GetIntegralStop() const                 { return integralStop; }
            double  GetBaseline() const                     { return baseline; }
            Point   GetMaxPoint() const                     { return maxPoint; }
            Point   GetMinPoint() const                     { return minPoint; }
            double  GetPkPk() const                         { return pkPk; } 
            double  GetIntegral() const                     { return integral; }

            void    Print() const;
    };
}
#endif
