#include "Devices/Devices.hpp"
#include "Dongle/HackRFDongle.h"
#include <signal>
#include <thread>


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
    const std::string OUTPUT_DIR = "/home/fullofbologna/dev_env/CppDev/HackRF_Dev";

    Demod BentPipeDemod();
    WavOutput WavFileOutput(OUTPUT_FILE);

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


    /*
     * Initialize Threads for Rx Receiving. 
     *  - HackRF Will run on it's own thread, listening for a callback from the Rx Device
     *  - Demod instance will wait for signal from Rx Receive that it is ready to pass in data. 
     *  - Output instane will wait for signal from Demod that it is ready to receive data to write\
     *      to file, or output via audio. 
     */

    bool outputReady(false);
    bool demodReady(false);
    std::mutex outputMutex;
    std::mutex demodMutex;

    std::condition_variable outputConditionVar;
    std::condition_variable demodConditionVar;
    std::condition_variable hackrfConditionVar;

    std::thread outputThread(WaveFileOutput);
    std::thread demodThread(BentPipeDemod);
    std::thread hackRfThread(HackRF);

    WavFileOutput.ConditionVariableSet(outputConditionVar);
    BentPipeDemod.ConditionVariableSet(demodConditionVar);
    HackRF.ConditionVariableSet(hackrfConditionVar);


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
