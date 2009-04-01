#include <iostream>
#include <fstream>

using namespace std;

inline volatile unsigned long ReadTSC()
{
unsigned long tsc;
asm("rdtsc":"=A"(tsc));
return tsc;
}

int main(int argc, char** argv)
{
	ofstream f("x.txt");
	for(int i = 0; i < 1000000; i++)
		{
			f << ReadTSC() << endl;
		}
	return 0;
}