/* 
 * File:   output.hpp
 * Author: uli
 *
 * Created on 27. November 2008, 18:12
 *
 * Contains functions for printing out data
 */

#ifndef _OUTPUT_HPP
#define	_OUTPUT_HPP

#include "globals.hpp"

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
        of << ep.first << separator << format(ldFormatString) % ep.second << "\n";
    }
}


#endif	/* _OUTPUT_HPP */

