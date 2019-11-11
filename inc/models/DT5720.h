#ifndef DT5720_H
#define DT5720_H


namespace caen
{
    const double     SAMPLE_TIME = 4.0;//ns
    const unsigned   N_BITS      = 12;//
    const double     FSR         = 2.0;//V

    const double     LSB         = FSR / ( (1 << N_BITS) - 1 );//V
}
#endif
