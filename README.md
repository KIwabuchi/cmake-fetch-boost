# Fetch Boost

This CMake project shows how to fetch Boost C++ Libraries using CMake's FetchContent module.

## Key Components

- CMake module to fetch Boost C++ Libraries
  - Main contribution of this project
  - Path: `./cmake/fetch_boost.cmake`
- Main CMake script
  - Show how to use `cmake/fetch_boost.cmake` in your CMake script.
  - Path: `./cmake/fetch_boost.cmake`

This CMake script does not look for already installed Boost libraries
(using `find_package()`) to reduce the complexity of the script.

## Build

The CMake script has tree patterns to fetch Boost C++ Libraries.

```shell
mkdir build
cd build

# Use the default FETCH URL (download from GitHub)
cmake ../
make

# Use a custom FETCH URL
# BOOST_FETCH_URL can be set to a local directory or a URL.
# The Boost source must be an archived file and supports CMake.
cmake ../ -DBOOST_FETCH_URL=https://github.com/boostorg/boost/releases/download/boost-1.88.0/boost-1.88.0-cmake.tar.gz
make

# Use an already uncompressed CMake supported Boost.
# This mode copies only the files needed to all the Boost components this project depends on.
wget https://github.com/boostorg/boost/releases/download/boost-1.88.0/boost-1.88.0-cmake.tar.gz
tar xvf boost_1_88_0.tar.gz
cmake ../ -DBOOST_SOURCE_DIR=boost_1_88_0
make

```

### VERBOSE Message

Run CMake with `--log-level=VERBOSE` to show verbose messages.

The `fetch_boost` module supports the [message context](https://cmake.org/cmake/help/v3.24/variable/CMAKE_MESSAGE_CONTEXT.html#variable:CMAKE_MESSAGE_CONTEXT). 
Run CMake with '-DCMAKE_MESSAGE_CONTEXT_SHOW=true' to show the message context (CMake >= 3.17 is required).

### Boost UUID Link Error

Boost::uuid depends on libatomic by default.
On some machines, libatomic is not available somehow.

To make Boost::uuid stop depending on libatomic, for example,
use `BOOST_UUID_LINK_LIBATOMIC=OFF` in CMake.
This option works with Boost >= v1.87.
For older versions, one needs to modify their CMake files manually.