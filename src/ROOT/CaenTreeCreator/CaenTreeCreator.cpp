#include "ROOT/CaenTreeCreator.h"

#include "CaenParser.h"
#include "CaenAnalyzer.h"

#include <TFile.h>
#include <TTree.h>


std::string CaenTreeCreator::MergePaths( const std::string& parent,
                                         const std::string& child ) const
{
    if( parent.empty()  and  child.empty() )
    {
        return "";
    }

    if( parent.back() == '/' )
    {
        if( child.front() == '/' )
        {
            return parent.substr( 0, parent.size() - 1 ) + child;
        }
        else
        {
            return parent + child;
        }
    }
    else if( child.front() == '/' )
    {
        return parent + child;
    }
    else
    {
        return parent + '/' + child;
    }
}


bool CaenTreeCreator::CompareExtension( const std::string& fileName,
                                        const std::string& extension ) const
{
    if( fileName.length() > extension.length() )
    {
        if( fileName.rfind( extension ) != (fileName.length() - extension.length()) )
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}


void CaenTreeCreator::GetListOfSamples( std::vector< std::string >& sampleNames,
                                        bool fullPath ) const
{
    sampleNames.clear();

    try
    {
        if( b_fs::exists( fPathToDataDir ) && b_fs::is_directory( fPathToDataDir ) )
        {
            b_fs::directory_iterator iter( fPathToDataDir );
            b_fs::directory_iterator end;

            while( iter != end )
            {
                if( b_fs::is_directory( iter->path() ) ) 
                {
                    if( fullPath )
                    {
                        sampleNames.push_back( iter->path().string() ); 
                    }
                    else
                    {
                        sampleNames.push_back( iter->path().filename().string() ); }
                }
                
                boost::system::error_code ec;
                iter.increment( ec );
                if( ec )
                {
                    std::cerr << "WARNING :: Error while accessing : " << iter->path().string() << " :: " << ec.message() << "\n";
                }
            }
        }
    }
    catch( std::system_error& e )
    {
        std::cerr << "Exception :: " << e.what();
    }
}


void CaenTreeCreator::GetListOfFiles( std::vector< std::string >& fileNames,
                                      bool fullPath,
                                      std::string pathToParentDir ) const
{
    fileNames.clear();
    if( pathToParentDir == "" ) { pathToParentDir = fPathToDataDir; }

    try
    {
        if( b_fs::exists( pathToParentDir ) && b_fs::is_directory( pathToParentDir ) )
        {
            b_fs::recursive_directory_iterator iter( pathToParentDir );
            b_fs::recursive_directory_iterator end;

            while( iter != end )
            {
                if( CompareExtension( (std::string)iter->path().string(), ".dat" ) )
                {
                    if( fullPath )
                    {
                        fileNames.push_back( iter->path().string() );
                    }
                    else
                    {
                        fileNames.push_back( iter->path().filename().string() );
                    }
                }
                
                boost::system::error_code ec;
                iter.increment( ec );
                if( ec )
                {
                    std::cerr << "ERROR :: Error while accessing : " << iter->path().string() << " :: " << ec.message() << "\n";
                }
            }
        }
    }
    catch( std::system_error& e )
    {
        std::cerr << "Exception :: " << e.what();
    }
}


void CaenTreeCreator::CreateTree( SAMPLE mode, const std::string& target )
{
    std::vector< std::string > samples;
    GetListOfSamples( samples, false );
    std::sort( samples.begin(), samples.end() );

    if( samples.empty() )
    {
        samples = { "" };
    }

    TFile* fileTree = new TFile( MergePaths( fPathToTreeFile, fTreeFileName ).c_str(), "RECREATE" );

    for( auto sample : samples )
    {
        if( (mode == SAMPLE::INCLUDE)  &&  (sample != target) )
        {
            continue;
        }
        else if( (mode == SAMPLE::EXCLUDE)  &&  (sample == target) )
        {
            continue;
        }

        std::cout << "INFO :: Processing of sample '" << sample << "' begins. Waiting ..." << std::endl;

        Double_t baseline;
        Double_t maxValue, maxValueTime;
        Double_t minValue, minValueTime;
        Double_t triggerTime;
        Double_t timeStep;
        Double_t integral;
        Double_t pkpk;
        std::string pathToBinFile;
        UInt_t  size;
        Int_t startPos;

        TTree tree( ("tree_" + sample).c_str(), ("tree_" + sample).c_str() );
            tree.Branch( "baseline", &baseline, "baseline/D" );
            tree.Branch( "maxValue", &maxValue, "maxValue/D" );
            tree.Branch( "maxValueTime", &maxValueTime, "maxValueTime/D" );
            tree.Branch( "minValue", &minValue, "minValue/D" );
            tree.Branch( "minValueTime", &minValueTime, "minValueTime/D" );
            tree.Branch( "triggerTime", &triggerTime, "triggerTime/D" );
            tree.Branch( "timeStep", &timeStep, "timeStep/D" );
            tree.Branch( "integral", &integral, "integral/D" );
            tree.Branch( "pkpk", &pkpk, "pkpk/D" );
            tree.Branch( "pathToBinFile", &pathToBinFile );
            tree.Branch( "size", &size, "size/i" );
            tree.Branch( "startPos", &startPos, "startPos/I" );
            
        std::vector< std::string > files;
        GetListOfFiles( files, true, MergePaths( fPathToDataDir, sample ) );

        for( auto file : files )
        {
            std::cout << "|\n";
            std::cout << "|---INFO :: file: " << file << "\n";

            caen::Parser parser( fBoard ); 
            parser.SetPathToFile( file );
            caen::Analyzer analyzerObject;
            analyzerObject.SetBaselineMethod( fBaselineMethod );
            analyzerObject.SetBaselineInterval( fBaselineInterval );
            analyzerObject.SetGate( fIntegralStart, fIntegralStop );
            caen::Event e;

            while( parser.ReadEvent( e ) )
            {
                analyzerObject.Analyze( e );

                baseline = analyzerObject.GetBaseline();
                maxValue = baseline - analyzerObject.GetMaxPoint().voltage;
                maxValueTime = analyzerObject.GetMaxPoint().time;
                minValue = baseline - analyzerObject.GetMinPoint().voltage;
                minValueTime = analyzerObject.GetMinPoint().time;
                triggerTime = 0.;
                timeStep = fBoard.GetSampleTime();
                integral = analyzerObject.GetIntegral();
                pkpk = analyzerObject.GetPkPk();
                pathToBinFile = file;
                size = e.GetSize();
                startPos = (Int_t)e.GetStartPosition();

                tree.Fill();
            }
        }
        tree.Write();

        std::cout << "|\n|-------OK!\n";
    }

    fileTree->Close();
    delete fileTree;
}
