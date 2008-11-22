/* 
 * File:   analyze-chunks.hpp
 * Author: uli
 *
 * Created on 16. November 2008, 18:29
 */

#ifndef _ANALYZE_CHUNKS_HPP
#define	_ANALYZE_CHUNKS_HPP

#include "globals.hpp"

/**
 * All occurrences map:
 * Maps a binary string ("chunk") represented as a number
 * to the count of occurrences of this number
 * With -p:
 *      Cleared after each block
 */
static map<val_t, ulong> allOcc; // All occurrences

static pair<val_t,ulong> p;

static int cpb;
static int i, j; //Iterators

/**
 * Writes the data from the supplied map to the supplied output stream
 * (See printStatistics for parameter description)
 * Called inside printStatistics to reduce code mass.
 * Template: template paramter for std::bitset
 */
template<int n>
void
writeBinData (ostream& of, map<val_t, ulong>& occ, ulong blockNum = 0)
{
    if (blockNum)
        {

            BOOST_FOREACH (p, occ)
            {
                of << "\"" << bitset < n > (p.first) << "\"" << separator << p.second << separator << blockNum << "\n";
            }
        }
    else
        {

            BOOST_FOREACH (p, occ)
            {
                of << "\"" << bitset < n > (p.first) << "\"" << separator << p.second << "\n";
            }
        }
}

/**
 * Prints a long double value (into stdout)
 */
inline void
pld (long double val)
{
    printf ("%Lf\n", val);
}

/**
 * Prints the header into the supplied output stream
 * (for 3-column output)
 */
inline
void
printChunksHeader (ostream& of, bool perblock)
{
    /**
     * Write the header
     */
    if (perblock)
        {
            if (!vm.count ("disable-header"))
                {
                    of << "\"Number\"" << separator << "\"Count\"" << separator << "\"Block\n";
                }
        }
    else
        {

            if (!vm.count ("disable-header"))
                {
                    of << "\"Number\"" << separator << "\"Count\"\n";
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
print3ColumnStatistics (ostream& of, map<val_t, ulong>& occ, ulong blockNum = 0)
{
    /**
     * Write the data
     */
    if (vm.count ("decimal"))
        {
            if (blockNum)
                {

                    BOOST_FOREACH (p, occ)
                    {
                        of << p.first << separator << p.second << separator << blockNum << "\n";
                    }
                }
            else
                {

                    BOOST_FOREACH (p, occ)
                    {
                        of << p.first << separator << p.second << "\n";
                    }
                }
        }
    else
        {
            switch (chunksize)
                {
                case 2:
                    {
                        writeBinData < 2 > (of, occ, blockNum);
                        break;
                    }
                case 4:
                    {
                        writeBinData < 4 > (of, occ, blockNum);
                        break;
                    }
                case 8:
                    {
                        writeBinData < 8 > (of, occ, blockNum);
                        break;
                    }
                case 16:
                    {
                        writeBinData < 16 > (of, occ, blockNum);
                        break;
                    }
                case 32:
                    {
                        writeBinData < 32 > (of, occ, blockNum);
                        break;
                    }
                default:
                    {
                        writeBinData < 64 > (of, occ, blockNum);
                        break;
                    }
                }
        }
}

inline void
printEntropyStatistics (ostream& of, map<ulong, long double>& entropies)
{
    static pair<ulong, long double> ep; //ep = entropy pair

    BOOST_FOREACH (ep, entropies)
    {
        /**
         * p.first = blockNum; p.second = shannonEntropy(blockNum)
         */
        of << ep.first << separator << ep.second << "\n";
    }
}

/**
 * Increments the map value associated with the specified key
 */
inline void
incVal (val_t n)
{
    //Increase the global counter map at index n
    if (allOcc.count (n) == 0)
        {
            allOcc[n] = 1;
        }
    else
        {
            allOcc[n]++;
        }
}

/**
 * Analyzes block for chunksize = 2
 */
void
ch2a (char *b)
{ //Iterates through the block (one byte per iteration)
    for (i = 0; i < blocksize; i++)
        {
            //Build n
            incVal ((unsigned char) b[i] & 3); //3   = 00000011
            incVal (((unsigned char) b[i] & (3 << 2)) >> 2); //12  = 00001100
            incVal (((unsigned char) b[i] & (3 << 4)) >> 4); //48  = 00110000
            incVal (((unsigned char) b[i] & (3 << 6)) >> 6); //192 = 11000000
        }
}

//Analyzes block for chunksize = 4

void
ch4a (char *b)
{ //Iterates through the block (one byte per iteration)
    for (i = 0; i < blocksize; i++)
        {
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
            incVal ((uint8_t) b[i]
                    +((uint8_t) (b[i + 1]) << 8)
                    +((uint8_t) (b[i + 2] << 16))
                    +((uint8_t) (b[i + 3] << 24)));
        }
}

/**
 * Analyzes block for chunksize n = 2^m > 8
 */
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

/**
 * Main chunk analyzator function
 */
inline void
analyzeChunks (istream& f, ostream& of)
{
    static ulong filesize = 0; //Blocksize is added to this each iteration
    boost::function<void(char* b) > fa; //function analyze
    //Select the appropriate function
    switch (chunksize)
        {
        case 1:
            {
                analyzeBitsPerBlock (f, of);
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
     * Declare the accumulator set used to perform a statistical analysis on the data
     * The standard deviation is calculated directly from the variance (sqrt(variance))
     */
    accumulator_set<long double, features<//Standard algebra
                                        tag::min,
                                        tag::max,
                                        tag::sum,
                                        //Statistics
                                        tag::variance,
                                        tag::mean,
                                        //Probability theory (of random variable
                                        tag::skewness
                                             > > acc;
    /**
     * Main loop: analyzes data and stores results in the map
     */
    if (vm.count ("entropy"))
        {
            /**
             * Write the CSV header
             */
            of << "\"Blocknum\"" << separator << "\"Entropy\"\n";
            /**
             * The same as the next (perblock), but calculates Shannon entropy for each block
             * allOcc is misused here and cleared every block round
             * The Shannon entropy associated with the block number is stored in the entropies local map
             */
            static map<ulong, long double> entropies;
            for (ulong blocknum = 1; f.good (); blocknum++)
                {
                    f.read (buffer, blocksize);
                    static int c = f.gcount ();
                    if (c < blocksize)
                        {
                            /**
                             * Fill the rest of the buffer with the filling character
                             * (here blocksize is the length of the buffer array)
                             */
                            for(int i = c;i < blocksize;i++)
                                {
                                    buffer[i] = fillByte;
                                }
                            /**
                             * For other functions using blocksize:
                             * Set it to the maximum size usable without errors
                             */ 
                            blocksize = c;
                        }
                    fa (buffer);
                    static long double entropy = shannonEntropy (allOcc, blocksize);
                    acc(entropy);
                    entropies.insert (pair<ulong, long double>(blocknum, entropy));
                    allOcc.clear();
                }
            /**
             * Write the statistics into the statistics file
             */
            printEntropyStatistics (of, entropies);
            /**
             * Print out the indicators (gathered from acc)
             */
            cout << "Statistical indicators:\n";
            cout << "Min: " << extract::min(acc) << "\n";
            cout << "Max: " << extract::max(acc) << "\n";
            cout << "Mean: " << extract::mean(acc) << "\n";
            cout << "Variance: " << extract::variance(acc) << "\n";
            cout << "Skewness: " << extract::skewness(acc) << "\n";
        }
    else if (perblock)
        {
            /**
             * Write the CSV header
             */
            printChunksHeader (of, perblock);
            /**
             * allOcc is misused here and cleared every block round
             */
            for (ulong blocknum = 1; f.good (); blocknum++)
                {
                    f.read (buffer, blocksize);
                    static int c = f.gcount ();
                    if (c < blocksize)
                        {
                            blocksize = c;
                        }
                    fa (buffer);
                    print3ColumnStatistics (of, allOcc, blocknum); //Write this block's data to the output file
                    allOcc.clear ();
                }

        }
    else
        {
            /**
             * Write the CSV header
             */
            printChunksHeader (of, perblock);
            /**
             * This block analyzes the chunks in the entire file.
             */
            while (!f.eof ())
                {
                    f.read (buffer, blocksize);
                    static int c = f.gcount ();
                    if (c < blocksize)
                        {
                            blocksize = c;
                        }
                    fa (buffer);
                    filesize += blocksize; //Count the filesize;
                }
            /**
             * Write the acquired data to the output file
             * Iterates over all elements
             * and write the data to the output file
             */
            print3ColumnStatistics (of, allOcc);
            /**
             * Calculate the Shannon entropy of the entire file and print it into stdout
             */
            cout << "Shannon Entropy: ";
            pld (shannonEntropy (allOcc, filesize));
            cout << endl;
        }
    /**
     * Print a success message
     */
    cout << "Written data to statistics file.\n" << endl;

}

#endif	/* _ANALYZE_CHUNKS_HPP */

