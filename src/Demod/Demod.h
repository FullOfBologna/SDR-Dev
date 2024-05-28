#ifndef DEMOD_H_
#define DEMOD_H_

#include <cstdint>
#include "defines.h"
#include "Output/Output.h"

class Demod
{

public:
    virtual ~Demod();


protected:
    Demod(){};

    int16_t lpBuf[MAXIMUM_BUF_LENGTH];
    int16_t result[MAXIMUM_BUF_LENGTH];

    std::array<int16_t,MAXIMUM_BUF_LENGTH> m_lpBuf;
    std::array<int16_t,MAXIMUM_BUF_LENGTH> m_result;

void OutputTargetSet(std::unique_ptr<Output*> outputTarget);
};

#endif
