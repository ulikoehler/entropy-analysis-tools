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

/**
 * Message digest main function
 * called by main
 */
void mdMain(int argc, char** argv);

/**
 * Returns the hexadecimal representation of the input hashed
 * using the specified algorithm
 */
string hash(string& algorithm, string& input);

/**
 * For interal use:
 * Hashes the input string using the specifiedm algorithm and returns the result as an
 * SecureVector<byte>
 */
SecureVector<byte> hashRaw(string& algorithm, string& input);

/**
 * For interal use:
 * Hashes the input string using the specifiedm algorithm and returns the result as an
 * SecureVector<byte>
 */
SecureVector<byte> hashRawWithSalt(string& algorithm, string& input, SecureVector<byte> salt);

#endif	/* _MD_HPP */

