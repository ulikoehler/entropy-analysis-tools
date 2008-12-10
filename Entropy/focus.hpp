/* 
 * File:   focus.hpp
 * Author: uli
 *
 * Created on 10. Dezember 2008, 13:56
 *
 * Analyzator function looking at only one specified chunk value
 */

#ifndef _FOCUS_HPP
#define	_FOCUS_HPP

#include "globals.hpp"

/**
 * Template analyzator function
 */
template<class T>
ulong
chta (char* arg)
{
    ulong ctr = 0;
    for (i = 0; i < blocksize; i += sizeof (T))
        {
            if ((*(reinterpret_cast<T*> (arg))) == focus)
                {
                    ctr++;
                }
        }
    return ctr;
}

/**
 * Analyzes chunks but focuses on one target value
 * ignoring all other values
 */
inline void
analyzeChunksFocus (istream& f, ostream& of)
{
    boost::function < ulong (char*) > fa; //function analyze
    //Select the appropriate function
    switch (chunksize)
        {
        case 8:
            {
                fa = chta<uint8_t>;
                break;
            }
        case 16:
            {
                fa = chta<uint16_t>;
                break;
            }
        case 32:
            {
                fa = chta<uint32_t>;
                break;
            }
        default: //Not possible
            {
                cout << "Invalid chunk size for focus analysis!" << endl;
                exit (121);
                break;
            }
        }
    //TODO comment
    for (ulong blocknum = 1; f.good (); blocknum++)
        {
            f.read (buffer, blocksize);
            c = f.gcount ();
            if (c < blocksize)
                {
                    if (c == 0)
                        {
                            return;
                        }
                    /**
                     * Fill the rest of the buffer with the filling character
                     * (here blocksize is the length of the buffer array)
                     */
                    for (i = c; i < blocksize; i++)
                        {
                            buffer[i] = fillByte;
                        }
                    blocksize = c;
                }
            allOcc[blocknum] = fa (buffer);
            fa (buffer);

            /**
             * Write the data to the statistics file
             */

            BOOST_FOREACH (p, allOcc)
            {
                standardAcc (p.second);
                entropyWeightedAcc (p.second, weight = entropy);
                entropyRecipWeightedAcc (p.second, weight = (1 / entropy));
            }
        }

}
#endif	/* _FOCUS_HPP */

