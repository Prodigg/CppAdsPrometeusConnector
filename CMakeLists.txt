cmake_minimum_required(VERSION 4.1)
project(CppAdsPrometeusConnector)

set(CMAKE_CXX_STANDARD 23)
#add_subdirectory(external/ADS/include/AdsLib)
include_directories(external/ADS/include/AdsLib)
include_directories(external/libpistacheStatic/include)

add_executable(CppAdsPrometeusConnector
        src/main.cpp
        src/ProcessDataBuffer.h
        src/ProcessDataBuffer.cpp
        src/ADSProvidor.h
        src/ADSProvidor.cpp
        src/PrometheusEndpoint.h
        src/PrometheusEndpoint.cpp
)

target_link_libraries(CppAdsPrometeusConnector PRIVATE ${CMAKE_SOURCE_DIR}/external/ADS/lib/libAdsLib.a)
target_link_libraries(CppAdsPrometeusConnector PRIVATE ${CMAKE_SOURCE_DIR}/external/libpistacheStatic/libpistache.a)
