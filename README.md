![](yam.jpg)

### Segment of a Chinese yam (D. polystachya)

Source: https://commons.wikimedia.org/wiki/File:Dioscorea_polystachya_(batatas).jpg  
No Author. File is considered to be in the Public Domain.

# Why?

I found the features in `assert.h` to be a little too bland and lackluster.  
I wanted a few more options as to which assertions are which, and a few fancy colors. :)

# Usage  

It is best to include `yaam.h` and `yaam.c` directly into your project. I have decided to use Bash and PowerShell as the simplest ways to build the tests.

There are 3 kinds of "assertions" in this repo, the warning, the regular error, and the fatal error.  

Each error corresponds to different situations:  
> **A warning can be used to denote if the user(s) of a function really know what they are doing. These just print a message if a warning assertion is false, and do not abort the program.**  
> Ex: valid but unusual input that is not planned happen internally  

> **A regular error denotes invalid input/state that should be rectified.**  
> Ex: Divide by 0 error, nullptr, NaN, inf  

> **A fatal error is when the program must stop as nothing else can be done.**  
> Ex: Failed heap allocation, failed write to a file, no internet connectivity (if connectivity is needed)  
  
The general examples above are my opinion on how to classify errors. The 3 kinds of errors can be classified however you wish.

Each kind of error can stay, be wiped, or be assumed true by the compiler.  
To remove each kind, use:  
> YAAM_NO_WARN, YAAM_NO_ERROR, YAAM_NO_FATAL  
You may use YAAM_NONE to remove all 3 kinds with one macro.  

If your compiler supports the "assume" extension, you can use:  
> YAAM_ASSUME_WARN, YAAM_ASSUME_ERROR, YAAM_ASSUME_FATAL  
For no mercy, you may use YAAM_ASSUME_ALL.  

I choose YAAM_NONE over a standardized macro such as NDEBUG
YAAM_NONE takes priority over YAAM_ASSUME_ALL.

`YAAM_NO_RET` is a convenience macro to wrap `[[noreturn]]` and `_Noreturn`. This is useful to prevent a static analyzer such as `-fanalyzer` for GCC from emitting false positives in a codebase littered with assertions/error handlers. Only `yaam.c` needs this.  
If you want to use it, you may use `#define YAAM_INCLUDE_NORET` before `#include "path/to/yaam.h"`

`static_assert` is also made available if your current C standard is before C23.

ANSI escape codes are used to give colors and boldness to text, highlighting the important stuff when debugging.  
`YAAM_NO_COLORS` can be defined if you don't want ANSI escape codes, or the console you will be using (e.g. Web Console) doesn't support them.

# How to Build the Tests

In the top directory:  

  If on MacOS or a Linux distro, given a Bash shell:  

      ./unix.sh  

  If on Windows, given a PowerShell shell:  

      ./win.ps1  

  
# FAQ (No one has asked me these questions.)

***The text `Func not available` appears as opposed to the name of the function when an error/warning is emitted. Why?***

You have probably set the standard to a version without the predefined variable `__func__`. These standards are: C89/ANSI C, C95, and C++98.

As of right now, MSVC doesn't enforce these versions, only C11 and C++14 at the earliest. If you are still getting this for MSVC, are you also compiling C files while setting a C++ standard? If so, include the `/TP` compiler flag somewhere to ENSURE that all files regardless of the extension are treated as C++. This does not seem to be the case for compiling C++ files while setting a C standard.

***Why is there no benchmark for your own assertion implementation?***  

There is no benchmark here much like how there is no benchmark for the built-in ternary operator, which is far too fast to be a bottleneck. Plus, these warning/error handlers are mostly used in debug builds, not release.
