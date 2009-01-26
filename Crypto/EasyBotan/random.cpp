/*
 * File:   random.cpp
 * Author: uli
 *
 * Created on 19. Januar 2009, 16:10
 */

#include "globals.hpp"

#define BUF_SIZE 4096

/**
 * Generates a file containing random data ("entropy")
 * @param outfile The filename to write the entropy to
 * @param size The number of bytes to write out
 */
void generateEntropyFile(string outfile, ulong size)
{    
    shared_ptr<AutoSeeded_RNG> rng = rootWindow->rng;
    /**
     * Generate the entropy in BUF_SIZE (default 4096) blocks and write the buffer content
     */
    ofstream fout(outfile.c_str(), ofstream::out | ofstream::binary); //The filename should be supplied in argv[3]
    char* buffer = new char[BUF_SIZE]; //sizeof(char) == 1
    for(;size >= BUF_SIZE;size -= BUF_SIZE) //Write all full blocks, counts down the size counter
        {
            rng->randomize ((byte*)buffer, BUF_SIZE);
            fout.write(buffer, BUF_SIZE);
        }
    /**
     * Write the last block
     * (less than BUF_SIZE bytes or none if the desired file size is divisible by BUF_SIZE)
     */
    delete buffer; //Deletes the original buffer
    if(!(size % BUF_SIZE == 0))
        {
            buffer = new char[size];
            rng->randomize ((byte*)buffer, size);
            fout.write(buffer, size);
        }
    delete buffer; //Deletes the last-block buffer
    fout.close();
}
