#ifndef DEVICES_H_
#define DEVICES_H_

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <cstdint>
#include <iostream>
#include <array>
#include <vector>


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

class Devices
{
private:	
	/* TODO - Need to add support for rtlsdr device list reading and other possible 
		sdr devices. 
	*/
	
	std::unique_ptr<hackrf_device_list_t> m_deviceList;

	read_partid_serialno_t read_partid_serialno;
	
	int m_result;

public:

	// ctor
	Devices();

	//dtor
	~Devices();

	void libInitialize();
	
	//Hack Rf Device List
	void DeviceListRead();
	int DeviceListReport();

	int DeviceOpen(int devSelect, std::unique_ptr<hackrf_device>& devToOpen);
	
	void DeviceListFree();

	void resultCheck(int& result);
};


#endif