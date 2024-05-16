#include "Devices.hpp"


Devices::Devices():
        m_deviceList{new hackrf_device_list_t}
{

}

Devices::~Devices()
{

} 

void Devices::libInitialize()
{
	m_result = hackrf_init();


	if( m_result != HACKRF_SUCCESS)
	{
		std::cout << "ERROR: hackrf_init() failed: " << hackrf_error_name((hackrf_error)m_result) << '\n';
	}

	std::cout << "INFO: libhackrf version: " << hackrf_library_release() << " (" << hackrf_library_version() << ")\n";

}

void Devices::DeviceListRead()
{
	hackrf_device_list_t *devList;
	devList = hackrf_device_list();

	m_deviceList = std::unique_ptr<hackrf_device_list_t>(devList);

}


void Devices::DeviceListFree()
{
	hackrf_device_list_free(m_deviceList.get());
}

int Devices::DeviceListReport()
{
	if(m_deviceList->devicecount < 1)
	{
		std::cout << "ERROR: No Devices boards found.\n";
		return EXIT_FAILURE;	
	}


	hackrf_device *device;
	const size_t devCount = m_deviceList->devicecount;
	std::vector<devInfo> devInfoList;

	if(devCount == 1)
	{
		std::cout << "Found " << devCount << " HackRF device on USB\n";
	}
	else
	{
		std::cout << "Found " << devCount << " HackRF devices on USB\n";
	}

	for(int devIndex = 0; devIndex < m_deviceList->devicecount; devIndex++)
	{
		devInfo devInfo;

		if(devIndex == 0)
		{
			std::cout << "\n";
		}

		if(m_deviceList->serial_numbers[devIndex])
		{
			std::cout << "Serial number: " << m_deviceList->serial_numbers[devIndex] << '\n';
		}

		device = nullptr;

		m_result = hackrf_device_list_open(m_deviceList.get(),devIndex,&device);

		if( m_result != HACKRF_SUCCESS)
		{
			std::cout << "ERROR: hackrf_open() failed: " << hackrf_error_name((hackrf_error)m_result) << '\n';
			return EXIT_FAILURE;
		}

		m_result = hackrf_board_id_read(device, &devInfo.boardId);

		if( m_result != HACKRF_SUCCESS)
		{
			std::cout << "ERROR: hackrf_board_id_read() failed: " << hackrf_error_name((hackrf_error)m_result) << '\n';
			return EXIT_FAILURE;
		}

		m_result = hackrf_version_string_read(device, &devInfo.version[0],255);

		if( m_result != HACKRF_SUCCESS)
		{
			std::cout << "ERROR: hackrf_version_string_read() failed: " << hackrf_error_name((hackrf_error)m_result) << '\n';
			return EXIT_FAILURE;
		}

		m_result = hackrf_usb_api_version_read(device, &devInfo.usbVersion);

		if( m_result != HACKRF_SUCCESS)
		{
			std::cout << "ERROR: hackrf_usb_api_version_read() failed: " << hackrf_error_name((hackrf_error)m_result) << '\n';
			return EXIT_FAILURE;
		}

		/*
		
			FILL IN WITH REST OF BOARD INFO
		
		*/

		//Add +0 to print value and not ASCII
		std::cout << "Board ID Number: " << std::hex << devInfo.boardId+0 << std::dec << " (" << hackrf_board_id_name((hackrf_board_id)devInfo.boardId) << ")\n";
		std::cout << "Firmware Version: " << devInfo.version <<" (API:" << ((devInfo.usbVersion > 8) & 0xFF) << "." << (devInfo.usbVersion & 0xFF) << ")\n";
		
		// Close Device
		m_result = hackrf_close(device);
		if( m_result != HACKRF_SUCCESS)
		{
			std::cout << "ERROR: hackrf_close() failed: " << hackrf_error_name((hackrf_error)m_result) << '\n';
			return EXIT_FAILURE;
		}	
	}

	return EXIT_SUCCESS;
}

int Devices::DeviceOpen(int devSelect, std::unique_ptr<hackrf_device>& devToOpen)
{
	int result = HACKRF_SUCCESS;

	if(m_deviceList == nullptr)
	{
		result = HACKRF_ERROR_OTHER;
		std::cout << "ERROR: m_deviceList is NULL. Perhaps it is uninitialized or ownership has already been transferred.\n";
	}
	else
	{
		hackrf_device* device = nullptr;

		result = hackrf_device_list_open(m_deviceList.get(), devSelect, &device);

		if(result != HACKRF_SUCCESS)
		{
			std::cout << "ERROR: hackrf_open() failed: " << hackrf_error_name((hackrf_error)m_result) << '\n';
			result = EXIT_FAILURE;
		}		
		else
		{
			std::unique_ptr<hackrf_device> tempUniquePtr(device);
			devToOpen = std::move(tempUniquePtr);
		}
	}
	return result;

}

void Devices::resultCheck(int& result)
{
	result = m_result;
}