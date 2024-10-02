#include "Demod.hpp"

Demod::~Demod(){}

void InputChannelSet(std::shared_ptr<Channel>& channel)
{
    mInChannel = channel;
}

void OutputChannelSet(std::shared_ptr<Channel>& channel)
{
    mOutChannel = channel;
}


