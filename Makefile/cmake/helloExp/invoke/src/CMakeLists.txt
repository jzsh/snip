set(CMAKE_INCLUDE_DIRECTORIES_BEFORE on)
INCLUDE_DIRECTORIES(/tmp/cmake/include/myprint/)
LINK_DIRECTORIES(/tmp/cmake/lib/)

ADD_EXECUTABLE(main main.c)
TARGET_LINK_LIBRARIES(main libmyprint.a)
