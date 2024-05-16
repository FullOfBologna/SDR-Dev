# Basic CMake List for compiling HackRF c++ Program. 

project(HackRFDev CXX C)
cmake_minimum_required(VERSION 3.22)

# set(CMAKE_HACKRF_SOURCE_DIR "/home/fullofbolgna/dev_env/hackrf/host")

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_HACKRF_SOURCE_DIR}/cmake/Modules/")

# include(FindLIBHACKRF)

# find_package(LIBHACKRF REQUIRED)
# include_directories(${LIBHACKRF_INCLUDE_DIR})

SET(DEVICES_SRCS
	Devices/Devices.cpp
)	

SET(DEVICES_HDRS
	Devices/Devices.h
)


SET(DONGLE_SRCS
	Dongle/Dongle.cpp
	Dongle/HackRFDongle.cpp
)

SET(DONGLE_HDRS
	Dongle/Dongle.h
	Dongle/HackRFDongle.h

SET(SRC
	main.cpp
	Devices/Devices.cpp
)

SET(HDRS
	defines.h
)

add_executable(HackRFDev ${SRC} ${DEVICE_SRCS} ${DONGLE_SRCS} )
target_link_libraries(HackRFDev hackrf)



