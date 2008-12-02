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
    static string amountString;
    // Declare the supported options.
    options_description allowedOptions ("Allowed options");
    allowedOptions.add_options ()
            ("help,h", "Show help")
            ;
    options_description generatorsChooseOptions ("Generators: (Choose only one)");
    generatorsChooseOptions.add_options ()
            ("lc", "Linear congruential (minstd_rand)")
            ("lf607", "Lagged fibonacci 607")
            ("mt19937", "Mersenne Twister 19937")            
            ;
    options_description generatorOptions ("Generator options");
    generatorOptions.add_options ()
            ("out,o", value<string > (&outfile)->default_value ("randnum.txt"), "Set statistics output file")
            ("lower,l", value<string>(&lowerLimit)->default_value("0"), "Lower generator limit")
            ("upper,u", value<string>(&upperLimit)->default_value (lexical_cast<string>(std::numeric_limits<long>::max ())), "Upper generator limit")
            ("number,n", value<amount_t> (&amount)->default_value (100000), "Number of numbers to generator")
            ("p1", value<string>(&distParam1)->default_value("1"), "Parameter 1")
            ("p2", value<string>(&distParam2)->default_value("1"), "Parameter 2")
            ;
    options_description outputFormatOptions ("Output options");
    outputFormatOptions.add_options ()
            ("separator,s", value<string > (&separator)->default_value (","), "Set the CSV field separator")
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

    //Open the output stream
    fout.open(outfile.c_str (), ios::out);

    if (vm.count ("lc"))
        {

        }
    else if (vm.count ("lf607"))
        {
            
        }
    else if(vm.count("mt19937"))
        {
            
        }

    fout.close ();
    return (EXIT_SUCCESS);
}

