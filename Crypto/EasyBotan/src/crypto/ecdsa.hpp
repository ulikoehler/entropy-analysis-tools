/*
 * File:   ecdsa.hpp
 * Author: uli
 *
 * Created on 17. Januar 2009, 16:58
 */

#include "../globals.hpp"

#ifndef _ECDSA_HPP
#define	_ECDSA_HPP

/**
 * Must be called before a main signing function call.
 * Initizalizes the oid map.
 */
void initECDSA ();

/**
 * ECDSA signing function called by main
 * Argc decreased by the number options already parsed
 * and argv must be passed
 */
void ecdsaMain (int argc, char** argv);

/**
 * Returns a list of all supported curves
 */
std::List<string> listECDSACurves();

/**
 * Toplevel function to generate an ECDSA key
 */
void generateECDSAKeyPair (string& pubout, string& privout, string& oid);

/**
 * Toplevel function to generate an ECDSA key
 */
void generateECDSAKeyPair (string& out, string& oid);

/**
 * Low-level signing function
 */
void
generateECDSAKeyPair (ofstream& pubout, ofstream& privout, string& oid);

#endif	/* _ECDSA_HPP */

