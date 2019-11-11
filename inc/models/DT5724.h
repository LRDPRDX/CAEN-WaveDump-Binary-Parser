#ifndef DT5724_H
#define DT5724_H


namespace caen
{
    const double     SAMPLE_TIME = 10.0;//ns
    const unsigned   N_BITS      = 14;//
    const double     FSR         = 2.0;//V

    const double     LSB         = FSR / ( (1 << N_BITS) - 1 );//V
}
#endif
