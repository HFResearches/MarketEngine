cmake_minimum_required(VERSION 3.10)

project(MarketEngine
  VERSION 1.0
  LANGUAGES CXX)

find_program(CCACHE_PROGRAM ccache)
  message(STATUS "ccache found: 
  ${CCACHE_PROGRAM}")

set(CMAKE_BUILD_TYPE Release)

if(CCACHE_PROGRAM)
  set(CMAKE_C_COMPILER_LAUNCHER 
  ${CCACHE_PROGRAM})

  set(CMAKE_CXX_COMPILER_LAUNCHER
  ${CCACHE_PROGRAM})
endif()

add_executable(MarketEngine
  src/main.cpp)

target_include_directories(MarketEngine 
  PRIVATE src)

find_package(OpenSSL REQUIRED)

include(FetchContent)

FetchContent_Declare(duckdb 
  GIT_REPOSITORY
  https://github.com/duckdb/duckdb.git
  
  GIT_TAG v1.4.2)

FetchContent_MakeAvailable(duckdb)

FetchContent_Declare(nlohmann_json
  GIT_REPOSITORY
  https://github.com/nlohmann/json.git
 
  GIT_TAG v3.12.0)

FetchContent_MakeAvailable(nlohmann_json)

target_link_libraries(MarketEngine PRIVATE
  OpenSSL::SSL
  OpenSSL::Crypto

  duckdb
  nlohmann_json::nlohmann_json)


