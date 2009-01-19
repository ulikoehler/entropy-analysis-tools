/*
 * File:   random.cpp
 * Author: uli
 *
 * Created on 19. Januar 2009, 16:10
 */

#include "globals.hpp"

#define BUF_SIZE 4096
#define K_FACTOR 1024 //Factor for kilobytes, maybe someone wants to change it to 10000

void randomMain(int argc, char** argv)
{
    if (!(argc==2))
        {
            printf("Syntax: %s rand <size> <file>\n %i \n", argv[0], argc);
            exit(1);
        }
    string sizeString = argv[2];
    int len = sizeString.length ();
    int factor = 1;
    //Check if the user supplied a factor like k (kilo) or M (Mega).
    char suffix = sizeString[len-1];

    if(suffix == 'k') {factor = K_FACTOR;} //Kile
    else if(suffix == 'M') {factor = K_FACTOR*K_FACTOR;} //Mega
    else if (suffix == 'G') {factor = K_FACTOR*K_FACTOR*K_FACTOR;} //Giga
    else {len += 1;} //No factor so take the whole string (else substr (0,len-1))
    
    ulong size = lexical_cast<ulong>(sizeString.substr (0,len-1))*factor;
    AutoSeeded_RNG rng;
    /**
     * Generate the entropy in BUF_SIZE (default 4096) blocks and write the buffer content
     */
    ofstream fout(argv[3], ofstream::out | ofstream::binary); //The filename should be supplied in argv[3]
    char* buffer = new char[BUF_SIZE]; //sizeof(char) == 1
    for(;size >= BUF_SIZE;size -= BUF_SIZE) //Write all full blocks, counts down the size counter
        {
            rng.randomize ((byte*)buffer, BUF_SIZE);
            fout.write(buffer, BUF_SIZE);
        }
    /**
     * Write the last block
     * (less than BUF_SIZE bytes or none if the desired file size is divisible by BUF_SIZE)
     */
    if(!(size % BUF_SIZE == 0))
        {
            buffer = new char[size];
            rng.randomize ((byte*)buffer, size);
            fout.write(buffer, size);
        }
    cout << "Random file created successfully" << endl;
    fout.close();
}
