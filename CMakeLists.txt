# CMake 3.19 is the earliest tested version that works on both Windows and Linux
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
project(CMakeImGuiOpenGL VERSION 1.0.0 LANGUAGES CXX)

# ########################################################################################
# User variables
set(VENDOR_PATH "${PROJECT_SOURCE_DIR}/vendor")

# message("VENDOR_PATH = ${VENDOR_PATH}")

# ########################################################################################
# # User build options
# The preferred method for setting these options is to use command line flags when
# invoking cmake. See the README.md for details.

# ########################################################################################
# # Global flags
# Use C++11 throughout
if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED True)
endif()

# ########################################################################################
# Logging is performed using the spdlog library for fast C++ logging.
# FetchContent_Declare(
# spdlog
# GIT_REPOSITORY https://github.com/gabime/spdlog
# GIT_TAG eb3220622e73a4889eee355ffa37972b3cac3df5
# )
# set(spdlog_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest spdlog)

# ########################################################################################
# Build flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG=1")

# ########################################################################################
add_subdirectory(myApp) # Include App framework
add_subdirectory(anotherApp) # Include App framework
add_subdirectory(vendor) # include third party libraries
