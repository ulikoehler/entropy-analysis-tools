/* 
 * File:   ectool.cpp
 *
 * Main ectool file: ECDSA signing tool
 *
 * Created on 17. Januar 2009, 16:24
 */

#include <stdlib.h>
#include <botan/botan.h>
#include <botan/ecdsa.h>
#include <botan/pubkey.h>
#include <botan/look_pk.h>
#include <boost/program_options.hpp>

using namespace std;
using namespace boost;

/**
 * Name-OID-Associations
 */
#define Prime256v1 "1.2.840.10045.3.1.7"

/*
 * 
 */
int
main (int argc, char** argv)
{
    LibraryInitializizer init;
    AutoSeededRNG rng;

    variables_map vm;

    string action;
    string input;
    string output;
    uint shaSize; //Which keysize to use for signature
    //Init the program options
    options_description options ("Options");
    options.add_options()
            ("help,h", "Display help")
            ("action,-a", value<string>(&action)->default_value("sign"), "Action")
            ("output,u", value<string>(&output), "Output file (suffices .pub/.priv are added)")
            ("input,i", value<string>(&input),  "Input file (")
            ("verbose,v", "Produce more output")
            ("shasize,s", "Which SHA length to use for signing (160/224/256/512)")


    //Initialize the positional options
    positional_options_description p;
    p.add("action",1);
    p.add("output",1);
    p.add("input",1);

    //Parse the options
    store (command_line_parser (argc, argv).
           options (allowedOptions).positional (p).run (), vm);
    notify (vm);

    //Check if the user has requested help
    if (vm.count ("help"))
        {
            cout << allowedOptions << "\n";
            return 1;
        }

    //Check if the user has specified input
    if (!vm.count ("output"))
        {
            cout << "No output file specified!\n" << allowedOptions << "\n";
            return 2;
        }

    uint verbose = vm.count("verbose");

    if(action == "Generate")
        {
            //Check which key type to use
            EC_Domain_Params params = get_EC_Dom_Pars_by_oid(Prime256v1);
            ECDSA_PrivateKey privKey(rng, params);
            ECDSA_PublicKey ecdsa_pub = ecdsa;
            //Write the key to the specified file
            fstream fpub((output+".pub)").c_str(), fstream::out);
            fstream fpriv((output+".pub)").c_str(), fstream::out);
            fpub << X509::PEM_encode(ecdsa);
            fpriv << PKCS8::PEM_encode(ecdsa);
        }

    return (EXIT_SUCCESS);
}

