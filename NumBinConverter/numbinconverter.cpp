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

variables_map vm;

template<class T>
inline void convToBin()
{
    static string buffer;
    while(fin.good())
        {
            fin >> buffer;
            static T n = lexical_cast<T>(buffer);
            fout.write(reinterpret_cast<char*>(&n), sizeof(T));
        }
}

template<class T>
inline void convToNum()
{
    char buffer[sizeof(T)];
    while(fin.good())
        {
            fin.read(buffer, sizeof(T));
            fout << *(reinterpret_cast<T*>(&buffer)) << "\n";
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
            ("numbers,n", "Convert to numbers")
            ("binary,b", "Convert to binary")
            ("int","Use integers")
            ("uint","Use unsigned int")
            ("long","Use long")
            ("llong","Use long long")
            ("ullong","Use unsigned long long")
            ("float", "Use float")
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

    if(vm.count("numbers"))
        {
            fin.open(infile.c_str(), fstream::in | fstream::binary);
            fout.open(outfile.c_str(), fstream::out);
            if(vm.count("int"))
                {
                    convToNum<int>();
                }
            else if(vm.count("uint"))
                {
                    convToNum<unsigned int>();
                }
            else if (vm.count ("long"))
                {
                    convToNum<long>();
                }
            else if (vm.count ("ulong"))
                {
                    convToNum<unsigned long>();
                }
            else if (vm.count ("llong"))
                {
                    convToNum<long long>();
                }
            else if (vm.count ("ullong"))
                {
                    convToNum<unsigned long long>();
                }
            else if (vm.count ("float"))
                {
                    convToBin<float>();
                }
            else if (vm.count ("double"))
                {
                    convToBin<double>();
                }
        }
    else //vm.count("-b")
        {
            fin.open(infile.c_str(), fstream::in);
            fout.open(outfile.c_str(), fstream::out | fstream::binary);
            if(vm.count("int"))
                {
                    convToBin<int>();
                }
            else if(vm.count("uint"))
                {
                    convToBin<unsigned int>();
                }
            else if (vm.count ("long"))
                {
                    convToBin<long>();
                }
            else if (vm.count ("ulong"))
                {
                    convToBin<unsigned long>();
                }
            else if (vm.count ("llong"))
                {
                    convToBin<long long>();
                }
            else if (vm.count ("ullong"))
                {
                    convToBin<unsigned long long>();
                }
            else if (vm.count ("float"))
                {
                    convToBin<float>();
                }
            else if (vm.count ("double"))
                {
                    convToBin<double>();
                }
        }

    fin.close();
    fout.close();

    return (EXIT_SUCCESS);
}



