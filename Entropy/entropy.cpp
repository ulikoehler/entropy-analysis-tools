/**
 * Entropy analysis tools main file
 * Should run significantly faster on 64 bit architectures
 * because 128-bit long long values can be calculated natively
 */
#include "globals.hpp"

int analyzeBinaryFile (ifstream& f, ofstream& of);

int
main (int argc, char** argv)
{
    static string infile;
    static string outfile;
    static int precision;
    // Declare the supported options.
    options_description allowedOptions ("Allowed options");
    options_description genericOptions ("Generic options");
    genericOptions.add_options ()
            ("help,h", "Show help")
            ("input,i", value<string > (&infile), "The input file")
            ("out,o", value<string > (&outfile)->default_value ("stats.dat"), "Set statistics output file")
            ;
    options_description analysisOptions ("Analysis options:");
    analysisOptions.add_options ()
            ("chunks,c", "Analyze chunks of chunksize bits rather than bits. Must be a multiple of chunksize.")
            ("blocksize,b", value<uint > (&blocksize)->default_value (1024), "Set block size (must be a multiple of chunksize).")
            ("chunksize,s", value<uint > (&chunksize)->default_value (4), "Set chunk size")
            ("per-block,p", "Analyze each block separately")
            ("entropy,e", "Calculate Shannon's entropy for each block separately (Has to be called with -c and -p)")
            ("focus,f", value<uint > (&focus), "Just look at chunks equal to the supplied number")
            ("fill", value<uint > (&fillByte)->default_value (0), "The fill byte (as integer) if filesize is not multiple of chunksize")
            ;
    options_description outputFormatOptions ("Output format options");
    outputFormatOptions.add_options ()
            ("decimal,d", "Print statistics keys in decimal (for use with -c)")
            ("precision", value<int>(&precision)->default_value (15), "Precision (for floating point output in statistical indicators)")
            ("r-compatible,r", "Produce ordered output (with -p -c, compatible with all R scripts)")
            ("separator", value<string > (&separator)->default_value (","), "Set the CSV field separator")
            ;
    allowedOptions.add (genericOptions).add (analysisOptions).add (outputFormatOptions);

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

    //Build the format strings
    ldFormatString = "%." + lexical_cast<string > (precision) + "Lf";

    ///Open the streams
    ifstream f (infile.c_str (), fstream::binary | fstream::in);
    ofstream of (outfile.c_str (), fstream::out);

    int ret = 0; //Return value

    ret = analyzeBinaryFile (f, of);

    f.close ();
    of.close ();
    return ret;
}

inline int
analyzeBinaryFile (ifstream& f, ofstream& of)
{
    perblock = vm.count ("per-block"); //Behaves like a boolean, also consumes only one byte

    //Initalize the buffer array
    buffer = new char[blocksize];
    //Call the appropriate analysator function
    if (vm.count ("chunks"))
        {
            //Validate chunk size
            if (blocksize % chunksize != 0)
                {
                    cout << "Blocksize must be a multiple of chunksize!\n";
                    return 3;
                }
            if (vm.count ("focus"))
                {
                    analyzeChunksFocus (f, of);
                }
            else
                {
                    analyzeChunks (f, of);
                }
        }
        //Count bits
    else
        {
            //Count bits; per block
            if (perblock)
                {
                    analyzeBitsPerBlock (f, of);
                }
                //Count bits (no blocks)
            else
                {
                    analyzeBits (f);
                }
        }

    //Delete the buffer array
    delete buffer;
    return 0;
}

