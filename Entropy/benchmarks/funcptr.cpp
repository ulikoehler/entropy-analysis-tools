/**
* Benchmars raw function calls against inline function calls and function pointer calls (using boost function)
* Compile with gcc funcptr.cpp -O0 -o funcptr
*/ 
#include "readtsc.h"
#include <boost/function.hpp> //Should not cause any overhead
#include <iostream>
#include <cmath>
#include <MersenneTwister.h>

#define ITERATIONS 1000000 

using namespace std;
using namespace boost;

uint doCalc(uint n)
{
	return n*n;
}

uint doCalcInline(uint n)
{
	return n*n;
}

int main()
{
	ulong a = 0,b = 0;
	ull sum = 0;
	MTRand r;
	uint n;
	//Raw function call
	for(int i = ITERATIONS;i >0;i--)
	{
		n = r.randInt();
		a = readtsc();
			doCalc(n);
		b = readtsc();
		sum += b-a;
	}
	cout << "Raw call: " << sum/ITERATIONS << " timesteps" << endl;
	sum = 0;
	//Inline function call
	for(int i = ITERATIONS;i >0;i--)
	{
		n = r.randInt();
		a = readtsc();
			doCalcInline(n);
		b = readtsc();
		sum += b-a;
	}
	cout << "Inline call: " << sum/ITERATIONS << " timesteps" << endl;
	sum= 0;
	//Pointer function call
	boost::function<int(int)> doCalcPtr = doCalc;
	for(int i = ITERATIONS;i >0;i--)
	{
		n = r.randInt();
		a = readtsc();
			doCalcPtr(n);
		b = readtsc();
		sum += b-a;
	}
	cout << "Pointer call: " << sum/ITERATIONS << " timesteps" << endl;	
	return 0;
}