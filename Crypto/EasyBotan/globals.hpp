/* 
 * File:   globals.hpp
 * Author: uli
 *
 * Created on 9. Januar 2009, 22:35
 */

#ifndef _GLOBALS_HPP
#define	_GLOBALS_HPP

#include <fstream>
#include <botan/botan.h>
#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <boost/algorithm/string/case_conv.hpp> //Contains to_lowercase(string)
#include <botan/botan.h>
#include <botan/ecdsa.h>
#include <botan/pubkey.h>
#include <botan/look_pk.h>
#include <memory> //Needed by botan
#include <iostream>
#include <string>

using namespace std;
using namespace boost;
using namespace Botan;

#include "md.hpp"
#include "ecdsa.hpp"

#endif	/* _GLOBALS_HPP */

