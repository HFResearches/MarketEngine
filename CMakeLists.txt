cmake_minimum_required(VERSION 3.20)

project(MarketEngine
  VERSION 1.0
  LANGUAGES CXX)

include(ProcessorCount)
ProcessorCount(N_CORES)

set(CMAKE_BUILD_PARALLEL_LEVEL ${N_CORES})
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAG_RELEASE "-O3 -march=native -DNDEBUG -flto=auto")

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  message(STATUS "ccache found: 
  ${CCACHE_PROGRAM}")

  set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif()

add_executable(MarketEngine
  src/main.cpp)

add_library(MarketEngineLib STATIC
  src/MarketData.cpp)

target_include_directories(MarketEngine 
  PRIVATE src)

find_package(OpenSSL REQUIRED)

target_link_libraries(MarketEngine PRIVATE
  OpenSSL::SSL OpenSSL::Crypto)

install(TARGETS MarketEngineLib
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)

install(FILES
  src/MarketData.hpp
  DESTINATION include)
