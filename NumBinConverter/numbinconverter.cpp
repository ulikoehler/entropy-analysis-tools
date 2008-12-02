/* 
 * File:   numbinconverter.cpp
 * Author: uli
 *
 * Created on 29. November 2008, 18:50
 */

#include <stdlib.h>
#include <fstream>
#include <string>
#include <iostream>
#include <boost/program_options.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;
using namespace boost::program_options;

static fstream fin;
static fstream fout;
static string buffer;

variables_map vm;

template<class T>
inline void convToBin(T n)
{
    fout.write(reinterpret_cast<char*>(&n), sizeof(T));
}

template<class T>
inline void convert()
{
    while(fin.good())
        {
            fin >> buffer;
            convToBin<T>(lexical_cast<T>(buffer));
        }
}

int
main (int argc, char** argv)
{
    static string infile;
    static string outfile;
    // Declare the supported options.
    options_description allowedOptions ("Allowed options");
    allowedOptions.add_options ()
            ("help,h", "Show this help message")
            ("n", "Convert to numbers")
            ("b", "Convert to binary")
            ("int","Use integers")
            ("long","Use long")
            ("double", "Use double")
            ("in,i", value<string>(&infile), "Input file")
            ("out,o",value<string>(&outfile), "Output file")
            ;

    positional_options_description p;
    p.add("in", 1);
    p.add("out", 2);

    store (command_line_parser (argc, argv).
           options (allowedOptions).positional (p).run (), vm);
    notify (vm);

    fin.open(infile.c_str(), fstream::in);
    fout.open(outfile.c_str(), fstream::out | fstream::binary);

    //Check if the user has requested help
    if (vm.count ("help"))
        {
            cout << allowedOptions << "\n";
            return 1;
        }

    //Check if the user has specified input
    if (!vm.count ("in"))
        {
            cout << "No input file specified!\n" << allowedOptions << "\n";
            return 2;
        }

    //Check if the use has specified input
    if (!vm.count ("out"))
        {
            cout << "No output file specified!\n" << allowedOptions << "\n";
            return 2;
        }
    
    if(vm.count("int"))
        {
            convert<int>();
        }
    else if(vm.count("long"))
        {
            convert<long>();
        }
    else if(vm.count("double"))
        {
            convert<double>();
        }

    fin.close();
    fout.close();

    return (EXIT_SUCCESS);
}



