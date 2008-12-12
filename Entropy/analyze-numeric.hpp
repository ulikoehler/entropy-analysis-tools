/* 
 * File:   analyze-numeric.hpp
 * Author: uli
 *
 * Created on 12. Dezember 2008, 18:56
 */

#ifndef _ANALYZE_NUMERIC_HPP
#define	_ANALYZE_NUMERIC_HPP

#include "globals.hpp"

//Forward declarations
template<class T> void analyzeNumericData(istream& fin, ostream& fout);

/**
 * Top-level numeric analysis function: Determinates what type to use and
 * calls the main analyzator function with the appropriate tmeplate argument
 */

void analyzeNumeric(istream& fin, ostream& fout)
{
    if(vm.count("long")) //Long
        {
            analyzeNumericData<long>(fin, fout);
        }
    else if(vm.count("ld")) //Long double
        {
            analyzeNumericData<long double>(fin, fout);
        }
}

/**
 * Main numeric analyzator function
 */
template<class T>
void analyzeNumericData(istream& fin, ostream& fout)
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
    
    T buffer;
    /**
     * Read the data from the file
     */
    while(fin.good())
        {
            fin >> buffer;
            accumulator(buffer);
        }
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
    cout << "   Standard deviation: " << format (ldFormatString) % sqrt(variance) << "\n";
    cout << "   Skewness: " << format (ldFormatString) % extract::skewness (accumulator) << "\n";
}

#endif	/* _ANALYZE_NUMERIC_HPP */

