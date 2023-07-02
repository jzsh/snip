cmake_minimum_required(VERSION 2.8.12)
project(snip)


SET(SRC_LIST free_malloc.c)

ADD_EXECUTABLE(free_malloc ${SRC_LIST})
ADD_EXECUTABLE(endian endian.c)

# build type
if(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE debug)
endif()

MESSAGE(STATUS "HOME dir: $ENV{HOME}")

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=gnu99")
SET(CMAKE_C_FLAGS_RELEASE "-DNDEBUG -O2")
SET(CMAKE_C_FLAGS_DEBUG   "-g -O0")
