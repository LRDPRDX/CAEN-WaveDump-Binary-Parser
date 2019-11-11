#include "CaenBoard.h"


namespace caen
{
    Board::Board( MODEL model )
    {
        switch( model )
        {
            //Desktop series
            case DT5720     : resolution = 12; sampleRate = 250000000; FSR = 2.0; return; 
            case DT5724     : resolution = 14; sampleRate = 100000000; FSR = 2.0; return; 
            case DT5725     : resolution = 14; sampleRate = 250000000; FSR = 2.0; return; 
            case DT5730     : resolution = 14; sampleRate = 500000000; FSR = 2.0; return; 
            case DT5740     : resolution = 12; sampleRate = 62500000; FSR = 2.0; return; 
            case DT5740D    : resolution = 12; sampleRate = 62500000; FSR = 2.0; return; 
            case DT5742     : resolution = 12; sampleRate = 5000000000; FSR = 2.0; return; 
            case DT5743     : resolution = 12; sampleRate = 3200000000; FSR = 2.0; return; 
            case DT5751     : resolution = 10; sampleRate = 2000000000; FSR = 2.0; return; 
            case DT5761     : resolution = 10; sampleRate = 4000000000; FSR = 2.0; return; 
            //NIM series
            case N6720      : resolution = 12; sampleRate = 250000000; FSR = 2.0; return;
            case N6724      : resolution = 14; sampleRate = 100000000; FSR = 2.0; return; 
            case N6725      : resolution = 14; sampleRate = 250000000; FSR = 2.0; return; 
            case N6730      : resolution = 14; sampleRate = 500000000; FSR = 2.0; return;
            case N6740      : resolution = 12; sampleRate = 62500000; FSR = 2.0; return;
            case N6740D     : resolution = 12; sampleRate = 62500000; FSR = 2.0; return;
            case N6742      : resolution = 12; sampleRate = 5000000000; FSR = 2.0; return; 
            case N6743      : resolution = 12; sampleRate = 3200000000; FSR = 2.0; return;
            case N6751      : resolution = 10; sampleRate = 2000000000; FSR = 2.0; return;
            case N6761      : resolution = 10; sampleRate = 4000000000; FSR = 2.0; return;
            //VME series
            case V1720      : resolution = 12; sampleRate = 250000000; FSR = 2.0; return;
            case V1724      : resolution = 14; sampleRate = 100000000; FSR = 2.0; return;
            case V1725      : resolution = 14; sampleRate = 250000000; FSR = 2.0; return;
            case V1730      : resolution = 14; sampleRate = 500000000; FSR = 2.0; return;
            case V1740      : resolution = 12; sampleRate = 62500000; FSR = 2.0; return;
            case V1740D     : resolution = 12; sampleRate = 62500000; FSR = 2.0; return;
            case V1742      : resolution = 12; sampleRate = 5000000000; FSR = 2.0; return;
            case V1743      : resolution = 12; sampleRate = 3200000000; FSR = 2.0; return;
            case V1751      : resolution = 10; sampleRate = 2000000000; FSR = 2.0; return;
            case V1761      : resolution = 10; sampleRate = 4000000000; FSR = 2.0; return;
            //VME64X series
            case VX1720      : resolution = 12; sampleRate = 250000000; FSR = 2.0; return;
            case VX1724      : resolution = 14; sampleRate = 100000000; FSR = 2.0; return;
            case VX1725      : resolution = 14; sampleRate = 250000000; FSR = 2.0; return;
            case VX1730      : resolution = 14; sampleRate = 500000000; FSR = 2.0; return;
            case VX1740      : resolution = 12; sampleRate = 62500000; FSR = 2.0; return;
            case VX1740D     : resolution = 12; sampleRate = 62500000; FSR = 2.0; return;
            case VX1742      : resolution = 12; sampleRate = 5000000000; FSR = 2.0; return;
            case VX1743      : resolution = 12; sampleRate = 3200000000; FSR = 2.0; return;
            case VX1751      : resolution = 10; sampleRate = 2000000000; FSR = 2.0; return;
            case VX1761      : resolution = 10; sampleRate = 4000000000; FSR = 2.0; return;
        }     
    }
}
