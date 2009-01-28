/* 
 * File:   gui.hpp
 * Author: uli
 *
 * Created on 25. Januar 2009, 17:30
 */

#ifndef _GUI_HPP
#define	_GUI_HPP

#include "globals.hpp"


struct GenerateKeysTable : Gtk::Table
{
    //Constructors
    GenerateKeysTable ();
    //GUI members
    Gtk::Label algorithmLabel;
    Gtk::ComboBoxText algorithmComboBox; //Which algorithm to use, e.g. RSA or DSA
    Gtk::Label sizeLabel; //in bits
    Gtk::ComboBoxText sizeComboBox;
    Gtk::Label pubOutLabel;
       FileChooserSaveHBox pubOutFileChooser;
    Gtk::Label privOutLabel;
       FileChooserSaveHBox privOutFileChooser;
    Gtk::Label passwordLabel;
    Gtk::Entry passwordEntry;
    Gtk::Button okButton;

    void okButtonClicked();
};

struct EasyBotanWindow : Gtk::Window
{
    EasyBotanWindow();
    Gtk::Notebook mainNotebook;
    GenerateKeysTable genKeysTable;
    GenerateRandomFileTable genRandFileTable;
    //Crypto members
    shared_ptr<AutoSeeded_RNG> rng;
    
    void initCrypto();
};

#endif	/* _GUI_HPP */

