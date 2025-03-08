cmake_minimum_required(VERSION 3.20)
project(test_fetch_content)
include(FetchContent)

set(CMAKE_CXX_STANDARD 20)

# This CMake is designed to work with the Boost libraires available on
# https://github.com/boostorg/boost/releases. Must be *-cmake version.
# About URL option in FetchContent_Declare:
#  - URL can be a path to an already downloaded boost file.
#  - Must be a compressed version (e.g., *.tar.gz).
#  - If the directory is already uncompressed, use SOURCE_DIR instead of URL.
FetchContent_Declare(
  Boost
  URL https://github.com/boostorg/boost/releases/download/boost-1.87.0/boost-1.87.0-cmake.tar.gz
  URL_HASH
    SHA256=78fbf579e3caf0f47517d3fb4d9301852c3154bfecdc5eeebd9b2b0292366f5b)

set(BOOST_INCLUDE_LIBRARIES
    json
    unordered
    interprocess
    container
    property_tree
    uuid
    graph)

# Boost::uuid depends on libatomic by default.
# On LC, libatomic is not available somehow.
# To make Boost::uuid stop depending on libatomic, use:
# set(BOOST_UUID_LINK_LIBATOMIC OFF)
# NOTE: this option works with boost-1.87.
# For older versions, we need to modify their CMake files manually.

FetchContent_MakeAvailable(Boost)
# Memo: boost_POPULATED is set to TRUE by FetchContent_MakeAvailable This can be
# used to avoid calling find_packge() in child projects

# Utilize BOOST_INCLUDE_LIBRARIES to generate BOOST_COMPONENTS
foreach(lib ${BOOST_INCLUDE_LIBRARIES})
  list(APPEND BOOST_COMPONENTS "Boost::${lib}")
endforeach()

# Test with Metall Fetch Metall Make Metall installation light explicitly
# (optional)
set(JUST_INSTALL_METALL_HEADER ON)
# set(BUILD_EXAMPLE ON)
FetchContent_Declare(
  Metall
  GIT_REPOSITORY https://github.com/LLNL/metall.git
  GIT_TAG feature/cmake-config)
FetchContent_MakeAvailable(Metall)

# If Metall is already installed find_package(Metall REQUIRED PATHS
# /home/ubuntu/metall-dpl/build/install)

find_package(Threads REQUIRED)

add_executable(metall_example metall_example.cpp)
target_link_libraries(metall_example PRIVATE Threads::Threads Metall::Metall
                                             ${BOOST_COMPONENTS})
