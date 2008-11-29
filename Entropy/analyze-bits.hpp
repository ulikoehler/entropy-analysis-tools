/* 
 * File:   analyze-bits.hpp
 * Author: uli
 *
 * Created on 16. November 2008, 18:17
 */


#ifndef _ANALYZE_BITS_HPP
#define	_ANALYZE_BITS_HPP

#include "globals.hpp"

static ull glob0 = 0;
static ull glob1 = 0;
static ull chunk0 = 0;
static ull chunk1 = 0;

/**
 * Counts the 1-bits in one file (does not take care of blocks)
 */
void
analyzeBits (ifstream& f)
{
    buffer = new char[blocksize];
    static ulong filesize;
    ///Main read loop
    while (!f.eof ()) //bn = block number
        {
            f.read (buffer, blocksize);
            c = f.gcount ();
            if (c < blocksize)
                {
                    blocksize = c;
                }
            filesize += blocksize;
            /** Chunk loop (iterates blocksize times)
             * Chunk0 is (blocksize << 3) - chunk1; <<3 multiplies by 8 (8 bits per byte)
             * global counters are increased by chunk counters
             */
            for (i = 0; i < blocksize; i++)
                {
                    chunk1 += one_lookup8[(unsigned char) buffer[i]]; //Lookup table, 3 to 25 times faster than others
                }
            glob1 += chunk1;
            glob0 += (blocksize << 3) - chunk1; //Blocksize * 8 - glob1
            chunk1 = 0; //Zero chunk1 for next loop
        }
    f.close ();
    cout << "Overall statistics: 0:" << glob0 << " 1:" << glob1 << endl;
    cout << "Shannon entropy: " << format(ldFormatString) % shannonEntropy(glob0, glob1, filesize) << "\n";
}

/**
 * Analyzes bits in blocks and prints them out into the statistics file
 */
void
analyzeBitsPerBlock (istream& f, ostream& of)
{
    /**
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

    static accumulator_set<ull, features<
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

    static accumulator_set<ull, features<
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

    static accumulator_set<ull, features<
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
    /**
     * Print the header into the output stream
     */
    of << "\"Blocknum\"" << separator << "\"Bitcount\"\n";
    buffer = new char[blocksize];
    ///Main read loop
    for (ulong blocknum = 1; !f.eof (); blocknum++) //bn = block number
        {
            f.read (buffer, blocksize);
            c = f.gcount ();
            if (c < blocksize)
                {
                    if(c == 0){break;}
                    blocksize = c;
                }
            /**Chunk loop (iterates blocksize times)
             * Chunk0 is (blocksize << 3) - chunk1; << 3 multiplies by 8 (8 bits per byte)
             * global counters are increased by chunk counters
             */
            for (i = 0; i < blocksize; i++)
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
            of << blocknum << separator << chunk1 << "\n";
            glob0 += chunk0;
            glob1 += chunk1;
            chunk0 = 0;
            chunk1 = 0;

            //Add the values to the accumulators (zeroes are used here)
            static long double entropy = 0;
            entropy = shannonEntropy(glob0, glob1, blocksize);
            entropyAcc(entropy);
            standardAcc(glob0);
            entropyWeightedAcc(glob0, weight = entropy);
            entropyRecipWeightedAcc(glob1, weight = (1/entropy));
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
    
    cout << "Written data to statistics file." << endl;
}

#endif	/* _ANALYZE_BITS_HPP */

