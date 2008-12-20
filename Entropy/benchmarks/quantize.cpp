/**
 * This benchmark tests quantizing floating point numbers by using Boost::format
 * against the mathematical way with fmod: x-fmod(x,10^-precision)
 * Do not forget to compile without optimizing!
 */

#include <cmath>
#include <cstdlib>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include "readtsc.h"

using namespace std;
using namespace boost;

#define nprec 3 //Precision
#define prec 0.001 //10^-precision
#define ITERATIONS 100000

//Global variables all calcouulated outside loop
static string formatString;

inline string quantizeFormat(double& in)
{
	return str(format(formatString) % in);
}

inline double quantizeFmod(double& in)
{
	return in-fmod(in,prec);
}

int main()
{
	static ulong a = 0,b = 0;
	static ull sum = 0;
	static double n;
	//Precalculate the format string
	formatString = "%." + lexical_cast<string>(nprec) + "f";
	//Raw function call
	for(int i = ITERATIONS;i >0;i--)
	{
		n = rand();
		a = readtsc();
			quantizeFormat(n);
		b = readtsc();
		sum += b-a;
	}
	cout << "Formatting algorithm: " << sum/ITERATIONS << " timesteps" << endl;
	sum = 0;
	//Inline function call
	for(int i = ITERATIONS;i >0;i--)
	{
		n = rand();
		a = readtsc();
			quantizeFmod(n);
		b = readtsc();
		sum += b-a;
	}
	cout << "Fmod call: " << sum/ITERATIONS << " timesteps" << endl;
	sum = 0;	
	return 0;
}
