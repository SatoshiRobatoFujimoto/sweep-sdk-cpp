cmake_minimum_required(VERSION 2.8.3)
project(sweep-sdk-cpp)

## Sources
set(sweep-sdk-cpp_SRCS
        src/serial/serial.cc
        src/sweep_driver.cc
        src/util.cc
        )

if (APPLE)
    # If OSX
    list(APPEND sweep-sdk-cpp_SRCS src/serial/arch/unix.cc)
elseif (UNIX)
    # If unix
    list(APPEND sweep-sdk-cpp_SRCS src/serial/arch/unix.cc)
else ()
    # If windows
    list(APPEND sweep-sdk-cpp_SRCS src/serial/arch/win.cc)
endif ()

add_library(${PROJECT_NAME} ${sweep-sdk-cpp_SRCS})

## Include headers
include_directories(inc inc/serial)

## Uncomment for example
add_executable(example src/example.cc)
add_dependencies(example ${PROJECT_NAME})
target_link_libraries(example ${PROJECT_NAME} pthread)



