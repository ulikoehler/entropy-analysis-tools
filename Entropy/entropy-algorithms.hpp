/* 
 * File:   entropy-algorithms.hpp
 * Author: uli
 *
 * Created on 19. November 2008, 18:51
 */

#ifndef _ENTROPY_ALGORITHMS_HPP
#define	_ENTROPY_ALGORITHMS_HPP

#include "globals.hpp" //Declares ld = long double

#include <sys/types.h>
#include <sys/stat.h>
#include <cmath>

/**
 * Calculates entropy of two given values
 * (used in analyze-bits.hpp with 0 and 1 values)
 */
inline long double shannonEntropy(ull& zeroes, ull& ones, ulong size)
{
    static long double entropy = 0.0E0l; //Return value
    static long double prob; //The probability of a single char to occur (used as buffer)
    //Calculate entropy (must be negated before returning)
    prob = zeroes/size;
    entropy = (long double)prob*log2(prob);
    prob = ones/size;
    entropy += (long double)ones*log2(ones);

    return (long double)-entropy;
}

/**
 * Calculates entropy of a given filled map using Shannon's algorithm
 * Is called after analyzing chunks without -p ioption (entropy -c)
 */
inline long double shannonEntropy(map<val_t,ulong>& occ, ulong size)
{
    static long double entropy = 0.0E0l; //Return value
    static std::pair<val_t,ulong> p; //Used in BOOST_FOREACH
    static long double prob; //The probability of a single char to occur (used as buffer)
    /**
     * Main loop: Calculates the entropy (must be negated before returning)
     */
    BOOST_FOREACH(p, occ)
    {
        prob = (long double)p.second/size;
        entropy += (long double)prob*log2(prob);
    }
    return (long double)-entropy;
}

#endif	/* _ENTROPY_ALGORITHMS_HPP */

