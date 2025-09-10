


# How to build

To build the tests:

    cmake -S . -B builds;  
    cmake --build builds;

Though the library is built automatically if this repo is not in the top level, there is an option to build the library anyway:

    cmake -S . -B lib -DBUILD_CUSTOM_ERRORS_LIBRARY:BOOL=ON;
    cmake --build lib;

# FAQ (No one has asked me these questions.)

***Why is there no benchmark for your own assertion implementation?***  

There is no benchmark here much like how there is no benchmark for the built-in ternary operator, which is far too fast to be a bottleneck **even on debug mode**.


