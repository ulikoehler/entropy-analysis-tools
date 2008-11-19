/* 
 * File:   analyze-binary.hpp
 * Author: uli
 *
 * Created on 19. November 2008, 01:10
 */

#ifndef _ACTIONS_HPP
#define	_ACTIONS_HPP

#include "globals.hpp"

int
analyzeBinaryFile (ifstream& f, ofstream& of)
{
    perblock = vm.count ("per-block"); //Behaves like a boolean, also consumes only one byte

    //Initalize the buffer array
    buffer = new char[blocksize];
    //Call the appropriate analysator function
    if (vm.count ("chunks"))
        {
            //Validate chunk size
            if (blocksize % chunksize != 0)
                {
                    cout << "Blocksize must be a multiple of chunksize!\n";
                    return 3;
                }
            analyzeChunks (f, of);
        }
        //Count bits
    else
        {
            //Count bits; per block
            if (perblock)
                {
                    analyzeBitsPerBlock (f, of);
                }
                //Count bits (no blocks)
            else
                {
                    analyzeBits (f);
                }
        }

    //Delete the buffer array
    delete buffer;
    return 0;
}

/**
 * TODO
 */
int
analyzeNumericFile (ifstream& f, ofstream& of)
{
    return 0;
}

#endif	/* _ANALYZE_BINARY_HPP */

