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

#include <boost/program_options.hpp>
#include <boost/function.hpp>
#include <boost/foreach.hpp>

#include <stdlib.h>
#include <math.h>

using namespace std;
using namespace boost::program_options;

typedef unsigned long ulong;
typedef unsigned int uint;

/**
 * Zeroing these variables at procedure start is only neccessary
 * in nested function calls because they are used only once
 * per program call
 */
unsigned long long glob0 = 0;
unsigned long long glob1 = 0;
unsigned long long chunk0 = 0;
unsigned long long chunk1 = 0;

static char perblock;

static string separator = ","; //For CSV output

/**
 * Buffer char array, initialized
 * in main function before analyzator function calls
 */
static char* buffer SSE;

int blocksize;
int chunksize;

//Program options
variables_map vm;

/**
 * Local includes
 */
#include "count1bits.hpp"
#include "analyze-bits.hpp"
#include "analyze-chunks.hpp"

#endif	/* _GLOBALS_HPP */

