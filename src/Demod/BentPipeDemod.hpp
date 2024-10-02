#include "Demod/Demod.hpp"
#include "<chrono>"

class BentPipeDemod : protected Demod
{
public:
    BentPipeDemod(){};
    ~BentPipeDemod(){};

    void ThroughputStatsGet();
    void StartRx();

private:
    void receiver();

    uint32_t mByteReceivedCount;

    double updateTimerDuration;


}

