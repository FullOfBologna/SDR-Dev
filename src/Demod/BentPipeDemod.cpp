#include "BentPipeDemod.hpp"


void BentPipeDemod::receiver()
{
    while(!do_exit)
    {
        mInChannel->receive(m_rawBuf,m_inBufSize);
    }
    mChannel
}

void BentPipeDemod::ThroughputStatsGet()
{

}

//Brainstorming need to loop through and call receiver, but allow it to return for other processing.
//  Possibly need to look at coroutines, or other methods of managing. Need to call the 
//  channel->receive copy the buffer contents then proceed, which right now as implemented
//  means we need to have an outer loop handling the call into the receiver. 
//
//  As it currently stands, without a callback implementation, we will be dependent on the timing
//  of the Demod processing thread to both aquire the buffer data, and perform any processing/
//  transmitting to the output message queue, then call the receiver again. 
//
//  This is highlighting the need for asyncronous handling of the data. But for right now, it's
//  important to establish a working MVP prior to refactoring. Hopefully we can establish a baseline
//  test that will highlight:
//      - Packet Loss
//      - Throughput Data Rate
//      - Processing Time available

void processingLoop()
{
}
