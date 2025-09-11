# Why?

I found the features in `assert.h` to be a little too bland and lackluster.  
I wanted a few more options as to which errors are which, and fancy colors. :)

# Usage  

It is best to include `custom_errors.h` and `custom_errors.c` directly into your project, as making them into a library adds unnecessary complexity. The use of CMake is only for the building of the tests.

# How to build the tests

    cmake -S . -B builds;  
    cmake --build builds;  

# FAQ (No one has asked me these questions.)

***Why is there no benchmark for your own assertion implementation?***  

There is no benchmark here much like how there is no benchmark for the built-in ternary operator, which is far too fast to be a bottleneck **even on debug mode**.
