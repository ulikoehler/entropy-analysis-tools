/*
 * File:   md.hpp
 * Author: uli
 *
 * This header provides easy access to Botan's hash functions
 *
 * Created on 9. Januar 2009, 22:35
 */
#include "globals.hpp"

#ifndef _MD_HPP
#define	_MD_HPP
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
void mdMain(int argc, char** argv);
/**
 * Hashes a file
 * \param algorithm The message digest algorithm to use
 * \param filename the filename to use
 * \return The hexadecimal representation of the hash
 */
string hashFile(string& algorithm, string& filename);
/**
 * Returns the hexadecimal representation of the input hashed
 * using the specified algorithm
 * \param algorithm The message digest algorithm to use
 * \param input The string to hash
 * \return The hexadecimal representation of the hash
 */
string hashString(string& algorithm, string& input);

/**
 * For interal use:
 * Hashes the input string using the specifiedm algorithm and returns the result as an SecureVector<byte>
 * \param algorithm The message digest algorithm to use
 * \param input The string to use
 * \return
 */
SecureVector<byte> hashRaw(string& algorithm, string& input);

/**
 * For interal use:
 * Hashes the input string using the specifiedm algorithm and returns the result as an
 * SecureVector<byte>
 */
SecureVector<byte> hashRawWithSalt(string& algorithm, string& input, SecureVector<byte>& salt);

#endif	/* _MD_HPP */

