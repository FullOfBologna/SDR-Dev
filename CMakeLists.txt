# Basic CMake List for compiling HackRF c++ Program. 

project(HackRFDev CXX C)
cmake_minimum_required(VERSION 3.22)

set(SUBDIRS
    src
    src/Demod
    src/Devices
    src/Dongle
    src/Output
    src/util
)

foreach(sub_dir ${SUBDIRS}
        add_subdirectory(${sub_dir})
endforeach()

#Include src subdirectories
#add_subdirectory(src)
#add_subdirectory(src/Demod)
#add_subdirectory(src/Devices)
#add_subdirectory(src/Dongle)
#add_subdirectory(src/Output)
#add_subdirectory(src/util)

#Get this working, before shifting it to 
target_sources(my_project PUBLIC
    ${DEMOD_SRC}
    ${DEVICES_SRC}
    ${DONGLE_SRC}
    ${OUTPUT_SRC}
    ${UTIL_SRC}
    ${SRC}
)

foreach(sub_dir ${SUBDIRS}
    target_include_directories(PUBLIC ${SUBDIRS})
endforeach()


# set(CMAKE_HACKRF_SOURCE_DIR "/home/fullofbolgna/dev_env/hackrf/host")

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_HACKRF_SOURCE_DIR}/cmake/Modules/")

# include(FindLIBHACKRF)

# find_package(LIBHACKRF REQUIRED)
# include_directories(${LIBHACKRF_INCLUDE_DIR})

#[[
SET(DEVICES_SRCS
	src/Devices/Devices.cpp
)	

SET(DEVICES_HDRS
	src/Devices/Devices.h
)

SET(DONGLE_SRCS
	src/Dongle/Dongle.cpp
	src/Dongle/HackRFDongle.cpp
)

SET(DONGLE_HDRS
	src/Dongle/Dongle.h
	src/Dongle/HackRFDongle.h
)

SET(OUTPUT_SRCS
    src/Output/Output.cpp
    src/Output/WavOutput.cpp
)

SET(OUTPUT_HDRS
    src/Output/Output.hpp
    src/Output/WavOutput.hpp
)

SET(DEMOD_SRCS
    src/Demod/Demod.cpp
    src/Demod/BentPipeDemod.cpp
)

SET(DEMOD_HDRS
    src/Demod/Demod.hpp
    src/Demod/BentPipeDemod.hpp
)
SET(SRC
	src/main.cpp
)
SET(HDRS
	src/defines.hpp
    src/util/Channel.hpp
)
]]


add_executable(HackRFDev ${SRC} ${DEVICE_SRCS} ${DONGLE_SRCS} ${DEMOD_SRCS} ${OUTPUT_SRCS})
target_link_libraries(HackRFDev hackrf)



