#ifndef CAEN_WD_H
#define CAEN_WD_H

#include <cinttypes>


namespace caen
{
    struct Header
    {
        uint32_t        EVENT_SIZE;//header + data 
        uint32_t        BOARD_ID;//identificaton number of a digitizer
        uint32_t        PATTERN;//meaningful only for VME boards
        uint32_t        CHANNEL;//channel number
        uint32_t        EVENT_COUNTER;//count number of an event
        uint32_t        TRIGGER_TIME_TAG;//absolute trigger time
    };

    typedef uint16_t    SAMPLE_SIZE;
}
#endif
