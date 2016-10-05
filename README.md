# sweep-sdk-cpp

[![Join the chat at https://gitter.im/scanse/sweep-sdk-cpp](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/scannable/sweep-sdk-cpp?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

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
