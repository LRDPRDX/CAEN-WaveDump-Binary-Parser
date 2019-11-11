#ifndef CAEN_ADC_H
#define CAEN_ADC_H

/*
//Desktop models
#if defined(DT5720)
    #include "models/DT5720.h"
#elif defined(DT5724)
    #include "models/DT5724.h"
#elif defined(DT5725)
    #include "models/DT5725.h"
#elif defined(DT5730)
    #include "models/DT5730.h"
#elif defined(DT5740) || defined(DT5740D)
    #include "models/DT5740.h"
#elif defined(DT5761)
    #include "models/DT5761.h"
//NIM models
#elif defined(N6720)
    #include "models/N6720.h"
#elif defined(N6724)
    #include "models/N6724.h"
#elif defined(N6725)
    #include "models/N6725.h"
#elif defined(N6730)
    #include "models/N6730.h"
#elif defined(N6740) || defined(N6740D)
    #include "models/N6740.h"
#elif defined(N6742)
    #include "models/N6742.h"
#elif defined(N6743)
    #include "models/N6743.h"
#elif defined(N6751)
    #include "models/N6751.h"
#elif defined(N6761)
    #include "models/N6761.h"
//VME models
#else
    #error Please provide digitizer model
#endif
*/

#include "CaenWD.h"
#include "CaenBoard.h"


namespace caen
{
    inline double RealVoltage( SAMPLE_SIZE adcChannels, const Board& board )
    {
        //Returns real voltage in mV
        return 1000. * (double)adcChannels * board.GetLSB();
    }


    inline double RealTime( uint32_t sampleNumber, const Board& board )
    {
        //Returns real time in microsecs
        return (double)sampleNumber * board.GetSampleTime();
    }
}
#endif
