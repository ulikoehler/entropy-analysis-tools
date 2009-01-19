/* 
 * File:   random.hpp
 * Author: uli
 *
 * Created on 19. Januar 2009, 16:10
 */
#include "globals.hpp"

#ifndef _RANDOM_HPP
#define	_RANDOM_HPP

void randomMain(int argc, char** argv)
{
    if (!(argc==2))
        {
            printf("Syntax: %s rand <size> <file>");
            exit(1);
        }
    string sizeString = argv[2];
    int len = sizeString.length ();
    ulong size;
    int factor = 1;
    //Check if the user supplied a factor like k (kilo) or M (Mega).
    char suffix = sizeString[size-1];
    if(suffix == 'k') factor = 1024;
    else if(suffix == 'M') factor = 1024*1024;
    size = lexical_cast<ulong>(sizeString.substr (0,len-1))*factor;
    AutoSeeded_RNG rng;
}

#endif	/* _RANDOM_HPP */

