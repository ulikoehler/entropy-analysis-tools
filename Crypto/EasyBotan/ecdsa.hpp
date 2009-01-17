/* 
 * File:   ecdsa.hpp
 * Author: uli
 *
 * Created on 17. Januar 2009, 16:58
 */

#include "globals.hpp"

#ifndef _ECDSA_HPP
#define	_ECDSA_HPP

/**
 * Name-OID-Associations
 */
#define Prime256v1 "1.2.840.10045.3.1.7"

void
generateECDSAKey (ostream& pubout, ostream& privout, AutoSeededRNG& rng, string OID = Prime256v1)
{
    //Check which key type to use
    EC_Domain_Params params = get_EC_Dom_Pars_by_oid (Prime256v1);
    ECDSA_PrivateKey privKey (rng, params);
    //Write the key to the specified file
    pubout << X509::PEM_encode (privkey);
    privout << PKCS8::PEM_encode (privkey);
}

#endif	/* _ECDSA_HPP */

