#include "Devices/Devices.hpp"
#include "Dongle/HackRFDongle.h"
#include <signal>

void sigint_callback_handler(int signum)
{
    interrupted = true;
    std::cerr << "Caught Signal " << signum << '\n';
    do_exit = true;
}

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
    //
    Demod BentPipeDemod();
	HackRFDongle.DemodTargetSet(BentPipeDemod);

	uint32_t tuneFrequencyHz = 2100 * MHZ_TO_HZ;
	uint32_t sampleRate = 20 * MHZ_TO_HZ;

	HackRF.FrequencySet(tuneFrequencyHz);
	HackRF.SampleRateSet(sampleRate);
	HackRF.VGAGainSet(32);
	HackRF.LNAGainSet(14);

	//Move HackRF to own thread. 
	HackRF.StartRx();

    //OutputFile.setFileSize();

	// Catch Signal and call hackRFStopRx();
	signal(SIGINT, &sigint_callback_handler);
    signal(SIGILL, &sigint_callback_handler);
	signal(SIGFPE, &sigint_callback_handler);
	signal(SIGSEGV, &sigint_callback_handler);
    signal(SIGTERM, &sigint_callback_handler);
	signal(SIGABRT, &sigint_callback_handler);

    while(!do_exit)
    {
        
    }
    //Clean up threads. 
        //Stop RX
        //Close Output File
        //Teardown Threads
    HackRF.StopRx();

	return EXIT_SUCCESS;
}
