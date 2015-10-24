project(ImplementsAlgo)
include_directories("include")

set(SRC_FOLDER src)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(SRC_LIST
  ${SRC_FOLDER}/RandomPrimaryGenerator.cpp
  ${SRC_FOLDER}/BloomFilter.cpp
  ${SRC_FOLDER}/main.cpp
)

set(BIN_FOLDER bin)
set(UTILS_FOLDER ${BIN_FOLDER}/utils)

file(MAKE_DIRECTORY ${BIN_FOLDER})
file(MAKE_DIRECTORY ${UTILS_FOLDER})

# list utils
set(UTILS convertPrimaryTextFileToBinary)

add_executable(${BIN_FOLDER}/${PROJECT_NAME} ${SRC_LIST})

foreach(util ${UTILS})
  add_executable(${UTILS_FOLDER}/${util} ${SRC_FOLDER}/utils/${util}.cpp)
endforeach(util)
