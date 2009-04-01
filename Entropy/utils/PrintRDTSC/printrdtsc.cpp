#include <iostream>

using namespace std;

inline volatile uint64_t ReadTSC()
{
uint64_t tsc;
asm("rdtsc":"=A"(tsc) );
return tsc;
}

int main(int argc, char** argv)
{
	cout << ReadTSC() << endl;
}