/* 
 * File:   genkeypairs.hpp
 * Author: uli
 *
 * This header provides easy access to Key pair generation
 *
 * Created on 9. Januar 2009, 22:43
 */
#include "globals.hpp"

#ifndef _GENKEYPAIRS_HPP
#define	_GENKEYPAIRS_HPP

/**
 * Generates a new RSA private key.
 * @param bits Key bits
 */
RSA_PrivateKey generateRSAKey(uint bits);

/**
 * Generates a new RSA private key.
 * @param pubname The file to write the public key to
 * @param privname The file to write the private key to
 * @param password The password to use to encrypt the private key or NULL if no password should be used
 * @param bits The key size in bits
 */
void generateRSAKey(string pubname, string privname, string password, uint bits);



#endif	/* _GENKEYPAIRS_HPP */

