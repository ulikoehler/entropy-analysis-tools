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
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>



#include <stdlib.h>
#include <math.h>

using namespace std;
using namespace boost;
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
static char rCompatible;

static string separator = ","; //For CSV output

/**
 * Buffer char array, initialized
 * in main function before analyzator function calls
 */
static char* buffer SSE;

int blocksize;
int chunksize;

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
//Actions
#include "actions.hpp"


#endif	/* _GLOBALS_HPP */

