#ifndef  _READTSC_HPP
#define _READTSC_HPP
typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned long long ull;
inline volatile unsigned long readtsc()
{
unsigned long tsc;
asm("rdtsc":"=A"(tsc));
return tsc;
}
#endif