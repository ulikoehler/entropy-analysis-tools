#include <iostream>
#include <string>
#include <fstream>
#include <boost/program_options.hpp>
#include <boost/function.hpp>
#include <boost/foreach.hpp>
#include <map>
//#include "asm.h"
#include <stdlib.h>
#include <algorithm>
#include <bitset>
#include <math.h>
#include "count1bits.h"

#define val_t ulong

using namespace std;
using namespace boost::program_options;

typedef unsigned long ulong;
typedef unsigned int uint;

unsigned long long glob0 = 0;
unsigned long long glob1 = 0;
unsigned long long chunk0 = 0;
unsigned long long chunk1 = 0;

void analyzeBits(ifstream& f, ofstream& of);

void analyzeChunks(ifstream& f, ofstream& of);

int blocksize;
int chunksize;

//Program options
variables_map vm;

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
        ("decimal,d", "Print statistics keys in decimal")
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
        cout << desc << "\n";
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
    //else if(vm.count
    else
    {
        analyzeBits(f,of);
    }

    f.close();
    of.close();

}

void analyzeBits(ifstream& f, ofstream& of)
{
    char* b = new char[blocksize];
    ///Main read loop
    for(uint bn = 1;!f.eof();bn++) //bn = block number
    {
        f.read(b, blocksize);
        static int c = f.gcount();
        if (c < blocksize)
        {
            blocksize = c;
        }
        ///Chunk loop (iterates blocksize times)
        //Chunk0 is (blocksize << 3) - chunk1; <<3 multiplies by 8 (8 bits per byte)
        //global counters are increased by chunk counters
        for (int i = 0; i < blocksize; i++)
        {
            /**
                Old algorithm:
                Faster than checking if: (b[i] & (1<<n)) >=1 for each n: 0 < n < 8:
                    chunk1 += b[i] & 1
                            + ((b[i] & (1<<1))>>1)
                            + ((b[i] & (1<<2))>>2)
                            + ((b[i] & (1<<3))>>3)
                            + ((b[i] & (1<<4))>>4)
                            + ((b[i] & (1<<5))>>5)
                            + ((b[i] & (1<<6))>>6)
                            + ((b[i] & (1<<7))>>7);
                */
                chunk1 += one_lookup8[(unsigned char)b[i]]; //Lookup table, 3 to 25 times faster than others
        }
        chunk0 = (blocksize<<3) - chunk1;
        //Print into stdout
        cout << "Block statistics: 0:" << chunk0 << " 1:" << chunk1 << endl;
        //Print this block's statistics into statistics file
        of  << bn << "   " << chunk0 << endl;
        glob0 += chunk0;
        glob1 += chunk1;
        chunk0 = 0;
        chunk1 = 0;
    }
    f.close();
    cout << "Overall statistics: 0:" << glob0 << " 1:" << glob1 << endl;
}

map<val_t,ulong> occ; //Occurrences
val_t n;
//Increments the map value
void incVal(val_t n)
{
    if (occ.count(n) == 0)
    {
        occ[n] = 1;
    }
    else
    {
        occ[n]++;
    }
}

static int cpb;
static int i,j; //Iterators

//Analyzes block for chunksize = 2
void ch2a(char *b)
{    //Iterates through the block (one byte per iteration)
    for (i = 0; i < blocksize; i++)
    {
        //Build n
        static unsigned char j = b[i];
        incVal(j & 0x3);  //3   = 00000011
        incVal(j & 0xc >> 2);  //12  = 00001100
        incVal(j & 0x30 >> 4); //48  = 00110000
        incVal(j & 0xc0 >> 6); //192 = 11000000
    }
}

//Analyzes block for chunksize = 4
void ch4a(char *b)
{    //Iterates through the block (one byte per iteration)
    for (i = 0; i < blocksize; i++)
    {
        //Build n
        //static unsigned char j = ;
        incVal(b[i] & 15);  //15  = 00001111
        incVal(b[i] & 0xf0 >> 4); //240 = 11110000
    }
}

//Analyzes block for chunksize = 4
void ch8a(char *b)
{    //Iterates through the block (one byte per iteration)
    for (i = 0; i < blocksize; i++)
    {
        incVal((uint8_t)b[i]);
    }
}

///TODO: Does not work if filesize % blocksize != 0
void ch16a(char *b)
{    //Iterates through the block (one byte per iteration)
    for (i = 0; i < blocksize; i += 2)
    {
        incVal((uint8_t)b[i]+(uint8_t(b[i+1])<<8));
    }
}

//Analyzes block for chunksize = 24
void ch24a(char *b)
{    //Iterates through the block (one byte per iteration)
    for (i = 0; i < blocksize; i += 3)
    {
        incVal((uint8_t)b[i]+
                ((uint8_t)(b[i+1])<<8)+
                  ((uint8_t)(b[i+2]<<16)));
    }
}

//Analyzes block for chunksize = 24
void ch32a(char *b)
{    //Iterates through the block (one byte per iteration)
    for (i = 0; i < blocksize; i += 4)
    {
        incVal((uint8_t)b[i]+
                ((uint8_t)(b[i+1])<<8)+
                  ((uint8_t)(b[i+2]<<16))+
                  ((uint8_t)(b[i+3]<<24)));
    }
}

//Analyzes block for chunksize n = 2^m > 8
void chna(char* b)
{
    cpb = div(blocksize, chunksize).quot; //chunks per block
    //Iterates through the block
    for (i = 0; i < cpb; i++)
    {
        for (j = 0; j < chunksize; j++)
        {
            n += b[i+j]<<j;
        }
    }
}

void analyzeChunks(ifstream& f, ofstream& of)
{
    char* b = new char[blocksize];
    boost::function<void(char* b)> fa; //function analyze
    //Select the appropriate function
    switch (chunksize)
    {
        case 1:
            {
                analyzeBits(f,of);
                return;
            }
        case 2:
            {
                fa = ch2a;
                break;
            }
        case 4:
            {
                fa = ch4a;
                break;
            }
        case 8:
            {
                fa = ch8a;
                break;
            }
        case 16:
            {
                fa = ch16a;
                break;
            }
        default:
            {
                fa = chna;
                break;
            }
    }
    ///Main read and analyze loop
    while (!f.eof())
    {
        f.read(b, blocksize);
        static int c = f.gcount();
        if (c < blocksize)
        {
            blocksize = c;
        }
        fa(b);

    }
    ///Write the acquired data to the output file
    //Iterates over all elements
    //and write the data to the output file
    pair<val_t,ulong> p;
    if(vm.count("decimal"))
    {
        BOOST_FOREACH(p, occ)
        {
            of << p.first << "  " << p.second << endl;
        }
    }
    else
    {
        switch (chunksize)
        {
            case 2:
                {
                    BOOST_FOREACH(p, occ)
                    {
                        of << bitset<2>(p.first) << "  " << p.second << endl;
                    }
                    break;
                }
            case 4:
                {
                    BOOST_FOREACH(p, occ)
                    {
                        of << bitset<4>(p.first) << "  " << p.second << endl;
                    }
                    break;
                }
            case 8:
                {
                    BOOST_FOREACH(p, occ)
                    {
                        of << bitset<8>(p.first) << "  " << p.second << endl;
                    }
                    break;
                }
            case 16:
                {
                    BOOST_FOREACH(p, occ)
                    {
                        of << bitset<16>(p.first) << "  " << p.second << endl;
                    }
                    break;
                }
            case 32:
                {
                    BOOST_FOREACH(p, occ)
                    {
                        of << bitset<32>(p.first) << "  " << p.second << endl;
                    }
                    break;
                }
        }
    }
    cout << "Written data to statistics file." << endl;
}
