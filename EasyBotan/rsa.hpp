/* 
 * File:   genkeypairs.hpp
 * Author: uli
 *
 * This header provides easy access to Key pair generation
 *
 * Created on 9. Januar 2009, 22:43
 */

#include <globals.hpp>

#ifndef _GENKEYPAIRS_HPP
#define	_GENKEYPAIRS_HPP

/**
 * Generates a new RSA private key.
 * @param bits Key bits
 */
inline RSA_PrivateKey generateKey(uint bits)
{
    AutoSeeded_RNG rng;
    RSA_PrivateKey key(rng, bits);
    return key;
}

/**
 * PEM-encodes a private RSA key
 */
inline string pemEncodeKey(RSA_PrivateKey key)
{
    return X509::PEM_encode(key);
}

#endif	/* _GENKEYPAIRS_HPP */

