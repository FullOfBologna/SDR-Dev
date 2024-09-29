#ifndef DEMOD_H_
#define DEMOD_H_

#include <cstdint>
#include "defines.h"
#include "Output/Output.h"
#include "util/Channel.hpp"

class Demod
{

public:
    virtual ~Demod();

    void StartRx();
protected:
    Demod(){};

    int16_t lpBuf[MAXIMUM_BUF_LENGTH];
    int16_t result[MAXIMUM_BUF_LENGTH];

    std::array<int16_t,MAXIMUM_BUF_LENGTH> m_lpBuf;
    std::array<int16_t,MAXIMUM_BUF_LENGTH> m_result;

 //   void OutputTargetSet(std::unique_ptr<Output*> outputTarget);
    std::shared_ptr<Channel> mInChannel;
    std::shared_ptr<Channel> mOutChannel;

    //Methods
    //
    //receiver will loop calling mInChannel
    virtual void receiver();
};

#endif
