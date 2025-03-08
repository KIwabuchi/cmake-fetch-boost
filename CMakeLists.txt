cmake_minimum_required(VERSION 3.20)
project(test_fetch_content)
include(FetchContent)

set(CMAKE_CXX_STANDARD 20)

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

# Required on LC
# This option works >= boost-1.87
# set(BOOST_UUID_LINK_LIBATOMIC OFF)

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
