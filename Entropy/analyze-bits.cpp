
#include "globals.hpp"

/**
 * Counts the 1-bits in one file (does not take care of blocks)
 */
void analyzeBits (ifstream& f)
{
    char* b = new char[blocksize];
    ///Main read loop
    for (!f.eof ()) //bn = block number
        {
            f.read (b, blocksize);
            static int c = f.gcount ();
            if (c < blocksize)
                {
                    blocksize = c;
                }
            ///Chunk loop (iterates blocksize times)
            //Chunk0 is (blocksize << 3) - chunk1; <<3 multiplies by 8 (8 bits per byte)
            //global counters are increased by chunk counters
            for (int i = 0; i < blocksize; i++)
                {
                    glob1 += one_lookup8[(unsigned char) b[i]]; //Lookup table, 3 to 25 times faster than others
                }
            glob0 += blocksize - glob1;
        }
    f.close ();
    cout << "Overall statistics: 0:" << glob0 << " 1:" << glob1 << endl;
}

/**
 * Analyzes bits in blocks and prints them out into the statistics file
 */
void analyzeBitsBlocks (ifstream& f, ofstream& of)
{
    char* b = new char[blocksize];
    ///Main read loop
    for (uint bn = 1; !f.eof (); bn++) //bn = block number
        {
            f.read (b, blocksize);
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
                    chunk1 += one_lookup8[(unsigned char) b[i]]; //Lookup table, 3 to 25 times faster than others
                }
            chunk0 = (blocksize << 3) - chunk1;
            //Print into stdout
            cout << "Block statistics: 0:" << chunk0 << " 1:" << chunk1 << endl;
            //Print this block's statistics into statistics file
            of << bn << "   " << chunk0 << endl;
            glob0 += chunk0;
            glob1 += chunk1;
            chunk0 = 0;
            chunk1 = 0;
        }
    f.close();
    cout << "Overall statistics: 0:" << glob0 << " 1:" << glob1 << endl;
}
