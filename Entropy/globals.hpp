/* 
 * File:   globals.hpp
 * Author: uli
 *
 * Created on 16. November 2008, 19:23
 */

#ifndef _GLOBALS_HPP
#define	_GLOBALS_HPP

/**
 * Append to each array declaration
 * --> fast vectorizing
 */
#define SSE __attribute__((aligned (16)))

/**
 * C/C++ Standard library
 */
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <cmath>
#include <bitset>

/**
 * Boosting entropy
 */
#include <boost/cstdint.hpp>
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

using namespace std;
using namespace boost;
using namespace boost::accumulators;
using namespace boost::program_options;

//Typedefs

typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned long long ull;
//typedef long double ld;

typedef unsigned long val_t;

/**
 * Command line options
 */
//Bools (here used as chars
static char perblock;

static string separator = ","; //For CSV output
static string ldFormatString; //long double format string

/**
 * Buffers and globally used variables
 */
//Buffer char array, initialized
//in main function before analyzator function calls
static char* buffer SSE;

static uint blocksize;
static uint chunksize;
static uint fillByte;
static uint focus;

static uint i,j,c; //Ugly but saving memory and time in nested loops

//STL containers
/*
 * All occurrences map:
 * Maps a binary string ("chunk") represented as a number
 * to the count of occurrences of this number
 * With -p:
 *      Cleared after each block
 */
static map<val_t, ulong> allOcc; // All occurrences
static pair<val_t, ulong> p;
static uint res;

//Program options
static variables_map vm;

/**
 * Local includes
 */

//Algorithms
#include "output.hpp"
#include "analyze-numeric.hpp"
#include "entropy-algorithms.hpp"
#include "count1bits.hpp"
#include "analyze-bits.hpp"
#include "analyze-chunks.hpp"
#include "focus.hpp"

#endif	/* _GLOBALS_HPP */

