CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(rshell
    src/and.cpp
    src/command.cpp
    src/connector.cpp
    src/or.cpp
    src/semi.cpp
    src/user.cpp
    src/main.cpp
    src/pipe.cpp
    src/input.cpp
    src/output1.cpp
    src/output2.cpp
)

ADD_EXECUTABLE(test
    unit_tests/test.cpp
    src/and.cpp
    src/command.cpp
    src/connector.cpp
    src/or.cpp
    src/semi.cpp
    src/user.cpp
    src/pipe.cpp
    src/input.cpp
    src/output1.cpp
    src/output2.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
