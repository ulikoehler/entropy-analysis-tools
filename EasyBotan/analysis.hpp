/* 
 * File:   highlevel.hpp
 * Author: uli
 *
 * This file contains functions suitable for cryptanalysis
 *
 * Created on 9. Januar 2009, 22:52
 */

#include <globals.hpp>

#ifndef _HIGHLEVEL_HPP
#define	_HIGHLEVEL_HPP

/**
 * For cryptographic analysis:
 * Encrypts a file with a random key.
 * Not decryptible.
 * @param cipher The cipher to use. Slash syntax preferred
 * @param size The key and IV size in bytes (not bits)
 */
void encryptRandom(string cipher, uint size, string infile, string outfile)
{
    ifstream fin(infile);
    ofstream fout(outfile)
    AutoSeeded_RNG rng;
    SymmetricKey key(rng, size);
    InitializationVector iv(rng, size);

    Pipe pipe(get_cipher(cipher, key, iv, ENCRYPTION), new DataSink_Stream(fout));
    //Process the file data
    fin >> pipe;
}


#endif	/* _HIGHLEVEL_HPP */

