/* 
 * File:   TextAnalyzer.cpp
 * Author: uli
 *
 * Created on 11. Dezember 2008, 13:41
 */

#include <stdlib.h>
#include <string>
#include <map>
#include <fstream>
#include <wctype.h>
#include <wchar.h>
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/program_options.hpp>

using namespace std;
using namespace boost;
using namespace boost::program_options;

/**
 * Typedefs
 */
//Maybe for unicode support
typedef char char_t;
typedef string string_t;

/**
 * Global variables
 */
static map<char_t, ulong> occ;
static pair<char_t, ulong> p;
static char sentenceSeparator; //Sentence separator
static string_t separator; //CSV separator
static variables_map vm;

inline void
print2ColumnOccurrenceStatistics (ostream& of)
{
    BOOST_FOREACH (p, occ)
    {
        of << p.first << separator << p.second << "\n";
    }
}

inline void
print3ColumnOccurrenceStatistics (ostream& of, ulong blockNum)
{
    BOOST_FOREACH (p, occ)
    {
        of << p.first << separator << p.second << separator << blockNum << "\n";
    }
}

inline string_t
readSentence(ifstream& fin)
{
    static string_t ret;
    static char c;
    while(fin.good())
        {
            //Read a character from the stream
            fin.get(c);
            //Break if it is the separator
            if(c == sentenceSeparator){break;}
            ret += c; //The separator is not added to the return string
        }
    return ret;

}

/*
 * 
 */
int
main (int argc, char** argv)
{
    static string infile;
    static string outfile;
    // Declare the supported options.
    options_description allowedOptions ("Allowed options");
    allowedOptions.add_options ()
            ("help,h", "Show help")
            ("input,i", value<string > (&infile), "The input file")
            ("out,o", value<string > (&outfile)->default_value ("stats.dat"), "Set statistics output file")
            ("separator", value<string> (&separator)->default_value (","), "CSV field separator")
            ("sentence-separator", value<char> (&sentenceSeparator)->default_value ('.'), "CSV field separator")
            ("overall,o", "Don't split (default)")
            ("lines,l", "Split by lines")
            ("sentences,s", "Split by sentences")
            ("words,w", "Split by words")
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

    /**
     * Main section: analyze the text
     */
    static ifstream fin (infile.c_str ());
    static ofstream fout(outfile.c_str ());
    static string_t buffer;

    if (vm.count ("sentences"))
        {
            for (static ulong bn = 0;fin.good ();bn++)
                {
                    //Read a sentence
                    buffer = readSentence (fin);

                    BOOST_FOREACH (char_t c, buffer)
                    {
                        if (occ[c] == 0)
                            {
                                occ[c] = 0;
                            }
                        occ[c]++;
                    }
                    //Save the data
                    print3ColumnOccurrenceStatistics (fout, bn);
                    //Clear the map data
                    occ.clear();
                }
        }
    else if (vm.count ("words"))
        {
            for (static ulong bn = 0;fin.good ();bn++)
                {
                    //Read one line
                    fin >> buffer;

                    BOOST_FOREACH (char_t c, buffer)
                    {
                        if (occ[c] == 0)
                            {
                                occ[c] = 0;
                            }
                        occ[c]++;
                    }
                    //Save the data
                    print3ColumnOccurrenceStatistics (fout, bn);
                    //Clear the map data
                    occ.clear();
                }
        }
    else //Overall statistics
        {
            while (fin.good ())
                {
                    //Read one line
                    fin >> buffer;

                    BOOST_FOREACH (char_t c, buffer)
                    {
                        if (occ[c] == 0)
                            {
                                occ[c] = 0;
                            }
                        occ[c]++;
                    }
                }
            //Save the data
            print2ColumnOccurrenceStatistics (fout);
        }

    fin.close ();
    fout.close ();

    return (EXIT_SUCCESS);
}

