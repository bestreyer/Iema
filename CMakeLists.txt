project(ImplementsAlgo)
include_directories("include")

ENABLE_TESTING()

set(SRC_FOLDER src)
set(BIN_FOLDER bin)
set(UTILS_FOLDER ${BIN_FOLDER}/utils)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(SRC_LIST
  ${SRC_FOLDER}/RandomPrimaryGenerator.cpp
  ${SRC_FOLDER}/BloomFilter.cpp
  ${SRC_FOLDER}/main.cpp
)

file(MAKE_DIRECTORY ${BIN_FOLDER})
file(MAKE_DIRECTORY ${UTILS_FOLDER})

# list utils
set(UTILS convertPrimaryTextFileToBinary)

add_executable(${BIN_FOLDER}/${PROJECT_NAME} ${SRC_LIST})

foreach(util ${UTILS})
  add_executable(${UTILS_FOLDER}/${util} ${SRC_FOLDER}/utils/${util}.cpp)
endforeach(util)

include("${CMAKE_CURRENT_LIST_DIR}/CxxTest.cmake")
cxx_test(bin/test test/BloomFilterSuite1.h)
