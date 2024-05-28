#include "Dongle.h"
#include "Demod/Demod.h"

#include <iostream>
#include <memory>


extern "C" {
	#include <libhackrf/hackrf.h>
}


struct devInfo
{
	uint8_t boardId;
	uint8_t boardRev;
	uint32_t supportedPlatform;
	uint16_t usbVersion;
	char version[255 + 1];
};

class HackRFDongle : public Dongle
{

private: 

std::unique_ptr<hackrf_device> mDevice;
std::unique_ptr<Demod> mDemodTarget;
std::unique_ptr<devInfo> mDevInfo;

uint32_t mVGAGain;
uint32_t mLNAGain;

static const char* mSerialNumber;

static std::array<uint8_t,MAXIMUM_BUF_LENGTH> mSampBuffer;

int dongleInit();
void devInfoSet(std::unique_ptr<devInfo> &devInfo);
/*
 Explicit Calls to lock demod target are now irrelevant with the Implementation of a Channel object to
 act as a traffic officer. 
int demodTargetLock();
int demodTargetFree();
*/
int bufferTransferToDemodTarget();
int sdrCallback(hackrf_transfer* transfer);

public: 

HackRFDongle(std::unique_ptr<hackrf_device>& device):mDevice(std::move(device)){};
~HackRFDongle(){};

// void hackRfConfigure();
int FrequencySet(uint32_t frequency);
int SampleRateSet(uint32_t sampleRate);
int VGAGainSet(uint32_t VGAgain);
int LNAGainSet(uint32_t LNAGain);

int DemodTargetSet(std::unique_ptr<Demod>&demodTarget);

void StartRx();
void StopRx();
};
