# RCH::Undenormal
#### Class for scoped denormal number protection in pure C++

-------------------------------------------------------------------------------------------------------

## Index

1. [Introduction](https://github.com/rcliftonharvey/rchundenormal/blob/master/README.md#introduction)
2. [How to use](https://github.com/rcliftonharvey/rchundenormal/blob/master/README.md#how-to-use)
3. [License](https://github.com/rcliftonharvey/rchundenormal/blob/master/README.md#license)

-------------------------------------------------------------------------------------------------------

## Introduction 

This pure C++ class implements denormal number protection for local scopes of code.

Denormal (or sub-normal) numbers are non-zero values smaller than the lowest representable value of a number type. They exist for a reason, but can significantly slow down mathematical processes that handle a lot of small values, think DSP. Disabling them breaks strict IEEE 754 standard compliance, but can (!) significantly speed up certain calculations.

There is lots of good information in the [Wikipedia article about Denormal numbers](https://en.wikipedia.org/wiki/Denormal_number), so be sure to give it a read.

This class was written with no dependencies, which means you can use it by itself and in any application, without being bound to any 3rd party frameworks.

I have done my best to comment the source as much as I could (or made sense to me), so by reading through the header you should get a good enough idea of what does what and how to use it.

The original repository for RCH::Undenormal is right here:<br>
[https://github.com/rcliftonharvey/rchundenormal]

-------------------------------------------------------------------------------------------------------

## How to use

Include the [header file](https://github.com/rcliftonharvey/rchundenormal/tree/master/include/rchundenormal.h) folder in your project.

Depending on your compiler and workspace settings, you will probably have to adjust the include path for this file. But once the include path is sorted out, this is the only line you should need:
```c++
#include "rchundenormal.h"
```

To avoid possible collisions with other libraries you may be using in your projects, the Undenormal class resides in the **RCH::** namespace by default. You're of course welcome to change the namespace in the [rchundenormal.h](https://github.com/rcliftonharvey/rchundenormal/blob/master/include/rchundenormal.h#L23) main include.

You don't need to prepare anything, you can just instantiate the Undenormal class on the fly, anywhere in your running code, when and where you need it.

The Undenormal class handles its own lifetime, so you don't have to (and you can't) start or stop it by hand. As soon as the class goes out of scope, i.e. the scope it was instantiated in ends, the Undenormal class is destroyed and resets denormal numbers to be enabled again.

There's nothing else to do with this class, you can only instantiate it:
```c++
RCH::Undenormal noDenormals;
```

If you instantiate the class at the very beginning of your code, denormals will be deactivated until the code ends. If you instantiate it e.g. inside a conditional branch or a dedicated code block, denormals will be deactivated until that scope ends.

```c++
// Denormal numbers can be crated here
if (shouldDisableDenormals == true)
{
  RCH::Undenormal noDenormals;
  // Denormal numbers can not be created here
  // so do some clever maths with small values
}
// The class instance was destroyed by here,
// so denormal numbers can be created again.
// Creating a dedicated code block below
{
  RCH::Undenormal noDenormals;
  // Denormal numbers can not be created here
}
// The class instance was destroyed again,
// so denormal numbers may be created again.
```

<br>
And that's all there's to it.

-------------------------------------------------------------------------------------------------------

## License

This source code is provided under the [MIT License](https://github.com/rcliftonharvey/rchundenormal/tree/master/LICENSE).<br>
A copy of the MIT license in written form comes in the download of this library.

-------------------------------------------------------------------------------------------------------

Enjoy!

Rob Clifton-Harvey

