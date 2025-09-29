# Why?

I found the features in `assert.h` to be a little too bland and lackluster.  
I wanted a few more options as to which errors are which, and fancy colors. :)

# Usage  

It is best to include `custom_errors.h` and `custom_errors.c` directly into your project. I have decided to use Bash and Powershell as the simplest ways to build the tests.
  
# How to build the tests

In the repo directory of custom-errors:  

  If on MacOS or a linux distro:  

      `./tests/unix.sh`  

  If on Windows:  

      `Insert execute command here for powershell file`  

  
# FAQ (No one has asked me these questions.)

***Why is there no benchmark for your own assertion implementation?***  

There is no benchmark here much like how there is no benchmark for the built-in ternary operator, which is far too fast to be a bottleneck. Plus, these warning/error handlers are mostly used in debug builds, not release.
