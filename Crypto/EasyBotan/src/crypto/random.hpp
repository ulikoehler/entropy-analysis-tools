/* 
 * File:   random.hpp
 * Author: uli
 *
 * Created on 19. Januar 2009, 16:10
 */

#ifndef _RANDOM_HPP
#define	_RANDOM_HPP

#include "../globals.hpp"

/**
 * Generates a file containing random data ("entropy")
 * @param outfile The filename to write the entropy to
 * @param size The number of bytes to write out
 */
void generateEntropyFile(string outfile, ulong size);

/**
 * GUI section
 */
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
         FileChooserSaveHBox outputFileChooser;
    Gtk::Button okButton;

    void okButtonClicked();
};

#endif	/* _RANDOM_HPP */

