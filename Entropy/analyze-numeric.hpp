/* 
 * File:   analyze-numeric.hpp
 * Author: uli
 *
 * Created on 12. Dezember 2008, 18:56
 */

#ifndef _ANALYZE_NUMERIC_HPP
#define	_ANALYZE_NUMERIC_HPP

#include "globals.hpp"
#include "output.hpp"

//Forward declarations
template<class T> void analyzeNumericData (istream& fin, ostream& fout);

/**
 * Top-level numeric analysis function: Determinates what type to use and
 * calls the main analyzator function with the appropriate tmeplate argument
 */

void
analyzeNumeric (istream& fin, ostream& fout)
{
    if (vm.count ("long")) //Long
        {
            analyzeNumericData<long>(fin, fout);
        }
    else //(vm.count("ld")) //Long double
        {
            analyzeNumericData<long double>(fin, fout);
        }
}

/**
 * Rounds a value to a arbitrary number of decimal digits.
 * Contains only one function, template class is overridden for types with specific functions
 */
template<class T>
class _round
{
public:

    static inline T
    roundArb (T num, ushort n)
    {
        static T log = log10 (num);
        static T pw; //Power
        if (num > 0)
            {
                log = ceil (log);
            }
        else
            {
                log = floor (log);
            }
        pw = -(log - n);
        return (int) ((num * pow ((T) 10.0L, pw) + 0.5) * pow ((T) 10.0L, -pw));
    }
};

template<>
class _round<long double>
{
public:

    static inline long double
    roundArb (long num, ushort n)
    {
        static long double log = log10 (num);
        static long double pw; //Power
        if (num > 0)
            {
                log = ceil (log);
            }
        else
            {
                log = floor (log);
            }
        pw = -(log - n);
        return (long double) (num * pow (10, pw) + 0.5) * pow (10, -pw);
    }
};

template<>
class _round<long>
{
public:

    static inline long
    roundArb (long num, ushort n)
    {
        static double log = log10 (num);
        static long pw; //Power
        if (num > 0)
            {
                log = ceil (log);
            }
        else
            {
                log = floor (log);
            }
        pw = -(log - n);
        return (long) (num * pow (10, pw) + 0.5) * pow (10, -pw);
    }
};

/**
 * Main numeric analyzator function
 */
template<class T>
void
analyzeNumericData (istream& fin, ostream& fout)
{
    static accumulator_set<T, features<
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
            >, void > accumulator;

    map<T, ulong> data;
    pair<T, ulong> dataPair;
    /**
     * Read the data from the file and process it
     */
    static string bufferString;
    static T buffer;
    while (fin.good ())
        {
            fin >> bufferString;
            buffer = lexical_cast<T > (bufferString);
            accumulator (buffer);
            /**
             * Round the value to the specified resolution
             * (res digits after the decimal point
             *   s.find(...) points at the character before the decimal point,
             *   so s.find(...) + 1 points at the decimal point character
             * )
             */
            static T rounded = lexical_cast<T > (bufferString.substr (0, bufferString.find (".") + 1 + res));
            if (data.count (rounded) == 0)
                {
                    data[rounded] = 1;
                }
            else
                {
                    data[rounded]++;
                }
        }

    /**
     * Write the data from the map to the output file
     */
    BOOST_FOREACH (dataPair, data)
    {
        fout << dataPair.first << separator << dataPair.second << "\n";
    }
    cout << "Written data to statistics file\n";
    /**
     * Print out the statistical indicators
     */
    static long double variance = 0;
    variance = extract::variance (accumulator);
    cout << "Statistical indicators:\n";
    cout << "   Count: " << extract::count (accumulator) << "\n";
    cout << "   Min: " << extract::min (accumulator) << "\n";
    cout << "   Max: " << extract::max (accumulator) << "\n";
    cout << "   Mean: " << format (ldFormatString) % extract::mean (accumulator) << "\n";
    cout << "   Sum: " << format (ldFormatString) % extract::sum (accumulator) << "\n";
    cout << "   Momentum (2): " << format (ldFormatString) % extract::moment < 2 > (accumulator) << "\n";
    cout << "   Momentum (3): " << format (ldFormatString) % extract::moment < 3 > (accumulator) << "\n";
    cout << "   Variance: " << format (ldFormatString) % variance << "\n";
    cout << "   Standard deviation: " << format (ldFormatString) % sqrt (variance) << "\n";
    cout << "   Skewness: " << format (ldFormatString) % extract::skewness (accumulator) << "\n";
}

#endif	/* _ANALYZE_NUMERIC_HPP */

