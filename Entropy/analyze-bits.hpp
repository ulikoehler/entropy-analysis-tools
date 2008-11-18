/* 
 * File:   analyze-bits.hpp
 * Author: uli
 *
 * Created on 16. November 2008, 18:17
 */


#ifndef _ANALYZE_BITS_HPP
#define	_ANALYZE_BITS_HPP

#include "globals.hpp"

/**
 * Counts the 1-bits in one file (does not take care of blocks)
 */
void analyzeBits (ifstream& f)
{
    buffer = new char[blocksize];
    ///Main read loop
    while(!f.eof ()) //bn = block number
        {
            f.read (buffer, blocksize);
            static int c = f.gcount ();
            if (c < blocksize)
                {
                    blocksize = c;
                }
            /** Chunk loop (iterates blocksize times)
              * Chunk0 is (blocksize << 3) - chunk1; <<3 multiplies by 8 (8 bits per byte)
              * global counters are increased by chunk counters
              */
            for (int i = 0; i < blocksize; i++)
                {
                    chunk1 += one_lookup8[(unsigned char) buffer[i]]; //Lookup table, 3 to 25 times faster than others
                }
            glob1 += chunk1;
            glob0 += (blocksize << 3) - chunk1; //Blocksize * 8 - glob1
            chunk1 = 0; //Zero chunk1 for next loop
        }
    f.close ();
    cout << "Overall statistics: 0:" << glob0 << " 1:" << glob1 << endl;
}

/**
 * Analyzes bits in blocks and prints them out into the statistics file
 */
void analyzeBitsPerBlock(ifstream& f, ofstream& of)
{
    /**
     * Print the header into the output stream
     */
    of << "\"Blocknum\"" << separator << "\"Bitcount\"\n";
    buffer = new char[blocksize];
    ///Main read loop
    for (uint bn = 1; !f.eof (); bn++) //bn = block number
        {
            f.read (buffer, blocksize);
            static int c = f.gcount ();
            if (c < blocksize)
                {
                    blocksize = c;
                }
            /**Chunk loop (iterates blocksize times)
             * Chunk0 is (blocksize << 3) - chunk1; <<3 multiplies by 8 (8 bits per byte)
             * global counters are increased by chunk counters
             */
            for (int i = 0; i < blocksize; i++)
                {
                    /**
                        Old algorithm:
                        Faster than checking if: (b[i] & (1<<n)) >=1 for each n: 0 < n < 8:
                            chunk1 += b[i] & 1
                                    + ((b[i] & (1<<1))>>1)
                                    + ((b[i] & (1<<2))>>2)
                                    + ((b[i] & (1<<3))>>3)
                                    + ((b[i] & (1<<4))>>4)
                                    + ((b[i] & (1<<5))>>5)
                                    + ((b[i] & (1<<6))>>6)
                                    + ((b[i] & (1<<7))>>7);
                     */
                    chunk1 += one_lookup8[(unsigned char) buffer[i]]; //Lookup table, 3 to 25 times faster than others
                }
            chunk0 = (blocksize << 3) - chunk1; //Blocksize * 8 - chunk 1
            //Print this block's statistics into statistics file
            of << bn << separator << chunk1 << "\n";
            glob0 += chunk0;
            glob1 += chunk1;
            chunk0 = 0;
            chunk1 = 0;
        }
    f.close();
    cout << "Written data to statistics file." << endl;
}

#endif	/* _ANALYZE_BITS_HPP */
