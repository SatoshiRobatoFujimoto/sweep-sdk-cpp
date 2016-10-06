set(sweep-sdk-cpp-example_SRCS
        example.cc)

find_package(Threads REQUIRED)

add_executable(sweep-sdk-cpp-example example.cc)
target_link_libraries(sweep-sdk-cpp-example sweep-sdk-cpp ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS sweep-sdk-cpp-example DESTINATION bin)
