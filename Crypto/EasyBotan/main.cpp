/* 
 * File:   main.cpp
 * Author: uli
 *
 * Created on 9. Januar 2009, 20:53
 */
#include "globals.hpp"

/*
 * 
 */
int
main (int argc, char** argv)
{
    LibraryInitializer init;

    string tlAction(argv[1]); //Toplevel action
    argc -= 2;//Program name and toplevel action

    if(tlAction == "ecdsa")
        {
            initECDSA();
            ecdsaMain(argc, argv);
        }
    else if(tlAction == "md" || tlAction == "hash")
        {
            mdMain(argc, argv);
        }
    else if(tlAction == "rand")
        {
            randomMain(argc, argv);
        }
    else //No toplevel action
        {
            cout << "Please specify an action!" << endl;
            return (2);
        }
    
    return(EXIT_SUCCESS);
}

