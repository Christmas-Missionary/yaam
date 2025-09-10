


# How to build

To build the tests:

    cmake -S . -B builds;  
    cmake --build builds;

Though the library is built automatically if this repo is not in the top level, there is an option to build the library anyway:

    cmake -S . -B lib -DBUILD_CUSTOM_ERRORS_LIBRARY:BOOL=ON;
    cmake --build lib;
