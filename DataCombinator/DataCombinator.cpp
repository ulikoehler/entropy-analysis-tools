/* 
 * File:   DataCombinator.cpp
 * Author: uli
 *
 * Created on 9. Dezember 2008, 18:34
 */

#include <stdlib.h>
#include <boost/program_options.hpp>
#include <iosfwd>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <iostream>

using namespace std;
using namespace boost::program_options;
using namespace boost;

typedef long double ld;
typedef unsigned long ulong;
typedef unsigned long long ull;

typedef long double acc_t; //Accumulator type

static string ldFormatString;

/**
 * Decimates data from a file and writes the results into another
 * 
 */
template<class T>
static void combine(ifstream& fin, ofstream& fout, ulong blocksize)
{
    static ld sum;
    static ld avg;
    static string buffer;
    ///Main read loop
    while (fin.good ())
        {
            /**
             * Read one block
             */
            for (int i = 0; i < blocksize; i++)
                {
                    //Read the buffer
                    fin >> buffer;
                    if(!fin.good())
                        {break;}
                    sum += lexical_cast<T>(buffer);
                }
            //Calculate the average...
            avg = sum / blocksize;
            //...and print it out
            fout << format(ldFormatString) % avg << endl;
        }
}

/*
 * 
 */
int
main (int argc, char** argv)
{
    static variables_map vm;
    static string infile;
    static string outfile;
    static unsigned short precision;
    static uint32_t blocksize;
    // Declare the supported options.
    options_description allowedOptions ("Allowed options");
    allowedOptions.add_options ()
            ("help,h", "Show this help message")
            ("blocksize,b", value<uint32_t>(&blocksize)->default_value(100), "Size of one block (is combined into one value)")
            ("int","Use integers")
            ("uint","Use unsigned int")
            ("long","Use long")
            ("llong","Use long long")
            ("ullong","Use unsigned long long")
            ("float", "Use float")
            ("double", "Use double")
            ("decimals", value<unsigned short>(&precision)->default_value(6),"Decimals to display")
            ("in,i", value<string>(&infile), "Input file")
            ("out,o",value<string>(&outfile), "Output file")
            ;

    //Build the long double format string
    ldFormatString = "%." + lexical_cast<string > (precision) + "Lf";

    positional_options_description p;
    p.add("in", 1);
    p.add("out", 1);
    p.add("blocksize", 1);

    store (command_line_parser (argc, argv).
           options (allowedOptions).positional (p).run (), vm);
    notify (vm);

    //Forward-declaration of the fstreams
    ifstream fin;
    ofstream fout;


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
            fin.open(infile.c_str());
            fout.open(outfile.c_str());
            if(vm.count("int"))
                {
                    combine<int>(fin, fout, blocksize);
                }
            else if(vm.count("uint"))
                {
                    combine<unsigned int>(fin, fout, blocksize);
                }
            else if (vm.count ("long"))
                {
                    combine<long>(fin, fout, blocksize);
                }
            else if (vm.count ("ulong"))
                {
                    combine<unsigned long>(fin, fout, blocksize);
                }
            else if (vm.count ("llong"))
                {
                    combine<long long>(fin, fout, blocksize);
                }
            else if (vm.count ("ullong"))
                {
                    combine<unsigned long long>(fin, fout, blocksize);
                }
            else if (vm.count ("float"))
                {
                    combine<float>(fin, fout, blocksize);
                }
            else if (vm.count ("double"))
                {
                    combine<double>(fin, fout, blocksize);
                }
        }
    //Close the streams
    fin.close();
    fout.close();
    return (EXIT_SUCCESS);
}

