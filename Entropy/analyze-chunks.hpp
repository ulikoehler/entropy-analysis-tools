/* 
 * File:   analyze-chunks.hpp
 * Author: uli
 *
 * Created on 16. November 2008, 18:29
 */

#ifndef _ANALYZE_CHUNKS_HPP
#define	_ANALYZE_CHUNKS_HPP

#include "globals.hpp"

//Locally used typedefs
typedef unsigned long val_t;

static map<val_t, ulong> allOcc; // All occurrences
static map<val_t, ulong> localOcc;
static pair<val_t, ulong> p;

static int cpb;
static int i, j; //Iterators

/**
 * Writes the data from the supplied map to the supplied output stream
 * (See printStatistics for parameter description)
 * Called inside printStatistics to reduce code mass.
 * Template: template paramter for std::bitset
 */
template<int n>
void writeBinData(ostream& of, map<val_t, ulong>& occ, ulong blockNum = 0)
{
    if (blockNum)
            {
                BOOST_FOREACH (p, occ)
                {
                    of << "\"" << bitset < n > (p.first) << separator << p.second << separator << blockNum << "\n";
                }
            }
        else
            {
                BOOST_FOREACH (p, occ)
                {
                    of << "\"" << bitset < n > (p.first) << separator << p.second << "\n";
                }
            }
}

/**
 * Prints the statistics from the map into the output stream
 * Arguments:
 *      -std::ostream& of: Output stream to print statistics into
 *      -std::map<val_t,ulong>& occ: Map to get the statistics from
 *      -unsigned long blockNum: Block index (0 if disabled. Range starts with 1) 
 */
inline void
printStatistics (ostream& of, map<val_t, ulong>& occ, ulong blockNum = 0)
{
    /**
     * Write the header
     */
    if (blockNum)
        {
            if (!vm.count ("disable-header"))
                {
                    of << "\"Number\"" << separator << "\"Count\"" << separator << "\"Block\"\n";
                }
        }
    else
        {

            if (!vm.count ("disable-header"))
                {
                    of << "\"Number\"" << separator << "\"Count\"\n";
                }
        }
    /**
     * Write the data
     */
    if (vm.count ("decimal"))
        {
            if (blockNum)
                {

                    BOOST_FOREACH (p, occ)
                    {
                        of << "\"" << p.first << "\"" << separator << p.second << separator << blockNum << "\n";
                    }
                }
            else
                {

                    BOOST_FOREACH (p, occ)
                    {
                        of << "\"" << p.first << "\"" << separator << p.second << "\n";
                    }
                }
        }
    else
        {
            switch (chunksize)
                {
                case 2:
                    {
                        writeBinData<2>(of, occ, blockNum);
                        break;
                    }
                case 4:
                    {
                        writeBinData<4>(of, occ, blockNum);
                        break;
                    }
                case 8:
                    {
                        writeBinData<8>(of, occ, blockNum);
                        break;
                    }
                case 16:
                    {
                        writeBinData<16>(of, occ, blockNum);
                        break;
                    }
                case 32:
                    {
                        writeBinData<32>(of, occ, blockNum);
                        break;
                    }
                default:
                    {
                        writeBinData<64>(of, occ, blockNum);
                        break;
                    }
                }
        }
}
//Increments the map value

inline void
incVal (val_t n)
{
    //Increase the local counter map value
    if (allOcc.count (n) == 0)
        {
            allOcc[n] = 1;
        }
    else
        {
            allOcc[n]++;
        }
    //Increase the local counter map value
    if (localOcc.count (n) == 0)
        {
            localOcc[n] = 1;
        }
    else
        {
            localOcc[n]++;
        }
}

//Analyzes block for chunksize = 2

void
ch2a (char *b)
{ //Iterates through the block (one byte per iteration)
    for (i = 0; i < blocksize; i++)
        {
            //Build n
            static unsigned char j = b[i];
            incVal (j & 0x3); //3   = 00000011
            incVal (j & 0xc >> 2); //12  = 00001100
            incVal (j & 0x30 >> 4); //48  = 00110000
            incVal (j & 0xc0 >> 6); //192 = 11000000
        }
}

//Analyzes block for chunksize = 4

void
ch4a (char *b)
{ //Iterates through the block (one byte per iteration)
    for (i = 0; i < blocksize; i++)
        {
            //Build n
            //static unsigned char j = ;
            incVal (b[i] & 15); //15  = 00001111
            incVal (b[i] & 0xf0 >> 4); //240 = 11110000
        }
}

//Analyzes block for chunksize = 4

inline void
ch8a (char *b)
{ //Iterates through the block (one byte per iteration)
    for (i = 0; i < blocksize; i++)
        {
            incVal ((uint8_t) b[i]);
        }
}

///TODO: Does not work if filesize % blocksize != 0

inline void
ch16a (char *b)
{ //Iterates through the block (one byte per iteration)
    for (i = 0; i < blocksize; i += 2)
        {
            incVal ((uint8_t) b[i]+(uint8_t (b[i + 1]) << 8));
        }
}

//Analyzes block for chunksize = 24

inline void
ch24a (char *b)
{ //Iterates through the block (one byte per iteration)
    for (i = 0; i < blocksize; i += 3)
        {
            incVal ((uint8_t) b[i]+
                    ((uint8_t) (b[i + 1]) << 8)+
                    ((uint8_t) (b[i + 2] << 16)));
        }
}

//Analyzes block for chunksize = 24

inline void
ch32a (char *b)
{ //Iterates through the block (one byte per iteration)
    for (i = 0; i < blocksize; i += 4)
        {
            incVal ((uint8_t) b[i]+
                    ((uint8_t) (b[i + 1]) << 8)+
                    ((uint8_t) (b[i + 2] << 16))+
                    ((uint8_t) (b[i + 3] << 24)));
        }
}

//Analyzes block for chunksize n = 2^m > 8

inline void
chna (char* b)
{
    static val_t n;
    cpb = div (blocksize, chunksize).quot; //chunks per block
    //Iterates through the block
    for (i = 0; i < cpb; i++)
        {
            for (j = 0; j < chunksize; j++)
                {
                    n += b[i + j] << j;
                }
        }
}

inline void
analyzeChunks (ifstream& f, ofstream& of)
{
    char* b = new char[blocksize];
    boost::function<void(char* b) > fa; //function analyze
    //Select the appropriate function
    switch (chunksize)
        {
        case 1:
            {
                analyzeBitsBlocks (f, of);
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
    /**
     * Write the output csv file header if enabled
     */
    ///Main read-and-analyze loop
    if (perblock)
        {
            for (ulong blocknum = 1; !f.eof (); blocknum++)
                {
                    f.read (b, blocksize);
                    static int c = f.gcount ();
                    if (c < blocksize)
                        {
                            blocksize = c;
                        }
                    fa (b);
                    printStatistics (of, localOcc, blocknum);
                }

        }
    else
        {
            while (!f.eof ())
                {
                    f.read (b, blocksize);
                    static int c = f.gcount ();
                    if (c < blocksize)
                        {
                            blocksize = c;
                        }
                    fa (b);
                }
            printStatistics (of, allOcc);
        }
    /**
     * Write the acquired data to the output file
     * Iterates over all elements
     * and write the data to the output file
     */
    cout << "Written data to statistics file." << endl;
}

#endif	/* _ANALYZE_CHUNKS_HPP */

