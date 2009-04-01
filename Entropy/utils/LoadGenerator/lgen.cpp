#include "iostream"
#include "boost/lexical_cast.hpp"
#include "boost/random.hpp"

using namespace std;
using namespace boost;

typedef unsigned long long ull;

static unsigned long long c = 0;

//Fwd dec
void simpleCount(const ull& max);
void runDieMT(const ull& count);

int main( int argc, char** argv)
{
	static unsigned long long max = lexical_cast<unsigned long long>(argv[1]);
	runDieMT(max);
	return 0;
}

void simpleCount(const ull& max)
{
	for (;c < max; c++)
	{
		if (c % 1000000 == 0)
		{
			cout << "Counted " << c << " times" << endl;
		}
	}
}

template<class gen>
void runDieInternal(const ull& max)
{
	static ull results[6];
	results[0] = 0;
	results[1] = 0;
	results[2] = 0;
	results[3] = 0;
	results[4] = 0;
	results[5] = 0;
	static int x;
	gen rng;
	boost::uniform_int<> six(1,6);
	boost::variate_generator<gen&, boost::uniform_int<> > die(rng, six);
	for (;c < max; c++)
	{
		x = die();
		results[x-1]++;
		
		if (c % 1000000 == 0)
		{
			cout << "Rolled " << c << " times" << endl;
		}
	}
	cout << "----Results:----" << endl;
	cout	<< "1: " << results[0] << endl;
	cout	<< "2: " << results[1] << endl;
	cout	<< "3: " << results[2] << endl;
	cout	<< "4: " << results[3] << endl;
	cout	<< "5: " << results[4] << endl;
	cout	<< "6: " << results[5] << endl;
}

void runDieMT(const ull& count)
{
	runDieInternal<mt19937>(count);
}