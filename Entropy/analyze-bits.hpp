/* 
 * File:   analyze-bits.hpp
 * Author: uli
 *
 * Created on 16. November 2008, 18:17
 */


#ifndef _ANALYZE_BITS_HPP
#define	_ANALYZE_BITS_HPP

#include "globals.hpp"
#include <fstream>
using namespace std;

/**
 * Counts the 1-bits in one file (does not take care of blocks)
 */
void analyzeBits(ifstream& f);

/**
 * Analyzes bits in blocks and prints them out into the statistics file
 */
void analyzeBitsBlocks(ifstream& f, ofstream& of);

#endif	/* _ANALYZE_BITS_HPP */

