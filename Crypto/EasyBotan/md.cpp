/*
 * File:   md.hpp
 * Author: uli
 *
 * This header provides easy access to Botan's hash functions
 *
 * Created on 9. Januar 2009, 22:35
 */
#include "globals.hpp"

/**
 * Message digest main function
 * called by main
 */
void mdMain(int argc, char** argv)
{
    //TODO
}

/**
 * Returns the hexadecimal representation of the input hashed
 * using the specified algorithm
 */
string hash(string& algorithm, string& input)
{
    Pipe hashPipe(new Chain(new Hash_Filter(algorithm), new Hex_Encoder));
    hashPipe.process_msg(input);
    return hashPipe.read_all_as_string(0);
}

/**
 * For interal use:
 * Hashes the input string using the specifiedm algorithm and returns the result as an
 * SecureVector<byte>
 */
SecureVector<byte> hashRaw(string& algorithm, string& input)
{
    Pipe hashPipe(new Chain(new Hash_Filter(algorithm)));
    hashPipe.process_msg(input);
    SecureVector<byte> ret = hashPipe.read_all(0);
    return ret;
}

/**
 * For interal use:
 * Hashes the input string using the specifiedm algorithm and returns the result as an
 * SecureVector<byte>
 */
SecureVector<byte> hashRawWithSalt(string& algorithm, string& input, SecureVector<byte>& salt)
{
    Pipe hashPipe(new Chain(new Hash_Filter(algorithm)));
    hashPipe.start_msg ();
    hashPipe.write(salt);
    hashPipe.write(input);
    hashPipe.end_msg ();
    SecureVector<byte> ret = hashPipe.read_all(0);
    return ret;
}


