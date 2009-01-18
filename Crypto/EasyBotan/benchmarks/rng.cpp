#include <botan/botan.h>
#include <botan/init.h>
#include <iostream>
#include "readtsc.h"

using namespace std;
using namespace Botan;

typedef unsigned long ulong;

int main(int argc, char** argv)
{
	static ulong t1 = readtsc();
	LibraryInitializer init;
	static ulong t2 = readtsc();
	//Print out the results
	ulong diff = t2-t1;
	cout << "LibraryInitializer time in CPU timesteps: " << diff << endl;
	t1 = readtsc();
	AutoSeeded_RNG rng;
	t2 = readtsc();
	//Print out the results
	diff = t2-t1;
	cout << "First RNG init time in CPU timesteps: " << diff << endl;
	t1 = readtsc();
	AutoSeeded_RNG rng2;
	t2 = readtsc();
	//Print out the results
	diff = t2-t1;
	cout << "Second RNG init time in CPU timesteps: " << diff << endl;
	t1 = readtsc();
	AutoSeeded_RNG rng3;
	t2 = readtsc();
	//Print out the results
	diff = t2-t1;
	cout << "Third RNG init time in CPU timesteps: " << diff << endl;
	return 0;
}