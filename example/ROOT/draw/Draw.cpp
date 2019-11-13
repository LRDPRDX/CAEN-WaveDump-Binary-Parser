#include <iostream>

#include "CaenAnalyzer.h"
#include "CaenParser.h"
 
#include <TGraph.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TH1F.h>
#include <TLegend.h>
 
 
void Draw()
{
    caen::Parser p( caen::Board::N6720 );
        p.SetPathToFile( "../../../data/mult/wave0.dat" );
    caen::Event e;
 
 
    p.ReadEvent( e );
    p.ReadEvent( e );
    e.Print();
 
    caen::Analyzer a;
        a.SetBaselineInterval( 0.1 );
        //we don't need to integrate here that is why there is no SetGate()
    a.Analyze( e );

    TCanvas* c = new TCanvas;
        c->SetGrid();
    
    TGraph* g = new TGraph( e.GetSize() );
        g->SetMarkerStyle( 7 );
 
    TLine* bl = new TLine( 0., 0., e.GetLength(), 0. );
        bl->SetLineColor( kRed );
 
    for( auto point = e.cbegin(); point != e.cend(); ++point )
    {   
                g->SetPoint( std::distance( e.cbegin(), point ), point->time, point->voltage - a.GetBaseline() );
    }

    TLegend* leg = new TLegend( 0.8, 0.9, 0.9, 0.8 );
        leg->AddEntry( g, "Data", "pl" );
        leg->AddEntry( bl, "Baseline", "l" );

    g->Draw( "APL" );
        //decoration
        g->GetXaxis()->SetTitle( "time, us" );
        g->GetXaxis()->CenterTitle( kTRUE );
        g->GetYaxis()->SetTitle( "amplitude, mV" );
        g->GetYaxis()->CenterTitle( kTRUE );

    bl->Draw( "same" );
    leg->Draw( "same" );
}
