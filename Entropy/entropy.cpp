/**
 * Entropy analysis tools main file
 */
#include "globals.hpp"

int main(int argc, char** argv)
{
    static string infile;
    static string outfile;
    // Declare the supported options.
    options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Show help")
        ("input,i", value<string>(&infile), "The input file")
        ("blocksize,b", value<int>(&blocksize)->default_value(1024), "Set block size")
        ("chunksize,s", value<int>(&chunksize)->default_value(4), "Set chunk size")
        ("decimal,d", "Print statistics keys in decimal (for use with -c)")
        ("per-block,p", "Analyze per block (makes diagram 3d with -c)")
        ("out,o", value<string>(&outfile)->default_value("stats.dat"), "Set statistics output file (for gnuplot)")
        ("chunks,c", "Analyze chunks of chunksize bits rather than bits. Blocksize % chunksize must be 0")
        ;
    positional_options_description p;
    p.add("input", -1);


    store(command_line_parser(argc, argv).
          options(desc).positional(p).run(), vm);
    notify(vm);

    //Check if the user requested help
    if (vm.count("help"))
    {
        desc.print(cout);
        cout << "\n";
        return 1;
    }

    //Check if the use has specified input
    if (!vm.count("input"))
    {
        cout << "No input file specified!\n" << desc << "\n";
        return 2;
    }

    ///Open the streams
    ifstream f(infile.c_str(), fstream::binary);
    ofstream of(outfile.c_str(), fstream::out);

    //Check if two analysator options are called together //TODO
    //if(vm.count("chunks")
    
    static char perblocks = vm.count("per-block"); //Behaves like a boolean, also consumes only one byte

    //Call the appropriate analysator function
    if (vm.count("chunks"))
    {
        //Validate chunk size
        if (blocksize % chunksize != 0)
        {
            cout << "Blocksize % chunksize must be 0 and chunksize  = 2^n!\n";
            return 3;
        }
        analyzeChunks(f,of);
    }
    //Count bits
    else
    {
        //Count bits; per block
        if(perblocks){analyzeBitsBlocks(f,of);}
        //Count bits (no blocks)
        else{analyzeBits(f);}
    }

    f.close();
    of.close();
}


