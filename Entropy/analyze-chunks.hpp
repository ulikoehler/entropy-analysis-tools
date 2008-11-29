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
 * Macros
 */

/**
 * All occurrences map:
 * Maps a binary string ("chunk") represented as a number
 * to the count of occurrences of this number
 * With -p:
 *      Cleared after each block
 */

static uint cpb; //chunks per block

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
    cpb = (long)blocksize/chunksize; //chunks per block
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
{    /**
     * Declare the accumulator sets used to perform a statistical analysis on the data
     * The standard deviation is calculated directly from the variance (sqrt(variance))
     * standardAcc = unweighted
     * entropyAcc = weighted by entropy
     * entropyRecipAcc = weighted by entropy reciprocal
     *
     * These are used only once per program call so there is no need to reset
     * In analyze-bits.hpp the sets are used with ulong as data type.
     */
    static accumulator_set<long double, features<
            //Standard algebra
            tag::count,
            tag::min,
            tag::max,
            tag::sum,
            tag::mean,
            //Statistics
            tag::variance,
            tag::moment < 2 >,
            tag::moment < 3 >,
            tag::skewness
            >, void > entropyAcc;

    static accumulator_set<long double, features<
            //Standard algebra
            tag::count,
            tag::min,
            tag::max,
            tag::sum,
            tag::mean,
            //Statistics
            tag::variance,
            tag::moment < 2 >,
            tag::moment < 3 >,
            tag::skewness
            >, void > standardAcc;

    static accumulator_set<long double, features<
            //Standard algebra
            tag::count,
            tag::weighted_sum,
            //Statistics
            tag::weighted_mean,
            tag::weighted_moment < 2 >,
            tag::weighted_moment < 3 >,
            tag::weighted_variance,
            tag::weighted_skewness
            >, long double> entropyWeightedAcc;

    static accumulator_set<long double, features<
            //Standard algebra
            tag::count,
            tag::weighted_sum,
            //Statistics
            tag::weighted_mean,
            tag::weighted_moment < 2 >,
            tag::weighted_moment < 3 >,
            tag::weighted_variance,
            tag::weighted_skewness
            >, long double> entropyRecipWeightedAcc;
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
    //Accumulator sets are declared in globals.hpp

    /**
     * Main loop: analyzes data and stores results in the map
     */
    static map<ulong, long double> entropies;
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
            for (ulong blocknum = 1; f.good (); blocknum++)
                {
                    f.read (buffer, blocksize);
                    c = f.gcount ();
                    if (c < blocksize)
                        {
                          if(c == 0){return;}
                            /**
                             * Fill the rest of the buffer with the filling character
                             * (here blocksize is the length of the buffer array)
                             */
                            //TODO apply for all analyzator functions
                            for (i = c; i < blocksize; i++)
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
                    static long double entropy = 0;
                    entropy = shannonEntropy (allOcc, blocksize); //Buffered
                    entropies.insert(pair<ulong, long double>(blocknum, entropy));
                    entropyAcc(entropy);
                    allOcc.clear ();
                }
            /**
             * Write the statistics into the statistics file
             */
            printEntropyStatistics (of, entropies);

            static long double variance = 0;
            variance = extract::variance (entropyAcc);
            cout << "Statistical indicators:\n";
            cout << "   Count: " << extract::count (entropyAcc) << "\n";
            cout << "   Min: " << extract::min (entropyAcc) << "\n";
            cout << "   Max: " << extract::max (entropyAcc) << "\n";
            cout << "   Mean: " << format (ldFormatString) % extract::mean (entropyAcc) << "\n";
            cout << "   Sum: " << format (ldFormatString) % extract::sum (entropyAcc) << "\n";
            cout << "   Momentum (2): " << format (ldFormatString) % extract::moment < 2 > (entropyAcc) << "\n";
            cout << "   Momentum (3): " << format (ldFormatString) % extract::moment < 3 > (entropyAcc) << "\n";
            cout << "   Variance: " << format (ldFormatString) % variance << "\n";
            cout << "   Standard deviation: " << format (ldFormatString) % sqrt(variance) << "\n";
            cout << "   Skewness: " << format (ldFormatString) % extract::skewness (entropyAcc) << "\n";
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
                    c = f.gcount ();
                    if (c < blocksize)
                        {
                            if(c == 0){return;}
                            blocksize = c;
                        }
                    fa (buffer);
                    print3ColumnStatistics (of, allOcc, blocknum); //Write this block's data to the output file
                    //Update statistical accumulators
                    static long double entropy = shannonEntropy (allOcc, blocksize); //Buffered
                    entropies.insert (pair<ulong, long double>(blocknum, entropy));
                    BOOST_FOREACH (p, allOcc)
                    {
                        standardAcc (p.second);
                        entropyWeightedAcc (p.second, weight = entropy);
                        entropyRecipWeightedAcc (p.second, weight = (1 / entropy));
                    }
                    //Clear the map
                    allOcc.clear ();
                }
            /**
             * Print out the statistical indiciators
             */
            static long double variance = 0;
            variance = extract::variance (entropyAcc); //Used in variance and std deviation
            cout << "Entropy indicators:\n";
            cout << "   Count: " << extract::count (entropyAcc) << "\n";
            cout << "   Min: " << extract::min (entropyAcc) << "\n";
            cout << "   Max: " << extract::max (entropyAcc) << "\n";
            cout << "   Mean: " << format (ldFormatString) % extract::mean (entropyAcc) << "\n";
            cout << "   Sum: " << format (ldFormatString) % extract::sum (entropyAcc) << "\n";
            cout << "   Momentum (2): " << format (ldFormatString) % extract::moment < 2 > (entropyAcc) << "\n";
            cout << "   Momentum (3): " << format (ldFormatString) % extract::moment < 3 > (entropyAcc) << "\n";
            cout << "   Variance: " << format (ldFormatString) % variance << "\n";
            cout << "   Standard deviation: " << format (ldFormatString) % sqrt (variance) << "\n";
            cout << "   Skewness: " << format (ldFormatString) % extract::skewness (entropyAcc) << "\n";

            variance = extract::variance (standardAcc); //Used in variance and std deviation
            cout << "Statistical indicators (unweighted):\n";
            cout << "   Count: " << extract::count (standardAcc) << "\n";
            cout << "   Min: " << extract::min (standardAcc) << "\n";
            cout << "   Max: " << extract::max (standardAcc) << "\n";
            cout << "   Mean: " << format (ldFormatString) % extract::mean (standardAcc) << "\n";
            cout << "   Sum: " << format (ldFormatString) % extract::sum (standardAcc) << "\n";
            cout << "   Momentum (2): " << format (ldFormatString) % extract::moment < 2 > (standardAcc) << "\n";
            cout << "   Momentum (3): " << format (ldFormatString) % extract::moment < 3 > (standardAcc) << "\n";
            cout << "   Variance: " << format (ldFormatString) % variance << "\n";
            cout << "   Standard deviation: " << format (ldFormatString) % sqrt (variance) << "\n";
            cout << "   Skewness: " << format (ldFormatString) % extract::skewness (standardAcc) << "\n";

            variance = extract::weighted_variance (entropyWeightedAcc);
            cout << "Statistical indicators (weighted by entropy):\n";
            cout << "   Sum: " << format (ldFormatString) % extract::weighted_sum (entropyWeightedAcc) << "\n";
            cout << "   Mean: " << format (ldFormatString) % extract::weighted_mean (entropyWeightedAcc) << "\n";
            cout << "   Momentum (2): " << format (ldFormatString) % extract::weighted_moment < 2 > (entropyWeightedAcc) << "\n";
            cout << "   Momentum (3): " << format (ldFormatString) % extract::weighted_moment < 3 > (entropyWeightedAcc) << "\n";
            cout << "   Variance: " << format (ldFormatString) % variance << "\n";
            cout << "   Standard deviation: " << format (ldFormatString) % sqrt (variance) << "\n";
            cout << "   Skewness: " << format (ldFormatString) % extract::weighted_skewness (entropyWeightedAcc) << "\n";

            variance = extract::weighted_variance (entropyRecipWeightedAcc);
            cout << "Statistical indicators (weighted by entropy reciprocal):\n";
            cout << "   Sum: " << format (ldFormatString) % extract::weighted_sum (entropyRecipWeightedAcc) << "\n";
            cout << "   Mean: " << format (ldFormatString) % extract::weighted_mean (entropyRecipWeightedAcc) << "\n";
            cout << "   Momentum (2): " << format (ldFormatString) % extract::weighted_moment < 2 > (entropyRecipWeightedAcc) << "\n";
            cout << "   Momentum (3): " << format (ldFormatString) % extract::weighted_moment < 3 > (entropyRecipWeightedAcc) << "\n";
            cout << "   Variance: " << format (ldFormatString) % variance << "\n";
            cout << "   Standard deviation: " << format (ldFormatString) % sqrt (variance) << "\n";
            cout << "   Skewness: " << format (ldFormatString) % extract::weighted_skewness (entropyRecipWeightedAcc) << "\n";
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
                    c = f.gcount ();
                    if (c < blocksize)
                        {
                            if(c == 0){return;}
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
            cout << "Shannon Entropy: " << format (ldFormatString) % shannonEntropy (allOcc, filesize) << "\n";
        }
    /**
     * Print a success message
     */
    cout << "Written data to statistics file.\n" << endl;

}

#endif	/* _ANALYZE_CHUNKS_HPP */
