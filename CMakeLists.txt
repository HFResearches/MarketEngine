cmake_minimum_required(VERSION 3.20)

project(MarketEngine
  VERSION 1.0
  LANGUAGES CXX)

include(ProcessorCount)
ProcessorCount(N_CORES)

set(CMAKE_BUILD_PARALLEL_LEVEL ${N_CORES})
set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
set(CMAKE_CXX_FLAG_RELEASE "-O3 -march=native -DNDEBUG -flto=auto")

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  message(STATUS "ccache found: 
  ${CCACHE_PROGRAM}")

  set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif()

set(CMAKE_BUILD_TYPE Release)

add_executable(MarketEngine
  src/main.cpp)

target_include_directories(MarketEngine 
  PRIVATE src)

find_package(OpenSSL REQUIRED)

target_link_libraries(MarketEngine PRIVATE
  OpenSSL::SSL OpenSSL::Crypto)

find_package(duckdb CONFIG QUIET)
if(NOT duckdb_FOUND)
  include(FetchContent)

  FetchContent_Declare(duckdb 
    GIT_REPOSITORY
    https://github.com/duckdb/duckdb.git
  
    GIT_TAG v1.4.2)

    FetchContent_MakeAvailable(duckdb)
endif()

target_link_libraries(MarketEngine PRIVATE duckdb)

if(NOT nlohmann_json_FOUND)
  include(FetchContent)
  FetchContent_Declare(nlohmann_json
    GIT_REPOSITORY
    https://github.com/nlohmann/json.git
 
    GIT_TAG v3.11.2
    GIT_SHALLOW TRUE)

    FetchContent_MakeAvailable(nlohmann_json)
endif()

target_link_libraries(MarketEngine PRIVATE  
  nlohmann_json::nlohmann_json)

