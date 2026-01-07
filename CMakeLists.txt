cmake_minimum_required(VERSION 4.1)
project(CppAdsPrometeusConnector)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(external/beckhoffAds/beckhoffAds)

add_executable(CppAdsPrometeusConnector main.cpp)

target_link_libraries(CppAdsPrometeusConnector PRIVATE beckhoffAds)