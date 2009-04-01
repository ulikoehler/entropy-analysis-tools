#include <iostream>

using namespace std;

inline volatile unsigned long ReadTSC()
{
unsigned long tsc;
asm("rdtsc":"=A"(tsc));
return tsc;
}

int main(int argc, char** argv)
{
	cout << ReadTSC() << endl;
}