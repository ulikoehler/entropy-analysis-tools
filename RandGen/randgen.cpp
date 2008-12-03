/* 
 * File:   randgen.cpp
 * Author: uli
 *
 * Created on 18. November 2008, 16:39
 */

#include "globals.hpp"

int
main (int argc, char** argv)
{
    static string outfile;
    static string separator;
    // Declare the supported options.
    options_description allowedOptions ("Allowed options");
    allowedOptions.add_options ()
            ("help,h", "Show help")
            ;
    options_description generatorChoices ("Generators: (Choose exactly one)");
    generatorChoices.add_options ()
            ("lc", "Linear congruential (minstd_rand)")
            ("mt19937", "Mersenne Twister 19937")
            ("ecuyer1988", "Ecuyer 1988 (Additive Combine)")
            ("hellekalek1995", "Hellekalek 1995 (Inverse Congruential)")
            ("kreutzer1986", "Kreutzer 1986 (Inverse Congruential)")
            ("lf607", "Lagged fibonacci 607")
            ;
    options_description distributionChoices ("Distributions: (Choose exactly one)");
    distributionChoices.add_options ()
            ("unismallint", "Uniform small integer distribution (requires limit parameters)")
            ("uniint", "Uniform integer distribution (requires limit parameters)")
            ("unireal", "Uniform real distribution (requires limit parameters)")
            ("triangle", "Triangle distribution (requires 3 distribution parameters [a,b,c])")
            ("bernoulli", "Bernoulli distribution (requires 1 distribution parameter [p])")
            ("cauchy", "Cauchy distribution (requires 2 distribution parameters [median,sigma])")
            ("exponential", "Exponential distribution (requires 1 distribution parameter [lambda])")
            ("geometric", "Geometric distribution (requires 1 distribution parameter [p])")
            ("normal", "Normal distribution (requires 2 distribution parameters [mu,sigma])")
            ("lognormal", "Logarithmic normal distribution (requires 2 distribution parameters [mean,sigma])")
            ("unionsphere", "Uniform on sphere distribution (requires 1 distribution parameter [dimension])")
            ;
    options_description generatorOptions ("Generator options");
    generatorOptions.add_options ()
            ("out,o", value<string > (&outfile)->default_value ("stdout"), "Set statistics output file (or stdout)")
            ("lower,l", value<string>(&lowerLimit)->default_value("0"), "Lower generator limit")
            ("upper,u", value<string>(&upperLimit)->default_value (lexical_cast<string>(std::numeric_limits<long>::max ())), "Upper generator limit")
            ("number,n", value<amount_t> (&amount)->default_value (100000), "Number of numbers to generator")
            ("p1", value<string>(&distParam1)->default_value("1"), "First distribution parameter")
            ("p2", value<string>(&distParam2)->default_value("1"), "Second distribution parameter")
            ("p3", value<string>(&distParam3)->default_value("1"), "Third distribution parameter")
            ;
    options_description outputFormatOptions ("Output options");
    outputFormatOptions.add_options ()
            ("separator,s", value<string > (&separator)->default_value (","), "Set the CSV field separator")
            ;

    static variables_map vm;

    allowedOptions.add (generatorChoices).add (generatorOptions).add(distributionChoices).add (outputFormatOptions);

    positional_options_description p;
    p.add ("out", -1);

    store (command_line_parser (argc, argv).
           options (allowedOptions).positional (p).run (), vm);
    notify (vm);

    //Check if the user has requested help
    if (vm.count ("help"))
        {
            cout << allowedOptions << "\n";
            return 1;
        }

    /**
     * Main section
     */

    //Open the output stream (or declare to be cout if specified)
    if (outfile == "stdout")
        {
            fout == cout;
        }

    /**
     * Set the RNG algorithm ID number depending on the user selection
     */
    if(vm.count("mt19937"))
        {
            algorithmNum = 0;
        }
    else if(vm.count("lc"))
        {
            algorithmNum = 1;
        }
    else if(vm.count("ecuyer1988"))
        {
            algorithmNum = 2;
        }
    else if(vm.count("hellekalek1995"))
        {
            algorithmNum = 3;
        }
    else if(vm.count("kreutzer1986"))
        {
            algorithmNum = 4;
        }
    else if(vm.count("lf607"))
        {
            algorithmNum = 5;
        }
    else //No RNG algorithm selected
        {
            cout << "Select a generator algorithm!\n" << allowedOptions << "\n";
        }

    /**
     * Set the distribution ID number depending on the user selection
     */
    if(vm.count("unismallint"))
        {
            distributionNum = 0;
        }
    else if(vm.count("uniint"))
        {
            algorithmNum = 1;
        }
    else if(vm.count("unireal"))
        {
            algorithmNum = 2;
        }
    else if(vm.count("triangle"))
        {
            algorithmNum = 3;
        }
    else if(vm.count("bernoulli"))
        {
            algorithmNum = 4;
        }
    else if(vm.count("cauchy"))
        {
            algorithmNum = 5;
        }
    else if(vm.count("exponential"))
        {
            algorithmNum = 6;
        }
    else if(vm.count("geometric"))
        {
            algorithmNum = 7;
        }
    else if(vm.count("normal"))
        {
            algorithmNum = 8;
        }
    else if(vm.count("lognormal"))
        {
            algorithmNum = 9;
        }
    else if(vm.count("unionsphere"))
        {
            algorithmNum = 10;
        }
    else //No distribution selected
        {
            cout << "Select a distribution!\n" << allowedOptions << "\n";
        }


    //Call the RNG function (no arguments depends on global variable state
    GenRandBoost();

    if (!(outfile == "stdout")) {fout.close ();}
    return (EXIT_SUCCESS);
}

