#ifndef  _READTSC_HPP
#define _READTSC_HPP
typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned long long ull;

inline volatile uint64_t readtsc()
{
uint64_t tsc;
asm("rdtsc":"=A"(tsc) );
return tsc;
}
#endif