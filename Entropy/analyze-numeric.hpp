/* 
 * File:   analyze-numeric.hpp
 * Author: uli
 *
 * Created on 12. Dezember 2008, 18:56
 */

#ifndef _ANALYZE_NUMERIC_HPP
#define	_ANALYZE_NUMERIC_HPP

#include "../globals.hpp"
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
 * remember precalculate n = 10^-precision.
 */
#define roundarb(x,n) x-std::fmod(x,n)

/**
 * We need copies of the precision of each type
 * to avoid ambigous constructs with std::fmod
 * (fmod is taking two parameters of the same type and is call in a template function)
 */
static double dPrec; //= 10^-res, as double
static float fPrec; //= 10^-res, as float
static long double ldPrec; //= 10^-res, as long double

inline void setPrecision(uint digits)
{
    ldPrec = pow(10,-digits);
    dPrec = pow(10,-digits);
    fPrec = pow(10,-digits);
}

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
    else if (vm.count ("short")) //Int
        {
            analyzeNumericData<short>(fin, fout);
        }
    else if (vm.count ("ushort")) //Int
        {
            analyzeNumericData<ushort>(fin, fout);
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
    else //if(vm.count("ld")) //Long double
        {
            analyzeNumericData<long double>(fin, fout);
        }
}

/**
 * Rounds floating point numbers to res digits
 * and returns integers.
 */
template<class T>
class _roundvalue
{
public:
    static inline T
    roundvalue(T& p)
    {
        return p;
    }
};
//Overrides

template<> class _roundvalue<double>
{
public:
    static inline double
    roundvalue(double& p)
    {
        return roundarb(p,dPrec);
    }
};

template<> class _roundvalue<long double>
{
public:
    static inline long double
    roundvalue(long double& p)
    {
        return roundarb(p,ldPrec);
    }
};

template<> class _roundvalue<float>
{
public:
    static inline float
    roundvalue(float& p)
    {
        return roundarb((float)p,fPrec);
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

    static map<T, ulong> data;
    static pair<T, ulong> dataPair;
    /**
     * Precalculate the precision
     */
    setPrecision (res);
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
            T rounded = _roundvalue<T>::roundvalue(buffer);
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

