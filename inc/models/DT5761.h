#ifndef DT5761_H
#define DT5761_H


namespace caen
{
    const double     SAMPLE_TIME = 0.25;//ns
    const unsigned   N_BITS      = 10;//
    const double     FSR         = 2.0;//V

    const double     LSB         = FSR / ( (1 << N_BITS) - 1 );//V
}
#endif
