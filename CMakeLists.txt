cmake_minimum_required(VERSION 2.8.11)
project(sweep-sdk-cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic")

# Library sources to built
set(sweep-sdk-cpp_SRCS
        src/serial/serial.cc
        src/sweep_driver.cc
        src/util.cc)

if (APPLE)
    list(APPEND sweep-sdk-cpp_SRCS src/serial/arch/unix.cc)
elseif (UNIX)
    list(APPEND sweep-sdk-cpp_SRCS src/serial/arch/unix.cc)
else ()
    list(APPEND sweep-sdk-cpp_SRCS src/serial/arch/win.cc)
endif ()

find_package(Threads REQUIRED)

add_library(sweep-sdk-cpp ${sweep-sdk-cpp_SRCS})
target_link_libraries(sweep-sdk-cpp ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(sweep-sdk-cpp PUBLIC include include/serial)
install(TARGETS sweep-sdk-cpp DESTINATION lib)
install(DIRECTORY include/sweep DESTINATION include)

add_subdirectory(example)
