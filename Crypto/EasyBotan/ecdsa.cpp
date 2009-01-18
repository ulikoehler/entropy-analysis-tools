/*
 * File:   ecdsa.hpp
 * Author: uli
 *
 * Created on 17. Januar 2009, 16:58
 */

#include "globals.hpp"

/**
 * Name-OID-Associations
 * A hashmap is used here to make it a bit faster because of decreased lookup complexity
 */
typedef unordered_map<string, string> oid_map;
static oid_map oids;

/**
 * Must be called before a main signing function call.
 * initizalizes the oid map.
 */
void initECDSA()
{
    /**
     * All keys must be lowercase to support lowercased user-input
     */
    oids["prime256v1"] = "1.2.840.10045.3.1.7";
    oids["prime239v3"] = "1.2.840.10045.3.1.6";
    oids["prime239v2"] = "1.2.840.10045.3.1.5";
    oids["prime239v1"] = "1.2.840.10045.3.1.4";
    oids["prime192v3"] = "1.2.840.10045.3.1.3";
    oids["prime192v2"] = "1.2.840.10045.3.1.2";
    oids["prime192v1"] = "1.2.840.10045.3.1.1";
    oids["brainpoolp512r1"] = "1.3.36.3.3.2.8.1.1.13";
    oids["brainpoolp384r1"] = "1.3.36.3.3.2.8.1.1.11";
    oids["brainpoolp320r1"] = "1.3.36.3.3.2.8.1.1.9";
    oids["brainpoolp256r1"] = "1.3.36.3.3.2.8.1.1.7";
    oids["brainpoolp224r1"] = "1.3.36.3.3.2.8.1.1.5";
    oids["brainpoolp192r1"] = "1.3.36.3.3.2.8.1.1.3";
    oids["brainpoolp160r1"] = "1.3.36.3.3.2.8.1.1.1";
    oids["nistp521"] = "1.3.6.1.4.1.8301.3.1.2.9.0.38";
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

/**
 * Lists the supported curves
 * //TODO: Find a way to print the out correctly cased
 * Not listed in the header file
 */
inline void listSupportedCurves()
{
    foreach(oid_map::value_type i, oids)
    {
        cout<<i.first<<"\n";
    }
}

void ecdsaMain(int argc, char** argv)
{
    string subAction = argv[2]; //Second level action
    argc--;
    if(subAction == "generate" || subAction == "gen")
        {
            /**
             * Check if there are enough arguments for:
             * -curve
             * -output file
             */
            if(argc < 2)
                {
                    cout << "Not enough arguments!" << endl;
                    exit(1);
                }
            /**
             * Check which curve to use
             */
            //TODO maybe we can optimize out some of these declarations
            string out = argv[4];
            string curveName = argv[3];
            to_lower(curveName);
            generateECDSAKeyPair (out, oids[curveName]);
        }
    else if(subAction == "list")
        {
            listSupportedCurves ();
        }
}


/**
 * Toplevel function to generate an ECDSA key
 */
void generateECDSAKeyPair(string& out, string& oid)
{
    ofstream pubout((out + ".pub").c_str());
    ofstream privout((out + ".priv").c_str());

    //Call a lower level function to generate the key
    generateECDSAKeyPair(pubout, privout, oid);

    pubout.close();
    privout.close();
}

/**
 * Low-level signing function
 * default OID is for curve prime256v1
 */
void
generateECDSAKeyPair (ofstream& pubout, ofstream& privout, string& oid)
{
    AutoSeeded_RNG rng;
    //Check which key type to use
    EC_Domain_Params params = get_EC_Dom_Pars_by_oid (oid);
    ECDSA_PrivateKey privKey (rng, params);
    //Write the key to the specified file
    pubout << X509::PEM_encode (privKey);
    privout << PKCS8::PEM_encode (privKey);

    cout << "ECDSA key pair generation finished";
}


