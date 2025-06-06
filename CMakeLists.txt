cmake_minimum_required(VERSION 3.20)
project(test_fetch_content)

# Just to suppress warnings
if (${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.24")
    cmake_policy(SET CMP0135 NEW)
endif ()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(fetch_boost)

#
# Fetch Boost using the fetch_boost() function defined in fetch_boost.cmake
#
# User options to specify Boost source or URL
set(BOOST_SOURCE_DIR CACHE STRING "Path to Boost libraries directory already uncompressed. Must be a version that supports CMake.")
set(BOOST_FETCH_URL CACHE STRING "URL or file path to an archived Boost source. Must be a version that supports CMake.")

# List of boost components this project depends on
set(BOOST_COMPS container json)

if (BOOST_SOURCE_DIR)
  fetch_boost(SOURCE ${BOOST_SOURCE_DIR} COMPONENTS ${BOOST_COMPS} VERBOSE)
elseif (BOOST_FETCH_URL)
  fetch_boost(URL ${BOOST_FETCH_URL} COMPONENTS ${BOOST_COMPS} VERBOSE)
else ()
  # Use default Boost version if not specified by the user
  fetch_boost(URL "https://github.com/boostorg/boost/releases/download/boost-1.88.0/boost-1.88.0-cmake.tar.gz"
              COMPONENTS ${BOOST_COMPS} VERBOSE)
endif ()

message(STATUS "BOOST_LIBS: ${BOOST_LIBS}")

#
# Build an example
#
set(CMAKE_CXX_STANDARD 20)
add_executable(example example.cpp)
# BOOST_LIBS is set by fetch_boost()
target_link_libraries(example PUBLIC ${BOOST_LIBS})
