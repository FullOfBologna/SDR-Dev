#include "Devices/Devices.hpp"
#include "Dongle/HackRFDongle.h"

int main(void)
{
	Devices FoundDevices = Devices();

	/*
		Need to initialize concurrent threads for handling the calls from the
	*/


	FoundDevices.libInitialize();

	int result = HACKRF_SUCCESS;
	FoundDevices.resultCheck(result);

	if(result != HACKRF_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	FoundDevices.DeviceListRead();


	FoundDevices.DeviceListReport();


	/*
		Read Device List

		Report devices found. 

		Ask for input for what device to Open
	*/

	int devSelect = 0;

	std::cin << "Select Device:" << devSelect << "\n";

	std::unique_ptr<hackrf_device> devToOpen = nullptr;

	FoundDevices.DeviceOpen(devSelect, devToOpen);

	//After transfer of opened device, free the device list. 
	FoundDevices.DeviceListFree();


	HackRFDongle HackRF(devToOpen);
	//Initialize Demod Object
	// HackRFDongle.DemodTargetSet(Demod);

	uint32_t tuneFrequencyHz = 2100 * MHZ_TO_HZ;
	uint32_t sampleRate = 20 * MHZ_TO_HZ;


	HackRF.FrequencySet(tuneFrequencyHz);
	HackRF.SampleRateSet(sampleRate);
	HackRF.VGAGainSet(32);
	HackRF.LNAGainSet(14);

	//Move HackRF to own thread. 
	HackRF.StartRx();

	// Catch Signal and call hackRFStopRx();

	// hackrf_exit();

	return EXIT_SUCCESS;

}
