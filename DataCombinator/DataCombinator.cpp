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
#include <string>

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
static void
combine (ifstream& fin, ofstream& fout, ulong blocksize)
{
    static ld sum;
    static ld avg;
    /**
     * Counts the lines in the current block.
     * Should be blocksize in each block except of the last one
     */
    static uint32_t vcount;
    static string buffer;

    cout << ldFormatString << endl;
    ///Main read loop
    while (fin.good ())
        {
            vcount = 0;
            sum = 0L;
            /**
             * Read the next block
             * Checks if the stream is still good after reading each line;
             * This makes
             */
            for (uint32_t i = 0; i < blocksize; i++)
                {
                    if (!fin.good ())
                        {
                            break;
                        }
                    //Read the next line (one value)
                    fin >> buffer;
                    sum += lexical_cast<T > (buffer);
                    vcount++;
                }
            //Calculate the average...
            avg = sum / vcount;
            //...and print it out
            fout << format (ldFormatString) % avg << endl;
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
    static int precision;
    static int blocksize;
    // Declare the supported options.
    options_description allowedOptions ("Allowed options");
    allowedOptions.add_options ()
            ("help,h", "Show this help message")
            ("blocksize,b", value<int> (&blocksize)->default_value (100), "Size of one block (is combined into one value)")
            ("precision,p", value<int>(&precision)->default_value (15), "Precision (for floating point output)")
            ("int", "Use integers")
            ("uint", "Use unsigned int")
            ("long", "Use long")
            ("llong", "Use long long")
            ("ullong,u", "Use unsigned long long")
            ("float,f", "Use float")
            ("double,d", "Use double")
            ("ldouble,l", "Use long double(default)")
            ("in,i", value<string > (&infile), "Input file")
            ("out,o", value<string > (&outfile), "Output file")
            ;

    //Build the long double format string
    cout << "b   "<< blocksize << endl;
    cout << "prec " << precision << endl;
    ldFormatString = "%." + lexical_cast<string > (precision) + "Lf";
    cout << "ldfs " << ldFormatString << endl;

    positional_options_description p;
    p.add ("in", 1);
    p.add ("out", 1);
    p.add ("blocksize", 1);

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
    //
    ifstream fin (infile.c_str ());
    ofstream fout (outfile.c_str ());
    if (vm.count ("int"))
        {
            combine<int>(fin, fout, blocksize);
        }
    else if (vm.count ("uint"))
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
    else //if (vm.count ("ldouble"))
        {
            combine<long double>(fin, fout, blocksize);
        }
    //Close the streams
    fin.close ();
    fout.close ();

    return (EXIT_SUCCESS);
}

