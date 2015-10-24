#Find CxxTestGet
FIND_PROGRAM(CXXTESTGEN
    NAMES cxxtestgen
    PATHS "${CXXTEST_PATH}/bin"
          "${PROJECT_SOURCE_DIR}/cxxtest/bin"
          "${PROJECT_SOURCE_DIR}/lib/cxxtest/bin"
          "${PROJECT_BINARY_DIR}/cxxtest/bin"
          "${PROJECT_BINARY_DIR}/lib/cxxtest/bin"
          /usr/bin
          /bin
          )

FIND_PATH(CXXTEST_INCLUDES
    NAMES "cxxtest/TestSuite.h"
    PATHS "${CXXTEST_PATH}"
          "${PROJECT_SOURCE_DIR}/cxxtest/"
          "${PROJECT_SOURCE_DIR}/lib/cxxtest/"
          )

IF(NOT CXXTESTGEN)
    MESSAGE(FATAL_ERROR "Unable to find 'cxxtestgen'")
    SET(CXXTEST_FOUND false)
ELSEIF(NOT CXXTEST_INCLUDES)
    SET(CXXTEST_FOUND false)
ELSE(NOT CXXTESTGEN)
    SET(CXXTEST_FOUND true)
    SET(CXXTEST_ROOT ${CXXTEST_INCLUDES})
ENDIF(NOT CXXTESTGEN)

SET(CXXTEST_CMAKE_MODULES_PATH "${CMAKE_CURRENT_LIST_DIR}")
SET(CXXTEST_SRC_FOLDER testsrc)
file(MAKE_DIRECTORY ${CXXTEST_SRC_FOLDER})


#Добавление нового теста
function(cxx_test target source)
    get_filename_component(CPP_FILE_NAME ${source} NAME)
    string(REGEX REPLACE "h$|hpp$" "cpp" CPP_FILE_NAME ${CPP_FILE_NAME})
    message(${CPP_FILE_NAME})
    set(CPP_FULL_NAME "${CXXTEST_SRC_FOLDER}/${CPP_FILE_NAME}")
    message(${CPP_FULL_NAME})
    add_custom_command(
        OUTPUT "${CPP_FULL_NAME}"
        COMMAND ${CXXTESTGEN} --runner=ErrorPrinter --output "${CPP_FULL_NAME}" "${source}"
        DEPENDS "${source}"
    )
    add_executable(${target} ${CPP_FULL_NAME})
    set_target_properties(${target} PROPERTIES COMPILE_FLAGS "-I${CXXTEST_INCLUDES} -Wno-effc++")
    add_test(${target} ${target})
endfunction(cxx_test)
