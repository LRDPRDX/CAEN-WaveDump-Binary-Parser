#ifndef CAEN_BOARD_H
#define CAEN_BOARD_H

#include <string>


namespace caen
{
    class Board
    {
        public :
            enum MODEL 
                {
                    //Desktop series
                    DT5720,
                    DT5724,
                    DT5725,
                    DT5730,
                    DT5740, DT5740D,
                    DT5742,
                    DT5743,
                    DT5751,
                    DT5761,
                    //NIM series
                    N6720,
                    N6724,
                    N6725,
                    N6730,
                    N6740, N6740D,
                    N6742,
                    N6743,
                    N6751,
                    N6761,
                    //VME series
                    V1720,
                    V1724,
                    V1725,
                    V1730,
                    V1740, V1740D,
                    V1742,
                    V1743,
                    V1751,
                    V1761,
                    //VME64X series 
                    VX1720,
                    VX1724,
                    VX1725,
                    VX1730,
                    VX1740, VX1740D,
                    VX1742,
                    VX1743,
                    VX1751,
                    VX1761,
                };


        protected :
            unsigned resolution;//Resolution [bits]
            uint64_t sampleRate;//Sample rate [kHz]
            double FSR;//Full scale range [volts]
            
    
        public :
            Board( unsigned resolution, uint64_t sampleRate, double FSR ) :
                resolution( resolution ),
                sampleRate( sampleRate ),
                FSR( FSR )
            { };
    
            Board( MODEL model );
    
            unsigned GetResolution() const { return resolution; }
            uint64_t GetSampleRate() const { return sampleRate; }
            double   GetSampleTime() const { return 1e6 / sampleRate; }//Time between neighboring points [us]
            double   GetFSR()        const { return FSR; }
            double   GetLSB()        const { return FSR / ( (1 << resolution) - 1 ); }//Least significant bit [volts] 
    };
}
#endif
