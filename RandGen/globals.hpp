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
#include <boost/function.hpp>
#include <boost/random.hpp>
#include <boost/foreach.hpp>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

using namespace std;
using namespace boost;
using namespace boost::program_options;

typedef unsigned long ulong;
typedef unsigned long long ull;
typedef unsigned short ushort;

typedef unsigned long long int_t;
typedef unsigned long smallint_t;
typedef unsigned long long amount_t;
typedef unsigned long seed_t;
typedef long double real_t;

/**
 * Local includes
 */
#include "generators.hpp"

#endif	/* _GLOBALS_HPP */

