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
    Gtk::FileChooserButton pubOutFileChooser;
    Gtk::Label privOutLabel;
    Gtk::FileChooserButton privOutFileChooser;
    Gtk::Label passwordLabel;
    Gtk::Entry passwordEntry;
    Gtk::Button okButton;

    void okButtonClicked();
};

struct GenerateRandomFileTable : Gtk::Table
{
    //Constructors
    GenerateRandomFileTable ();
    //GUI members
    Gtk::HBox sizeHBox;
    Gtk::Label sizeLabel;
    Gtk::Adjustment sizeAdjustment;
    Gtk::SpinButton sizeSpinButton;
    Gtk::ComboBoxText sizeSuffixComboBox;
    Gtk::Label fileLabel;
    Gtk::FileChooserButton outputFileChooser;
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

