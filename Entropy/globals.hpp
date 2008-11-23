/* 
 * File:   globals.hpp
 * Author: uli
 *
 * Created on 16. November 2008, 19:23
 */

#ifndef _GLOBALS_HPP
#define	_GLOBALS_HPP

#define SSE __attribute__((aligned (16)))

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <bitset>

/**
 * Boosting entropy
 */
#include <boost/program_options.hpp>
#include <boost/function.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/sum.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/skewness.hpp>

#include <boost/accumulators/statistics/weighted_mean.hpp>
#include <boost/accumulators/statistics/weighted_moment.hpp>
#include <boost/accumulators/statistics/weighted_mean.hpp>
#include <boost/accumulators/statistics/weighted_variance.hpp>
#include <boost/accumulators/statistics/weighted_skewness.hpp>
#include "boost/format.hpp"


#include <stdlib.h>
#include <math.h>

using namespace std;
using namespace boost;
using namespace boost::accumulators;
using namespace boost::program_options;

//Typedefs
typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned short ushort;
//typedef long double ld;

typedef unsigned long val_t; //For use in analyze-chunks.hpp

/**
 * Zeroing these variables at procedure start is only neccessary
 * in nested function calls because they are used only once
 * per program call
 */
unsigned long long glob0 = 0;
unsigned long long glob1 = 0;
unsigned long long chunk0 = 0;
unsigned long long chunk1 = 0;

/**
 * Command line options
 */
//Bools (here used as chars
static char perblock;

static string separator = ","; //For CSV output
static string ldFormatString; //long double format string

/**
 * Buffer char array, initialized
 * in main function before analyzator function calls
 */
static char* buffer SSE;

static int blocksize;
static int chunksize;
static int fillByte;

unsigned short base;

//Program options
variables_map vm;

/**
 * Local includes
 */
//Algorithms
#include "entropy-algorithms.hpp"
#include "count1bits.hpp"
#include "analyze-bits.hpp"
#include "analyze-chunks.hpp"

#endif	/* _GLOBALS_HPP */

