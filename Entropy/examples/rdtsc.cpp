#include <iostream>
#include <fstream>
#include <tr1/random>

using namespace std;
using namespace std::tr1;

#define ITERATIONS 10000

using namespace std;

inline volatile uint64_t ReadTSC()
{
uint64_t tsc;
asm("rdtsc":"=A"(tsc) );
return tsc;
}

int main(int argc, char** argv)
{
	ofstream f("rdtsc.txt");
	mt19937 rng(time(0));
	for(int i = 0; i < ITERATIONS; i++)
		{
			rng();
			f << ReadTSC() << endl;
		}
	return 0;
}