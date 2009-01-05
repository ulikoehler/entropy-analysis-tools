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
 * Arbitrary rounding macro
 * Replaced old Boost::format algorithm.
 * According to benchmarks/quantize it should make
 * the calculation about 48 times faster on a Pentium M.
 * Parameters: n is the number; x is 10^-precision
 * where precision is the number of digits to round to.
 * Although it is call rounding it will be more likely cutting
 * the last digits off.
 * To avoid performance losses on badly-optimizing compilers,
 * precalculate n = 10^-precision.
 */
#define roundarb(x,n) x-fmod(x,n)

/**
 * Global variables used only in this file
 */
static double prec; //= 10^-res
static string resString; //TODO check if needed

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
 * Rounds floating point numbers to res digits
 * and returns integers.
 */
template<class T>
class _fitvalue 
{
public:
    static inline T
    fitvalue(T& p)
    {
        return p;
    }
};
//Overrides

template<> class _fitvalue<double>
{
public:
    static inline double
    fitvalue(double& p)
    {
        return roundarb(p,prec);
    }
};

template<> class _fitvalue<long double>
{
public:
    static inline long double
    fitvalue(long double& p)
    {
        return roundarb(p,prec);
    }
};

template<> class _fitvalue<float>
{
public:
    static inline float
    fitvalue(float& p)
    {
        return roundarb(p,prec);
    }
};

/**
 * Main numeric analyzator function
 */
template<class T>
void
analyzeNumericData (istream& fin, ostream& fout)
{
    #ifndef NOSTATISTICSDATA
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
    #endif //NOSTATISTICSDATA

    map<T, ulong> data;
    pair<T, ulong> dataPair;
    /**
     * Precalculate some parameters
     */
    static string formatString = _buildFormatString<T>::buildFormatString();
    static string resString = lexical_cast<string>(res); //Cached //TODO check if needed
    prec = pow(10,-res);
    /**
     * Read the data from the file and process it
     */
    static T buffer;
    while (fin.good ())
        {
            fin >> buffer;
	    #ifndef NOSTATISTICSDATA
		accumulator (buffer);
	    #endif //NOSTATISTICSDATA
            /**
             * Round the value to the specified resolution
             * (res digits after the decimal point)
             */
            T rounded = str(format (formatString) % _prepVal<T>::prepVal(buffer));
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
    #ifndef NOSTATISTICSDATA
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
    #endif //NOSTATISTICSDATA
}

#endif	/* _ANALYZE_NUMERIC_HPP */

