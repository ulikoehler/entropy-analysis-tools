/* 
 * File:   main.cpp
 * Author: uli
 *
 * Created on 9. Januar 2009, 20:53
 */

#include <stdlib.h>
#include <boost/program_options.hpp>

using namespace boost;
using namespace std;

/*
 * 
 */
int
main (int argc, char** argv)
{
    Botan::LibraryInitializer init;
    AutoSeededRNG

    string tlAction(argv[1]); //Toplevel action
    argc -= 2;//Program name and toplevel action

    if(tlAction == "ec")
        {
            
        }
    

    return (EXIT_SUCCESS);
}

