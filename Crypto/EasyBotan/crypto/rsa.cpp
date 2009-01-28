#include "globals.hpp"

/**
 * Generates a new RSA private key.
 * @param pubname The file to write the public key to
 * @param privname The file to write the private key to
 * @param password The password to use to encrypt the private key or NULL if no password should be used
 * @param bits The key size in bits
 */
void generateRSAKey(string pubname, string privname, string password, uint bits)
{
    ofstream pubout(pubname.c_str());
    ofstream privout(privname.c_str());
    RSA_PrivateKey key = generateRSAKey(bits);
    pubout << X509::PEM_encode (key);
    if(password == NULL)
        {
            privout << PKCS8::PEM_encode (key);
        }
    else
        {
            AutoSeeded_RNG rng;
            privout << PKCS8::PEM_encode (key, rng, password);
        }
    pubout.close();
    privout.close();
}

/**
 * Generates a new RSA private key.
 * @param bits Key bits
 */
RSA_PrivateKey generateRSAKey(uint bits)
{
    AutoSeeded_RNG rng;
    RSA_PrivateKey key(rng, bits);
    return key;
}

void signRSA()
{
    //TODO implement, add to header file
}

void verifyRSA()
{
    //TODO implement, add to header file
}

void encryptRSA()
{
    //TODO implement, add to header file
}

void decryptRSA()
{
    //TODO implement, add to header file
}