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
    GenerateKeysTable ();
    //TODO comment
    Gtk::Label algorithmLabel;
    Gtk::ComboBoxText algorithmComboBox; //Which algorithm to use, e.g. RSA or DSA
    Gtk::Label sizeLabel; //in bits
    Gtk::ComboBoxText sizeComboBox;
    Gtk::FileChooserButton pubOutFileChooser; //Already contains the label (title)
    Gtk::FileChooserButton privOutFileChooser; //Already contains the label (title)
    Gtk::Button okButton;
    
    void okButtonClicked();
};

struct EasyBotanWindow : Gtk::Window
{
    EasyBotanWindow();
    Gtk::Notebook mainNotebook;
    GenerateKeysTable genKeysTable;
};

#endif	/* _GUI_HPP */

