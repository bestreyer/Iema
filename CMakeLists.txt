project(ImplementsAlgo)
include_directories("include")

cmake_minimum_required(VERSION 3.0)

ENABLE_TESTING()

set(SRC_FOLDER src)
set(BIN_FOLDER bin)
set(UTILS_FOLDER ${BIN_FOLDER}/utils)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SRC_LIST
  ${SRC_FOLDER}/RandomPrimaryGenerator.cpp
  ${SRC_FOLDER}/BloomFilter.cpp
  ${SRC_FOLDER}/LRUCache.cpp
  ${SRC_FOLDER}/main.cpp
)

file(MAKE_DIRECTORY ${BIN_FOLDER})
file(MAKE_DIRECTORY ${UTILS_FOLDER})

# list utils
set(UTILS convertPrimaryTextFileToBinary)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_FOLDER})
add_executable(${PROJECT_NAME} ${SRC_LIST})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${UTILS_FOLDER})
foreach(util ${UTILS})
  add_executable(${util} ${SRC_FOLDER}/utils/${util}.cpp)
endforeach(util)

#include("${CMAKE_CURRENT_LIST_DIR}/CxxTest.cmake")
#cxx_test(bin/test test/BloomFilterSuite1.h)
