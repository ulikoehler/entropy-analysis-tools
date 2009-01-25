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

inline void generateKey(string pubname, string privname, string password, uint bits)
{
    wfstream pubout(pubname, wfstream::out);
    wfstream privout(privname, wfstream::out);
    RSA_PrivateKey key = generateKey(bits);
    pubout << X509::PEM_encode (key, rng, password.c_str())
    privout << PKCS8::PEM_encode(key);
    pubout.close();
    privout.close();
}

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

#endif	/* _GENKEYPAIRS_HPP */

