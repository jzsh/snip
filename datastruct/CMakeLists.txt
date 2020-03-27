cmake_minimum_required(VERSION 2.8.12)
project(datastruct)


SET(SRC_LIST arraylist.c arrayListDemo.c)

ADD_EXECUTABLE(arrayListDemo ${SRC_LIST})

# build type
if(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE debug)
endif()

MESSAGE(STATUS "HOME dir: $ENV{HOME}")

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=gnu99")
SET(CMAKE_C_FLAGS_RELEASE "-DNDEBUG -O2")
SET(CMAKE_C_FLAGS_DEBUG   "-g -O0")

# Doxygen document
find_package(Doxygen)
if(DOXYGEN_FOUND)
    message(STATUS "Found doxygen:${DOXYGEN_FOUND} ${DOXYGEN_EXECUTABLE}")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif()

