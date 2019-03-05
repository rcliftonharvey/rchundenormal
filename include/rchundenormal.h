// RCH::Undenormal
//
// Class for scoped protection against creating denormal numbers
// https://github.com/rcliftonharvey/rchundenormal
//
// Copyright © 2019 R. Clifton-Harvey
//
// This source code is released under the MIT license, which means
// you can do anything you want with it, as long as you credit it.
//
// A full version of the license can be found here:
// https://github.com/rcliftonharvey/rchundenormal/blob/master/LICENSE
//
#ifndef _RCH_UNDENORMAL_H
#define _RCH_UNDENORMAL_H


// ---- INCLUDE DEPENDENCIES BELOW ---- //
#include <xmmintrin.h>
// ---- INCLUDE DEPENDENCIES ABOVE ---- //


namespace RCH
{
// ---- MODULE CODE STARTS BELOW ---- //
//
// Sets MXCSR register flags that can (!) speed up SIMD (SSE/AVX) instructions by removing
// the possibility of generating denormal numbers, i.e. really small close-to-zero values.
//
// FTZ - Flush To Zero
// DAZ - Denormals Are Zero
//
// Implemented after Wikipedia article and intel C++ Compiler 15.0 reference
// https://en.wikipedia.org/wiki/Denormal_number#Disabling_denormal_floats_at_the_code_level
// https://software.intel.com/en-us/node/523328
//
// Instantiate this class inside the scope that should not generate denormal numbers.
// When instantiated, protection against generating denormal numbers starts right away.
// When destroyed (i.e. class goes out of scope), denormal protection will stop again.
//
// Depending on whether or not the appropriate macros are defined in your environment, this
// class will either use the present macros or fall back to setting the registers directly.
//
    /** Scoped protection against denormal numbers */
    class Undenormal
    {
    private:
        
        const int maskFTZ = 0x8000;    // Mask to switch FLUSH TO ZERO mode
        const int maskDAZ = 0x0040;    // Mask to switch DENORMALS ARE ZERO mode
        
    public:
        
        /** Start protection against denormal numbers */
        Undenormal ()
        {
            // Set FLUSH TO ZERO mode to ON state
        #if defined (_MM_SET_FLUSH_ZERO_MODE) && defined (_MM_FLUSH_ZERO_ON)
            _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
        #else
            _mm_setcsr(_mm_getcsr() | maskFTZ);
        #endif
            
            // Set DENORMALS ARE ZERO mode to ON state
        #if defined (_MM_SET_DENORMALS_ZERO_MODE) && defined(_MM_DENORMALS_ZERO_ON)
            _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
        #else
            _mm_setcsr(_mm_getcsr() | maskDAZ);
        #endif
        }
        
        /** Stop protection against denormal numbers */
        ~Undenormal ()
        {
            // Set FLUSH TO ZERO mode back to OFF state
        #if defined (_MM_SET_FLUSH_ZERO_MODE) && defined (_MM_FLUSH_ZERO_OFF)
            _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_OFF);
        #else
            _mm_setcsr(_mm_getcsr() & ~maskFTZ);
        #endif
            
            // Set DENORMALS ARE ZERO mode back to OFF state
        #if defined (_MM_SET_DENORMALS_ZERO_MODE) && defined (_MM_DENORMALS_ZERO_OFF)
            _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_OFF);
        #else
            _mm_setcsr(_mm_getcsr() & ~maskDAZ);
        #endif
        }
        
    }; // end class RCH::Undenormal
    
    
// ---- MODULE CODE ENDS ABOVE ---- //
} // end namespace RCH


#endif // #ifndef _RCH_UNDENORMAL_H
