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
#define Prime239v3 "1.2.840.10045.3.1.6"
#define Prime239v2 "1.2.840.10045.3.1.5"
#define Prime239v1 "1.2.840.10045.3.1.4"
#define Prime192v3 "1.2.840.10045.3.1.3"
#define Prime192v2 "1.2.840.10045.3.1.2"
#define Prime192v1 "1.2.840.10045.3.1.1"
#define brainpoolP512r1 "1.3.36.3.3.2.8.1.1.13"
#define brainpoolP384r1 "1.3.36.3.3.2.8.1.1.11"
#define brainpoolP320r1 "1.3.36.3.3.2.8.1.1.9"
#define brainpoolP256r1 "1.3.36.3.3.2.8.1.1.7"
#define brainpoolP224r1 "1.3.36.3.3.2.8.1.1.5"
#define brainpoolP192r1 "1.3.36.3.3.2.8.1.1.3"
#define brainpoolP160r1 "1.3.36.3.3.2.8.1.1.1"
#define NISTP521 "1.3.6.1.4.1.8301.3.1.2.9.0.38"
#define secp521r1 "1.3.132.0.35"
#define secp384r1 "1.3.132.0.34"
#define secp256k1 "1.3.132.0.10"
#define secp224r1 "1.3.132.0.33"
#define secp224k1 "1.3.132.0.32"
#define secp192k1 "1.3.132.0.31"
#define secp160r2 "1.3.132.0.30"
#define secp160k1 "1.3.132.0.9"
#define secp128r2 "1.3.132.0.29"
#define secp128r1 "1.3.132.0.28"
#define secp112r2 "1.3.132.0.7"
#define secp112r1 "1.3.132.0.6"

void ecMain(int argc, char** argv)
{
    string subAction(argv[2]); //Second level action
    argc--;
    if(subAction == "generate" || subaction == "gen")
        {
            /**
             * Check if there are enough arguments
             */
            if(!argc)
                {
                    cout << "Not enough arguments!" << endl;
                    exit(1);
                }
            /**
             * Check which curve to use
             */
            string oid;
            string name(strlwr(argv[3]));
            if(name == "prime256v1")

        }
}

/**
 * Toplevel function to generate an ECDSA key
 */
void generateECDSAKey(string& out, string& oid)
{
    fstream pubout(out, fstream::out);
    fstream privout(out, fstream::out);
    
    generateECDSAKey(pubout, privout, Prime256v1);
}


void
generateECDSAKey (ofstream& pubout, ofstream& privout, string& oid = Prime256v1)
{
    //Check which key type to use
    EC_Domain_Params params = get_EC_Dom_Pars_by_oid (oid);
    ECDSA_PrivateKey privKey (rng, params);
    //Write the key to the specified file
    pubout << X509::PEM_encode (privKey);
    privout << PKCS8::PEM_encode (privKey);
}

void signECDSA ()
{

}

#endif	/* _ECDSA_HPP */

