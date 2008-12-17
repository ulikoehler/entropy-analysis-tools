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

/**
 * Global variables used only in this file
 */
static string resString;

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
    else if (vm.count ("int")) //Int
        {
            analyzeNumericData<int>(fin, fout);
        }
    else if (vm.count ("uint")) //Long
        {
            analyzeNumericData<uint>(fin, fout);
        }
    else if (vm.count ("llong")) //Long long
        {
            analyzeNumericData<long long>(fin, fout);
        }
    else if (vm.count ("ullong")) //Unsigned long long
        {
            analyzeNumericData<unsigned long long>(fin, fout);
        }
    else if (vm.count ("float")) //float
        {
            analyzeNumericData<float>(fin, fout);
        }
    else if (vm.count ("double")) //Long
        {
            analyzeNumericData<double>(fin, fout);
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
inline long double
around (long double n, unsigned e)
{
    return floor (n * pow (10., e) + .5) / pow (10., e);
}
//Manual overrides
inline double
around (double n, unsigned e)
{
    return floor (n * pow (10., e) + .5) / pow (10., e);
}
inline float
around (float n, unsigned e)
{
    return floor (n * pow (10., e) + .5) / pow (10., e);
}

/**
 * Prepares a value for storing in the map as a key
 * Returns either a rounded value or the input itself depending on
 * the template-supplied type
 */
template<class T>
class _prepVal
{
public:
    static inline T
    prepVal (T in)
    {
        return in;
    }
};
//Overrides

template<> class _prepVal<double>
{
public:

    static inline double
    prepVal (double in)
    {
        return around (in, res);
    }
};

template<> class _prepVal<long double>
{
public:

    static inline long double
    prepVal (long double in)
    {
        return around (in, res);
    }
};

template<> class _prepVal<float>
{
public:

    static inline float
    prepVal (float in)
    {
        return around (in, res);
    }
};

/**
 * Builds a format string for storing numeric values as string int the map
 */
template<class T>
class _buildFormatString
{
public:
    static inline string
    buildFormatString ()
    {
        return "%i";
    }
};
//Overrides

template<> class _buildFormatString<double>
{
public:
    static inline string
    buildFormatString ()
    {
        return ("%." + resString + "f");
    }
};

template<> class _buildFormatString<long double>
{
public:

    static inline string
    buildFormatString ()
    {
        return "%." + resString + "Lf";
    }
};

template<> class _buildFormatString<float>
{
public:
    static inline string
    buildFormatString ()
    {
        return "%." + resString + "f";
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

    map<string, ulong> data;
    pair<string, ulong> dataPair;
    /**
     * Build the format string and caching variables
     */
    static string formatString = _buildFormatString<T>::buildFormatString();
    resString = lexical_cast<string>(res); //Cached
    /**
     * Read the data from the file and process it
     */
    static T buffer;
    while (fin.good ())
        {
            fin >> buffer;
            accumulator (buffer);
            /**
             * Round the value to the specified resolution
             * (res digits after the decimal point)
             */
            string roundedString = str(format (formatString) % _prepVal<T>::prepVal(buffer));
            if (data.count (roundedString) == 0)
                {
                    data[roundedString] = 1;
                }
            else
                {
                    data[roundedString]++;
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

