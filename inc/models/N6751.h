#ifndef N6751_H
#define N6751_H


namespace caen
{
    const double     SAMPLE_TIME = 0.3125;//ns
    const unsigned   N_BITS      = 12;//resolution
    const double     FSR         = 2.0;//V

    const double     LSB         = FSR / ( (1 << N_BITS) - 1 );//V
}
#endif
