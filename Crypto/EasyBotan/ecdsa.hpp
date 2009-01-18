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
 * A hashmap is used here to make it a bit faster because of decreased lookup complexity
 */
static unordered_map<string, string> oids;

/**
 * Must be called before a main signing function call.
 * initizalizes the oid map.
 */
inline void initECDSA()
{
    oids["Prime256v1"] = "1.2.840.10045.3.1.7";
    oids["Prime239v3"] = "1.2.840.10045.3.1.6";
    oids["Prime239v2"] = "1.2.840.10045.3.1.5";
    oids["Prime239v1"] = "1.2.840.10045.3.1.4";
    oids["Prime192v3"] = "1.2.840.10045.3.1.3";
    oids["Prime192v2"] = "1.2.840.10045.3.1.2";
    oids["Prime192v1"] = "1.2.840.10045.3.1.1";
    oids["brainpoolP512r1"] = "1.3.36.3.3.2.8.1.1.13";
    oids["brainpoolP384r1"] = "1.3.36.3.3.2.8.1.1.11";
    oids["brainpoolP320r1"] = "1.3.36.3.3.2.8.1.1.9";
    oids["brainpoolP256r1"] = "1.3.36.3.3.2.8.1.1.7";
    oids["brainpoolP224r1"] = "1.3.36.3.3.2.8.1.1.5";
    oids["brainpoolP192r1"] = "1.3.36.3.3.2.8.1.1.3";
    oids["brainpoolP160r1"] = "1.3.36.3.3.2.8.1.1.1";
    oids["NISTP521"] = "1.3.6.1.4.1.8301.3.1.2.9.0.38";
    oids["secp521r1"] = "1.3.132.0.35";
    oids["secp384r1"] = "1.3.132.0.34";
    oids["secp256k1"] = "1.3.132.0.10";
    oids["secp224r1"] = "1.3.132.0.33";
    oids["secp224k1"] = "1.3.132.0.32";
    oids["secp192k1"] = "1.3.132.0.31";
    oids["secp160r2"] = "1.3.132.0.30";
    oids["secp160k1"] = "1.3.132.0.9";
    oids["secp128r2"] = "1.3.132.0.29";
    oids["secp128r1"] = "1.3.132.0.28";
    oids["secp112r2"] = "1.3.132.0.7";
    oids["secp112r1"] = "1.3.132.0.6";
}

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
            string name(strlwr(argv[3]));
            string oid = oids[name];


        }
}

/**
 * Toplevel function to generate an ECDSA key
 */
void generateECDSAKeyPair(string& out, string& oid)
{
    fstream pubout(out, fstream::out);
    fstream privout(out, fstream::out);

    //Call a lower level function to generate the key
    generateECDSAKeyPair(pubout, privout, Prime256v1);

    pubout.close();
    privout.close();
}

/**
 * Low-level signing function
 * default OID is for curve Prime256v1
 */
void
generateECDSAKeyPair (ofstream& pubout, ofstream& privout, string& oid = "1.2.840.10045.3.1.7")
{
    //Check which key type to use
    EC_Domain_Params params = get_EC_Dom_Pars_by_oid (oid);e
    ECDSA_PrivateKey privKey (rng, params);
    //Write the key to the specified file
    pubout << X509::PEM_encode (privKey);
    privout << PKCS8::PEM_encode (privKey);
}

#endif	/* _ECDSA_HPP */

