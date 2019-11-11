/*
    This is an example of analyzing an event.
 */
#include <iostream>

#include <CaenEvent.h>
#include <CaenParser.h>
#include <CaenAnalyzer.h>


int main()
{
    caen::Parser parser( caen::Board::N6720 );
        parser.SetPathToFile( "../../../data/single/single.dat" );
    caen::Event event;

    caen::Analyzer analyzer;
        //Analysis setup
        analyzer.SetBaselineMethod( caen::Analyzer::AVERAGE );
        analyzer.SetBaselineInterval( 0.02 );//
        analyzer.SetGate( 0.05, 0.2 );//

    parser.ReadEvent( event );//read event
    analyzer.Analyze( event );//analyze event

    analyzer.Print();

    return 0;
}
