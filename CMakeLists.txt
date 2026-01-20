cmake_minimum_required(VERSION 4.1)
project(CppAdsPrometeusConnector)

set(CMAKE_CXX_STANDARD 23)
#add_subdirectory(external/ADS/include/AdsLib)
include_directories(external/ADS/include/AdsLib)

add_executable(CppAdsPrometeusConnector
        src/main.cpp)

target_link_libraries(CppAdsPrometeusConnector PRIVATE ${CMAKE_SOURCE_DIR}/external/ADS/lib/libAdsLib.a)