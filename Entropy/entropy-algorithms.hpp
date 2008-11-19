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
 * Calculates entropy of a given filled map using Shannon's algorithm
 * Is called after analyzing chunks without -p ioption (entropy -c)
 */
inline long double shannonEntropy(map<val_t,ulong>& occ,ulong filesize)
{
    static long double entropy = 0.0; //Return value
    static std::pair<val_t,ulong> p; //Used in BOOST_FOREACH
    static long double prob; //The probability of a single char to occur (used as buffer)
    /**
     * Main loop: Calculates the Shannon Entropy
     */
    BOOST_FOREACH(p, occ)
    {
        prob = (long double)p.second/filesize;
        entropy += (long double)prob*log2(prob);
    }
    return (long double)-entropy;
}

#endif	/* _ENTROPY_ALGORITHMS_HPP */

