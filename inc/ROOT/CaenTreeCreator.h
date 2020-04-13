#ifndef CAEN_TREE_CREATOR_H
#define CAEN_TREE_CREATOR_H

#include <boost/filesystem.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include "CaenAnalyzer.h"

#include "TROOT.h"

namespace b_fs = boost::filesystem; 


class CaenTreeCreator
{
    protected :
        caen::Board                 fBoard;
        std::string                 fPathToDataDir;
        std::string                 fPathToTreeFile;
        std::string                 fTreeFileName;

        Double_t                    fBaselineInterval; 
        Double_t                    fIntegralStart; 
        Double_t                    fIntegralStop; 

        caen::Analyzer::BASELINE    fBaselineMethod;

        //Auxiliary methods
        std::string     MergePaths( const std::string& parent, const std::string& child ) const;
        bool            CompareExtension( const std::string& fileName,
                                          const std::string& extension ) const;


    public :
        CaenTreeCreator( caen::Board board,
                         const std::string& pathToDataDir,
                         const std::string& pathToTreeFile,
                         const std::string& treeFileName ) :
            fBoard( board ),
            fPathToDataDir( pathToDataDir ),
            fPathToTreeFile( pathToTreeFile ),
            fTreeFileName( treeFileName + ".root" ),
            fBaselineInterval( 0. ),
            fIntegralStart( 0. ),
            fIntegralStop( 0. ),
            fBaselineMethod( caen::Analyzer::AVERAGE )
        {
        }

        void GetListOfSamples( std::vector< std::string >& sampleNames, bool fullPath ) const;
        void GetListOfFiles( std::vector< std::string >& fileNames,
                             bool fullPath,
                             std::string pathToParentDir ) const;

        void SetPathToDataDir( const std::string& pathToDataDir )
        {
            fPathToDataDir = pathToDataDir;
        }
        void SetPathToTreeFile( const std::string& pathToTreeFile )
        {
            fPathToTreeFile = pathToTreeFile;
        }
        void SetTreeFileName( const std::string& treeFileName )
        {
            fTreeFileName = treeFileName + ".root";
        } 

        void SetIntervals( Double_t baselineInterval,
                           Double_t integralStart, Double_t  integralStop )
        {
            fBaselineInterval = baselineInterval;
            fIntegralStart = integralStart;
            fIntegralStop = integralStop;
        }

        void SetBaselineMethod( caen::Analyzer::BASELINE method )
        {
            fBaselineMethod = method;
        }

        std::string GetPathToDataDir() const { return fPathToDataDir; }
        std::string GetPathToTreeFile() const { return fPathToTreeFile; }
        std::string GetTreeFileName() const { return fTreeFileName; }

        enum SAMPLE { ALL, INCLUDE, EXCLUDE };
        void CreateTree( SAMPLE mode = ALL, const std::string& target = "" );
};
#endif
