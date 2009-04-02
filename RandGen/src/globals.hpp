/* 
 * File:   globals.hpp
 * Author: uli
 *
 * Created on 18. November 2008, 16:37
 */

#ifndef _GLOBALS_HPP
#define	_GLOBALS_HPP

#define SSE __attribute__((aligned (16)))

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <bitset>

#include <boost/program_options.hpp>
#include <boost/foreach.hpp>
#include <boost/random.hpp>

//TR1
#include <tr1/functional>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

using namespace std;
using namespace boost;
using namespace boost::program_options;
using namespace boost::random;

//This provides the pseudo-random number generators and distributions
using namespace std::tr1;

typedef unsigned long ulong;
typedef unsigned long long ull;
typedef unsigned short ushort;

typedef unsigned long long int_t;
typedef unsigned long smallint_t;
typedef unsigned long long amount_t;
typedef unsigned long seed_t;
typedef long double real_t;

/**
 * Generate and distribution enumerations
 */
enum Generator
{
    MT19937, //Mersenne Twister 19937
    MT11213b, //Mersenne Twister 11213b
    LinearCongruential, //Linear Congruential
    Ecuyer1988, //Additive Combine
    Hellekalek1995, //Inverse Congruential
    Kreutzer1986, //Shuffle output
    LaggedFibonacci607,
    LaggedFibonacci1279,
    LaggedFibonacci2281,
    LaggedFibonacci3217,
    LaggedFibonacci4423,
    LaggedFibonacci9689,
    LaggedFibonacci19937,
    LaggedFibonacci23209,
    LaggedFibonacci44497
};

enum Distribution
{
    UniformSmallInteger,
    UniformInteger,
    UniformReal,
    Triangle,
    Bernoulli,
    Cauchy,
    Exponential,
    Geometric,
    Normal,
    LogNormal,
    UniformOnSphere
};

/**
 * Local includes
 */
#include "generators.hpp"

#endif	/* _GLOBALS_HPP */

