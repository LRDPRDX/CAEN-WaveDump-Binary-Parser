{
    gSystem->AddLinkedLibs( "-lboost_filesystem -lboost_system" );
    gSystem->AddLinkedLibs( "-lcaenparse" );
    gSystem->AddIncludePath( "-I../inc");
    gROOT->LoadMacro( "../src/ROOT/CaenTreeCreator/CaenTreeCreator.cpp+" );
    //gROOT->LoadMacro( "../src/ROOT/Drawer/Drawer.cpp+" );
}
