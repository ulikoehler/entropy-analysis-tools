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
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/case_conv.hpp> //Contains to_lowercase(string)
#include <boost/algorithm/string/predicate.hpp>
#include <boost/foreach.hpp>
#include <botan/rsa.h>
#include <botan/ecdsa.h>
#include <botan/pubkey.h>
#include <botan/look_pk.h>
#include <memory> //Needed by botan
#include <iostream>
#include <string>
//GUI
#ifndef NOGUI
    #include <gtkmm-2.4/gtkmm.h>
#endif //NOGUI

/**
 * Namespaces
 */
using namespace Gtk;
using namespace Glib;
using namespace std;
using namespace boost;
using namespace Botan;

/**
 * Defines and typedefs
 */
#define foreach BOOST_FOREACH

#include "md.hpp"
#include "ecdsa.hpp"
#include "random.hpp"
#include "rsa.hpp"
#include "gui.hpp"

/**
 * Global variables
 */
static EasyBotanWindow *rootWindow; //Provides an AutoSeeded_RNG


#endif	/* _GLOBALS_HPP */

