/* 
 * File:   gui-components.hpp
 * Author: uli
 *
 * Contains derived GUI widget declarations
 * Source code is in gui.cpp!
 *
 * Created on 27. Januar 2009, 18:29
 */

#ifndef _GUI_COMPONENTS_HPP
#define	_GUI_COMPONENTS_HPP

#include "globals.hpp"

/**
 * Provides something like the FileChooserButton but with save support
 * When the user should open a file FileChooserButton is used preferably
 */
struct FileChooserSaveHBox : Gtk::HBox
{
    //Constructors
    FileChooserSaveHBox (const ustring& title);
    //GUI members
    Gtk::Entry fileEntry;
    Gtk::Button selectFileButton;
    Gtk::FileChooserDialog dialog;

    //Functions
    ustring get_filename();
    
private:
    void selectFileButtonClicked();
};

#endif	/* _GUI_COMPONENTS_HPP */

