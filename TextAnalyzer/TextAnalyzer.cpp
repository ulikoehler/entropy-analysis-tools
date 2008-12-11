/* 
 * File:   TextAnalyzer.cpp
 * Author: uli
 *
 * Created on 11. Dezember 2008, 13:41
 */

#include <stdlib.h>
#include <string>
#include <boost/program_options.hpp>

using namespace std;
using namespace boost;

/*
 * 
 */
int
main (int argc, char** argv)
{
    // Declare the supported options.
    options_description allowedOptions ("Allowed options");
    options_description genericOptions ("Generic options");
    genericOptions.add_options ()
            ("help,h", "Show help")
            ("input,i", value<string > (&infile), "The input file")
            ("out,o", value<string > (&outfile)->default_value ("stats.dat"), "Set statistics output file")
            ;
    positional_options_description p;
    p.add ("input", 1);

    store (command_line_parser (argc, argv).
           options (allowedOptions).positional (p).run (), vm);
    notify (vm);


    //Check if the user has requested help
    if (vm.count ("help"))
        {
            cout << allowedOptions << "\n";
            return 1;
        }
    //Check if the user has specified input
    if (!vm.count ("input"))
        {
            cout << "No input file specified!\n" << allowedOptions << "\n";
            return 2;
        }

    return (EXIT_SUCCESS);
}

