/* 
 * File:   gui.hpp
 * Author: uli
 *
 * Created on 25. Januar 2009, 17:30
 */

#ifndef _GUI_HPP
#define	_GUI_HPP

#include "globals.hpp"

/**
 * Provides something like the FileChooserButton but with save support
 */
struct FileChooserHBox : Gtk::HBox
{
    //Constructors
    FileChooserHBox (const ustring& title, FileChooserAction action);
    //GUI members
    Gtk::Entry fileEntry;
    Gtk::Button findButton;
    Gtk::FileChooserDialog dialog;

    //Functions
    ustring get_filename();
};

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
       FileChooserHBox pubOutFileChooser;
    Gtk::Label privOutLabel;
       FileChooserHBox privOutFileChooser;
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

