/*
* File: highlevel.hpp
* Author: uli
*
* This file contains some high level 'envelope' functions
*
* Created on 9. Januar 2009, 23:06
*/

#include <globals.hpp>

#ifndef _HIGHLEVEL_HPP
#define  _HIGHLEVEL_HPP

/////////////////////////////////////////
/////////////////////////////////////////
/////////Symmetric cryptography//////////
/////////////////////////////////////////
/////////////////////////////////////////
/**
* A fully parametrized symmetric string encryption function
* Encrypts using the specified algorithm and CBC+PKCS7.
* Format as follows (//TODO ASN.1 Notation required):
* Base64
* {
* n bytes salt (parameter)
* 32 bytes IV
* message
* }
*/
string cryptTextUnauthenticated(string& plaintext, string& password, bool decrypt = false, string& algorithm = "Twofish", uint saltSize = 24)
{
    AutoSeeded_RNG rng;
    string fullAlgorithmName = algorithm + "/CBC/PKCS7";

    //Generate a random salt
    SecureVector<byte> salt(rng, saltSize);

    //Check whether whe have to decrypt
    Cipher_Dir direction = ENCRYPTION;
    if(decrypt) {direction = DECRYPTION;}

    SymmetricKey key = OctetString(hashRaw("SHA-256", password, salt));
    InitializationVector iv(rng, 32);

    Pipe encryptionPipe(new Chain(get_cipher(fullAlgorithmName, key, iv, direction)));
    encryptionPipe.start_msg();
    encryptionPipe.write(plaintext);
    encryptionPipe.end_msg();
    SecureVector<byte> encryptedData = encryptionPipe.read_all(0);

    Pipe base64Pipe(new Base64_Encoder);
    base64Pipe.start_msg ();
    base64Pipe.write(salt);
    base64Pipe.write(iv);
    base64Pipe.write(encryptedData);
    base64Pipe.end_msg();

    return base64Pipe.read_all_as_string (0);
}

#endif  /* _HIGHLEVEL_HPP */
 