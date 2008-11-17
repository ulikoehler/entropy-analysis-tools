/* 
 * File:   analyze-chunks.hpp
 * Author: uli
 *
 * Created on 16. November 2008, 18:29
 */


#ifndef _ANALYZE_CHUNKS_HPP
#define	_ANALYZE_CHUNKS_HPP

#include "globals.hpp"

static map<val_t,ulong> occ; // All occurrences

static int cpb;
static int i,j; //Iterators

val_t n;
//Increments the map value
inline void incVal(val_t n)
{
    if (occ.count(n) == 0)
    {
        occ[n] = 1;
    }
    else
    {
        occ[n]++;
    }
}

//Analyzes block for chunksize = 2
void ch2a(char *b)
{    //Iterates through the block (one byte per iteration)
    for (i = 0; i < blocksize; i++)
    {
        //Build n
        static unsigned char j = b[i];
        incVal(j & 0x3);  //3   = 00000011
        incVal(j & 0xc >> 2);  //12  = 00001100
        incVal(j & 0x30 >> 4); //48  = 00110000
        incVal(j & 0xc0 >> 6); //192 = 11000000
    }
}

//Analyzes block for chunksize = 4
void ch4a(char *b)
{    //Iterates through the block (one byte per iteration)
    for (i = 0; i < blocksize; i++)
    {
        //Build n
        //static unsigned char j = ;
        incVal(b[i] & 15);  //15  = 00001111
        incVal(b[i] & 0xf0 >> 4); //240 = 11110000
    }
}

//Analyzes block for chunksize = 4
void ch8a(char *b)
{    //Iterates through the block (one byte per iteration)
    for (i = 0; i < blocksize; i++)
    {
        incVal((uint8_t)b[i]);
    }
}

///TODO: Does not work if filesize % blocksize != 0
void ch16a(char *b)
{    //Iterates through the block (one byte per iteration)
    for (i = 0; i < blocksize; i += 2)
    {
        incVal((uint8_t)b[i]+(uint8_t(b[i+1])<<8));
    }
}

//Analyzes block for chunksize = 24
void ch24a(char *b)
{    //Iterates through the block (one byte per iteration)
    for (i = 0; i < blocksize; i += 3)
    {
        incVal((uint8_t)b[i]+
                ((uint8_t)(b[i+1])<<8)+
                  ((uint8_t)(b[i+2]<<16)));
    }
}

//Analyzes block for chunksize = 24
void ch32a(char *b)
{    //Iterates through the block (one byte per iteration)
    for (i = 0; i < blocksize; i += 4)
    {
        incVal((uint8_t)b[i]+
                ((uint8_t)(b[i+1])<<8)+
                  ((uint8_t)(b[i+2]<<16))+
                  ((uint8_t)(b[i+3]<<24)));
    }
}

//Analyzes block for chunksize n = 2^m > 8
void chna(char* b)
{
    cpb = div(blocksize, chunksize).quot; //chunks per block
    //Iterates through the block
    for (i = 0; i < cpb; i++)
    {
        for (j = 0; j < chunksize; j++)
        {
            n += b[i+j]<<j;
        }
    }
}

void analyzeChunks(ifstream& f, ofstream& of)
{
    char* b = new char[blocksize];
    boost::function<void(char* b)> fa; //function analyze
    //Select the appropriate function
    switch (chunksize)
    {
        case 1:
            {
                analyzeBitsBlocks(f,of);
                return;
            }
        case 2:
            {
                fa = ch2a;
                break;
            }
        case 4:
            {
                fa = ch4a;
                break;
            }
        case 8:
            {
                fa = ch8a;
                break;
            }
        case 16:
            {
                fa = ch16a;
                break;
            }
        default:
            {
                fa = chna;
                break;
            }
    }
    ///Main read and analyze loop
    while (!f.eof())
    {
        f.read(b, blocksize);
        static int c = f.gcount();
        if (c < blocksize)
        {
            blocksize = c;
        }
        fa(b);

    }
    ///Write the acquired data to the output file
    //Iterates over all elements
    //and write the data to the output file
    pair<val_t,ulong> p;
    if(vm.count("decimal"))
    {
        BOOST_FOREACH(p, occ)
        {
            of << p.first << "  " << p.second << endl;
        }
    }
    else
    {
        switch (chunksize)
        {
            case 2:
                {
                    BOOST_FOREACH(p, occ)
                    {
                        of << bitset<2>(p.first) << "  " << p.second << endl;
                    }
                    break;
                }
            case 4:
                {
                    BOOST_FOREACH(p, occ)
                    {
                        of << bitset<4>(p.first) << "  " << p.second << endl;
                    }
                    break;
                }
            case 8:
                {
                    BOOST_FOREACH(p, occ)
                    {
                        of << bitset<8>(p.first) << "  " << p.second << endl;
                    }
                    break;
                }
            case 16:
                {
                    BOOST_FOREACH(p, occ)
                    {
                        of << bitset<16>(p.first) << "  " << p.second << endl;
                    }
                    break;
                }
            case 32:
                {
                    BOOST_FOREACH(p, occ)
                    {
                        of << bitset<32>(p.first) << "  " << p.second << endl;
                    }
                    break;
                }
        }
    }
    cout << "Written data to statistics file." << endl;
}

#endif	/* _ANALYZE_CHUNKS_HPP */

