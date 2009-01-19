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
 * \brief Message digest main function
 */
void mdMain(int argc, char** argv)
{
    if(!(argc == 2))
        {
            printf("Usage: %s hash algorithm file\n", argv[0]);
            exit(1);
        }
    string algorithm = argv[2];
    string file = argv[3];
    cout << hashFile(algorithm, file) << endl;
}

/**
 * Hashes a file
 * \param algorithm The message digest algorithm to use
 * \param filename the filename to use
 * \return The hexadecimal representation of the hash
 */
string hashFile(string& algorithm, string& filename)
{
    Pipe hashPipe(new Chain(new Hash_Filter(algorithm), new Hex_Encoder));
    DataSource_Stream in(filename);
    hashPipe.process_msg(in);
    return hashPipe.read_all_as_string(0);
}

/**
 * Returns the hexadecimal representation of the input hashed
 * using the specified algorithm
 * \param algorithm The message digest algorithm to use
 * \param input The string to hash
 * \return The hexadecimal representation of the hash
 */
string hashString(string& algorithm, string& input)
{
    Pipe hashPipe(new Chain(new Hash_Filter(algorithm), new Hex_Encoder));
    hashPipe.process_msg(input);
    return hashPipe.read_all_as_string(0);
}

/**
 * For interal use:
 * Hashes the input string using the specifiedm algorithm and returns the result as an SecureVector<byte>
 * \param algorithm The message digest algorithm to use
 * \param input The string to use
 * \return
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


