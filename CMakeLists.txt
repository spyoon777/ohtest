# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.18)

project (ohtest LANGUAGES C CXX VERSION 0.1.0.0)

set (CMAKE_C_STANDARD 11)
set (CMAKE_C_STANDARD_REQUIRED ON)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W1 -O2 /bigobj")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W1 -O2 /bigobj")

set (CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/build/install")
set (CMAKE_DEBUG_POSTFIX "d")

set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}/cmake_modules")

# EXT Lib
message ("############################################################")

set (OPENHOLO_ROOT_DIR "${CMAKE_SOURCE_DIR}/thirdparty/OpenHolo_v2.0")
message ("openholo dir: ${OPENHOLO_ROOT_DIR}")

#set (OPENCV3412_ROOT_DIR "${CMAKE_SOURCE_DIR}/thirdparty/opencv-3.4.12")
#message ("opencv-3.4.12 dir: ${OPENCV3412_ROOT_DIR}")

message ("############################################################")
#

find_package (CUDAToolkit REQUIRED)
if (NOT CUDAToolkit_FOUND)
    message (FATAL_ERROR "CUDA Toolkit not found")
else ()
    message ("CUDA Toolkit dir: ${CUDAToolkit_LIBRARY_ROOT}")
endif ()

# Include sub-projects.
add_subdirectory ("oht")
