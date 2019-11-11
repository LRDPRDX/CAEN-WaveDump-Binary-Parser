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
        p.SetPathToFile( "../../../data/single/single.dat" );
    caen::Event e;
 
 
    p.ReadEvent( e );
    e.Print();
 
    caen::Analyzer a;
        a.SetBaselineInterval( 0.02 );
        a.SetGate( 0.2, 0.8 );
    a.Analyze( e );
    
    TGraph* g = new TGraph( e.GetSize() );
        g->SetLineColor( 9 );
        g->SetMarkerStyle( 9 );
        g->SetMarkerColor( 9 );
        g->SetFillColor( 9 );
 
    TLine* bl = new TLine( 0., 0., e.GetLength(), 0. );
        bl->SetLineColor( kRed );
 
    for( auto point = e.cbegin(); point != e.cend(); ++point )
    {   
                g->SetPoint( std::distance( e.cbegin(), point ), point->time, point->voltage - a.GetBaseline() );
    }

    TCanvas* c = new TCanvas;
        c->SetGrid();
        c->SetFillColor( kBlack );

    TLegend* leg = new TLegend( 0.8, 0.9, 0.9, 0.8 );
        leg->SetFillColor( kBlack );
        leg->SetLineColor( kWhite );
        leg->SetTextColor( kWhite );
        leg->AddEntry( g, "Data", "f" );
        leg->AddEntry( bl, "Baseline", "l" );

    g->Draw( "APL" );
        g->GetXaxis()->SetTitle( "time, us" );
        g->GetYaxis()->SetTitle( "amplitude, mV" );
        g->GetXaxis()->SetTitleColor( kWhite );
        g->GetXaxis()->SetAxisColor( kWhite );
        g->GetXaxis()->SetLabelColor( kWhite );
        g->GetYaxis()->SetTitleColor( kWhite );
        g->GetYaxis()->SetAxisColor( kWhite );
        g->GetYaxis()->SetLabelColor( kWhite );
    bl->Draw( "same" );
    leg->Draw( "same" );
}
