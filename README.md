# Why?

I found the features in `assert.h` to be a little too bland and lackluster.  
I wanted a few more options as to which assertions are which, and a few fancy colors. :)

# Usage  

It is best to include `custom_errors.h` and `custom_errors.c` directly into your project. I have decided to use Bash and Powershell as the simplest ways to build the tests.

There are 3 kinds of "assertions" in this repo, the warning, the regular error, and the fatal error.  

Each error corresponds to different situations:  
> **A warning can be used to denote if the user(s) of a function really know what they are doing. These just print a message if a warning assertion is false, and do not abort the program.**  
> Ex: valid but unusual input that is not planned happen internally  

> **A regular error denotes invalid input/state that should be rectified.**  
> Ex: Divide by 0 error, nullptr, nan, inf  

> **A fatal error is when the program must stop as nothing else can be done.**  
> Ex: Failed heap allocation, failed write to a file, no internet connectivity (if connectivity is needed)  
  
The general examples above are my opinion on how to classify errors. The 3 kinds of errors can be classified however you wish.

Each kind of error can stay, be wiped, or be assumed true by the compiler.  
To remove each kind, use:  
> CE_NO_WARN, CE_NO_ERROR, CE_NO_FATAL  
You may use NDEBUG to remove all 3 kinds with one macro.  

If your compiler supports the "assume" extension, you can use:  
> CE_ASSUME_WARN, CE_ASSUME_ERROR, CE_ASSUME_FATAL  
For no mercy, you may use CE_ASSUME_ALL.  

Keep in mind that `CE_ASSUME_ALL` overrides `NDEBUG`, but `CE_NO_WARN`, `CE_NO_ERROR`, and `CE_NO_FATAL` override   `CE_ASSUME_WARN`, `CE_ASSUME_ERROR`, `CE_ASSUME_FATAL`. `CE_ASSUME_ALL` overrides `NDEBUG` so that `NDEBUG` doesn't need to be removed when configuring the build type to "Release" in build-programs such as CMake.

`CE_NO_RET` is a convenience macro to wrap `[[noreturn]]` and `_Noreturn`. This is useful to prevent a static analyzer such as `-fanalyzer` for gcc from emitting false positives in a code base littered with assertions/error handlers. Only `custom_errors.c` needs this.  
If you want to use it, you may use `#define CE_INCLUDE_NORET` before `#include "path/to/custom_errors.h"`

`static_assert` is also made available if your current C standard is before C23.

# How to build the tests

In the `tests` directory of custom-errors:  

  If on MacOS or a linux distro, given a Bash or Zsh shell:  

      `./unix.sh`  

  If on Windows, given a Powershell shell:  

      `./win.ps1`  

  
# FAQ (No one has asked me these questions.)

***Why is there no benchmark for your own assertion implementation?***  

There is no benchmark here much like how there is no benchmark for the built-in ternary operator, which is far too fast to be a bottleneck. Plus, these warning/error handlers are mostly used in debug builds, not release.
