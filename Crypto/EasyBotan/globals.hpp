/* 
 * File:   globals.hpp
 * Author: uli
 *
 * Created on 9. Januar 2009, 22:35
 */

#ifndef _GLOBALS_HPP
#define	_GLOBALS_HPP

#include <fstream> //Include iostream and string
#include <botan/botan.h>
#include <boost/shared_ptr.hpp>
#include <boost/unordered_set.hpp>

using namespace Botan;
AutoSeededRNG* rng;

#include "md.hpp"
#include "ecdsa.hpp"

#endif	/* _GLOBALS_HPP */

