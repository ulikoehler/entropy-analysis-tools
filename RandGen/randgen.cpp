/* 
 * File:   randgen.cpp
 * Author: uli
 *
 * Created on 18. November 2008, 16:39
 */

#include "globals.hpp"

/*
 * 
 */
int
main (int argc, char** argv)
{
    long lowerLimit;
    long upperLimit;
    ull count;
    string outfile;
    string separator;
    // Declare the supported options.
    options_description allowedOptions ("Allowed options");
    options_description generatorsChooseOptions ("Generators: (Choose only one)");
    generatorsChooseOptions.add_options ()
            ("lc", "Linear congruential (minstd_rand)")
            ("lf607", "Lagged fibonacci 607")
            ;
    options_description generatorOptions ("Generator options");
    generatorOptions.add_options ()
            ("help,h", "Show help")
            ("out,o", value<string > (&outfile)->default_value ("randnum.txt"), "Set statistics output file")
            ("lower,l", value<long>(&lowerLimit)->default_value (0), "Lower generator limit")
            ("upper,u", value<long>(&upperLimit)->default_value (std::numeric_limits<long>::max ()), "Upper generator limit")
            ("count,n", value<ull > (&count)->default_value (100000), "Number of numbers to generator")
            ;
    options_description outputFormatOptions ("Output options");
    outputFormatOptions.add_options ()
            ("binary,b", "Binary output")
            ("enumerate,e", "Enumerate output lines")
            ("separator", value<string > (&separator)->default_value (","), "Set the CSV field separator")
            ;



    variables_map vm;

    allowedOptions.add (generatorsChooseOptions).add (generatorOptions).add (outputFormatOptions);

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
    fstream f (outfile.c_str (), ios::out);
    if (vm.count ("enumerate"))
        {
            f << "\"Index\"" << separator << "\"Number\"\n"; //Header
        }
    else
        {
            f << "\"Number\"\n"; //Header
        }

    uint32_t seed = time (0);

    minstd_rand0 lc (seed);
    lagged_fibonacci607 lf607 (seed);

    uniform_int<long> udist (lowerLimit, upperLimit); //Declare distribution

    if (vm.count ("lc"))
        {
            variate_generator<minstd_rand0, uniform_int<long> > (lc, udist);
            if (vm.count ("enumerate"))
                {
                    #pragma omp parallel for
                    for (ull i = 1; i <= count; i++)
                        {
                            f << i << separator << lc () << "\n";
                        }
                }
            else if(vm.count("binary"))
                {
                    #pragma omp parallel for
                    for (count; count > 0; count--)
                        {
                            f << reinterpret_cast<char[];
                        }
                }
            else
                {
                    #pragma omp parallel for
                    for (count; count > 0; count--)
                        {
                            f << lc () << "\n";
                        }
                }
        }
    else if (vm.count ("lf607"))
        {
            variate_generator<lagged_fibonacci607, uniform_int<long> > (lf607, udist);
            #pragma omp parallel for
            for (count; count > 0; count--)
                {
                    f << lf607 () << "\n";
                }
        }
    else//(vm.count"lc")
        {

        }

    f.close ();
    return (EXIT_SUCCESS);
}

