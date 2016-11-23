# sweep-sdk-cpp

[![Continuous Integration](https://travis-ci.org/scanse/sweep-sdk-cpp.svg?branch=master)](https://travis-ci.org/scanse/sweep-sdk-cpp)


Scanse Sweep SDK for C++

This is only working on Linux for now.

### Build Test Executable 

Get the code:

    git clone https://github.com/scanse/sweep-sdk-cpp 

Build:

    make
    sudo make install

In your project:

    g++ -Wall -Wextra -pedantic -std=c++11 example/example.cc -lsweep-sdk-cpp -pthread

Link the `libsweep-sdk-cpp` library and include `<sweep/*.h>` header in your code; see the example.
