# Scratchpad Task Tracking

### TODO: 05-18-2024

Current goals: Configure HackRF to a given frequency, samplerate, and gain, and output the buffer to a .wav file. 
No demod will be performed. Demod will be a bentpipe only to get data to the output file. 

- [ ] Hack RF Demod Target accepts child intance of Demod Abstract Class
    - [x] Implment DemodTargetSet method
    - [ ] Implement Read/Write Lock Safety
- [ ] Demod Target has route to Output Abstract class target
- [ ] Instantiate C++ threads
    - [ ] Output Object thread
    - [ ] Demod Object thread 
    - [ ] HackRF Object thread
- [ ] Start the receiving thread
- [ ] Verify bytes have been written to the demod tartget, then passed to the output thread
- [ ] Implement the WAV File generation script
- [ ] 

- [ ] Compile
    
    - [ ] Refactor CMake with new directory structure and added files/classes
    - [ ] Refactor CMake for reading cmake files in individual sections of code. 

### ChatGPT Suggestion for CMake

```To call CMakeLists.txt files within subfolders, you can use the add_subdirectory() command in your top-level CMakeLists.txt file. Here's an example directory structure:

objectivec

project_folder/
│
├── CMakeLists.txt
├── src/
│   ├── CMakeLists.txt
│   ├── file1.cpp
│   └── file2.cpp
└── include/
    ├── header1.hpp
    └── header2.hpp

In your top-level CMakeLists.txt, you would add the subdirectories using add_subdirectory():

cmake

cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Include subdirectories
add_subdirectory(src)

Then, in the src/CMakeLists.txt, you can specify the details of your source files:

cmake

# Define the target
add_executable(MyExecutable file1.cpp file2.cpp)

# Link any libraries if needed
target_link_libraries(MyExecutable MyLibrary)

# Include directories if needed
target_include_directories(MyExecutable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

This structure assumes that the headers you want to include are in the include directory at the top level. Adjust the paths according to your project's actual structure.

Remember, CMake traverses the directory tree from the location where you invoke the cmake command. So if you are invoking CMake from a different location, adjust the paths accordingly.
```



