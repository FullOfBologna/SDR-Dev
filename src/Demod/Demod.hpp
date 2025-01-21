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

    // StartRx() - Link the receiver to the inChannel output. Need to have the receiver on it's own thread, then have the data in this object or it's child perform the 
    //      processing. 
    virtual void StartRx();
    void InputChannelSet(std::shared_ptr<Channel>& channel);
    void OutputChannelSet(std::shared_ptr<Channel>& channel
protected:
    Demod(){};

    std::array<int16_t,MAXIMUM_BUF_LENGTH> m_rawBuf;
    std::array<int16_t,MAXIMUM_BUF_LENGTH> m_lpBuf;
    std::array<int16_t,MAXIMUM_BUF_LENGTH> m_result;

 //   void OutputTargetSet(std::unique_ptr<Output*> outputTarget);
    std::shared_ptr<Channel> mInChannel;
    std::shared_ptr<Channel> mOutChannel;

    size_t m_inBufSize;
    //Methods
    //
    //receiver will loop calling mInChannel
    virtual void receiver();
};

#endif
