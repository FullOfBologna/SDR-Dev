#include "BentPipeDemod.hpp"

void BentPipeDemod::receiver()
{
    while(!do_exit)
    {
        mInChannel->receive(m_rawBuf,m_inBufSize);

    }
    mChannel
}

void ThroughputStatsGet()
{

}
