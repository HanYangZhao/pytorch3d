/*
 * cuda13_compat/bits/mathcalls.h
 *
 * Workaround for CUDA 13.x + glibc "incompatible exception specification" error.
 *
 * Root cause:
 *   CUDA 13's crt/math_functions.h declares rsqrt/rsqrtf as __host__ __device__
 *   WITHOUT noexcept (matching C linkage semantics).
 *   glibc's bits/mathcalls.h then redeclares them WITH noexcept(true) via __THROW.
 *   C++ treats these as incompatible declarations → hard error.
 *
 * Fix:
 *   Temporarily empty __THROW so glibc's declarations also lack noexcept,
 *   making them compatible with CUDA's prior declarations.
 *   Only active during CUDA compilation (__CUDACC__).
 */

#ifdef __CUDACC__
#pragma push_macro("__THROW")
#undef __THROW
#define __THROW
#endif

#include_next <bits/mathcalls.h>

#ifdef __CUDACC__
#pragma pop_macro("__THROW")
#endif
