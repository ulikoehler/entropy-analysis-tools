/**
 * Entropy analysis tools main file
 */
#include "globals.hpp"

int
main (int argc, char** argv)
{
    static string infile;
    static string outfile;
    static string action;
    // Declare the supported options.
    options_description allowedOptions ("Allowed options");
    options_description genericOptions ("Generic options");
    genericOptions.add_options ()
            ("action,a", value<string > (&action)->default_value ("analyze-bin"), "Action to do")
            ("help,h", "Show help")
            ("input,i", value<string > (&infile), "The input file")
            ("out,o", value<string > (&outfile)->default_value ("stats.dat"), "Set statistics output file")
            ;
    options_description binAnalysisOptions ("Binary analysis options (action analyze-bin):");
    binAnalysisOptions.add_options ()
            ("chunks,c", "Analyze chunks of chunksize bits rather than bits. Must be a multiple of chunksize.")
            ("blocksize,b", value<int>(&blocksize)->default_value (1024), "Set block size (must be a multiple of chunksize).")
            ("chunksize,s", value<int>(&chunksize)->default_value (4), "Set chunk size")
            ("per-block,p", "Analyze each block separately")
            ;
    options_description numericAnalysisOptions ("Numerical analysis options (action analyze-numeric):");
    numericAnalysisOptions.add_options ()
            ("base,b", value<ushort > (&base), "The base to use for input (must be <= 32)")
            ;
    options_description outputFormatOptions ("Output format options");
    outputFormatOptions.add_options ()
            ("decimal,d", "Print statistics keys in decimal (for use with -c)")
            ("separator", value<string > (&separator)->default_value (","), "Set the CSV field separator")
            ;

    allowedOptions.add (genericOptions).add(binAnalysisOptions).add (numericAnalysisOptions).add (outputFormatOptions);

    positional_options_description p;
    p.add ("action", 1);
    //p.add ("input", 1);


    store (command_line_parser (argc, argv).
           options (allowedOptions).positional (p).run (), vm);
    notify (vm);

    //Check if the user has requested help
    if (vm.count ("help"))
        {
            cout << allowedOptions << "\n";
            return 1;
        }

    //Check if the base is in valid range 0-32
    if (base > 32)
        {
            cout << "Base must be less or equal to 32\n"
                    << allowedOptions;
        }

    //Check if the use has specified input
    if (!vm.count ("input"))
        {
            cout << "No input file specified!\n" << allowedOptions << "\n";
            return 2;
        }

    ///Open the streams
    ifstream f (infile.c_str (), fstream::binary);
    ofstream of (outfile.c_str (), fstream::out);

    int ret = 0; //Return value
    if (action == "analyze-bin")
        {
            ret = analyzeBinaryFile (f, of);
        }
    else if (action == "analyze-numeric")
        {
            ret = analyzeNumericFile (f, of);
        }
    else
        {
            cout << "Invalid action: " << action << "\n"
                    << allowedOptions << "\n";
        }

    f.close ();
    of.close ();
    return ret;
}


