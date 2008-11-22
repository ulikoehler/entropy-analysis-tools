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

#include <stdlib.h>
#include <math.h>
#include <time.h>

using namespace std;
using namespace boost;
using namespace boost::program_options;

typedef unsigned long ulong;
typedef unsigned long long ull;

/**
 * Local includes
 */
#include "generators.hpp"

#endif	/* _GLOBALS_HPP */

