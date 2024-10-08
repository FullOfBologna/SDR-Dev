#ifndef DONGLE_H_
#define DONGLE_H_

#include <inttypes.h>
#include "defines.h"

class Dongle
{
protected:
    uint32_t mFrequency;
    uint32_t mSampleRate;
    uint32_t mBufLen;

    int mPpmError;

public: 
    Dongle(){};
    ~Dongle(){};

    virtual int FrequencySet(uint32_t frequency) = 0;
    virtual int SampleRateSet(uint32_t sampleRate) = 0;

    //Let specific Dongles implement their callbacks. 
    // virtual int dongleInit() = 0;

};

#endif
