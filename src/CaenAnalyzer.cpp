#include <algorithm>

#include "CaenAnalyzer.h"
#include "CaenAuxiliary.h"


namespace caen
{
    double Analyzer::FindMode( std::vector<double>::iterator first,
                               std::vector<double>::iterator last )
    {
        std::sort( first, last );

        double mostFoundElement = *first;
        size_t mostFoundElemntCount = 0;
        double currentElement = *first;
        size_t currentElementCount = 0;

        for( auto it = first; it != last; ++it )
        {
            if( *it == currentElement )
            {
                currentElementCount++;
            }
            else
            {
                if( currentElementCount > mostFoundElemntCount )
                {
                    mostFoundElement = currentElement;
                    mostFoundElemntCount = currentElementCount;
                }
                currentElement = *it;
                currentElementCount = 1;
            }
        }
        if( currentElementCount > mostFoundElemntCount )
        {
            mostFoundElement = currentElement;
            mostFoundElemntCount = currentElementCount;
        }

        return mostFoundElement;
    }


    void Analyzer::CalcBaselineMode( const Event& event )
    {
        std::vector<double> baselinePart;

        for( auto point = event.cbegin(); point != event.cend(); ++point )
        {
            if( point->time > baselineInterval )
            {
                break;
            } 
            baselinePart.push_back( point->voltage );
        }

        if( !baselinePart.empty() )
        {
            baseline = FindMode( baselinePart.begin(), baselinePart.end() );
        }
        else
        {
            PrintWarning( "Pretrigger is empty. No points to calculate baseline" );
        }
    }


    void Analyzer::CalcBaselineAverage( const Event& event )
    {
        baseline = 0.;
        size_t nPoints = 0;
        for( auto point = event.cbegin(); point != event.cend(); ++point )
        {
            if( point->time > baselineInterval )
            { 
                break;
            }
            baseline += point->voltage;
            nPoints++;
        }
        if( nPoints ) { baseline /= nPoints; }
        else
        {
            PrintWarning( "Pretrigger is empty. No points to calculate baseline" );
        }
    }


    void Analyzer::Reset()
    {
        baseline       = 0.;
        maxPoint       = { 0., 0. };
        minPoint       = { 0., 0. };
        pkPk           = 0.;
        integral       = 0.;
    }


    void Analyzer::Analyze( const Event& event )
    {
        Reset(); 

        switch( baselineMethod )
        {
            case( AVERAGE ) :
                CalcBaselineAverage( event ); break;
            case( MODE ) :
                CalcBaselineMode( event ); break;
        }

        bool firstPoint = true;
        for( auto point = event.cbegin(); point != event.cend(); ++point )
        {
            double offset = baseline - point->voltage;

            if( !firstPoint )
            {
                if( offset > (baseline - maxPoint.voltage) ) { maxPoint = *point; }
                if( offset < (baseline - minPoint.voltage) ) { minPoint = *point; }
            }
            else
            {
                maxPoint = minPoint = *point;
                firstPoint = false;
            }
            if( (point->time >= integralStart) and (point->time <= integralStop) )
            {
                integral += offset;
            }
        } 
        integral *= event.GetTimeStep();

        if( event.GetPolarity() == Event::POSITIVE )
        {
            //Changes sign
            integral = -integral;
            //Swap points
            Point temp = maxPoint;
            maxPoint = minPoint;
            minPoint = temp;
        }
        pkPk = minPoint.voltage - maxPoint.voltage;
    }//Analyze


    void Analyzer::Print() const
    {
        PrintHeader( "ANALYZER", 68 );
        PrintParam<double>( "Integral start [us]", GetIntegralStart(), 30 );
        PrintParam<double>( "Integral stop [us]", GetIntegralStop(), 30 );
        PrintParam<double>( "Integral gate [us]", GetGateInterval(), 30 );
        PrintParam<double>( "Integral [us*mV]", GetIntegral(), 30 );
        PrintParam<double>( "Baseline [mV]", GetBaseline(), 30 );
        PrintParam<Point> ( "Max point", GetMaxPoint(), 30 );
        PrintParam<Point> ( "Min point", GetMinPoint(), 30 );
        PrintParam<double>( "Peak to peak [mV]", GetPkPk(), 30 );
        PrintHRule( 68 );
    }
}//caen
