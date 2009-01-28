#include "globals.hpp"

FileChooserSaveHBox::FileChooserSaveHBox (const ustring& title)
: Gtk::HBox (false, 3),
fileEntry (),
selectFileButton (Gtk::Stock::SAVE_AS),
dialog (title, FILE_CHOOSER_ACTION_SAVE)
{
    //Add the buttons to the dialog
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);
    //Add the widgets to the box (= this)
    pack_end (selectFileButton);
    pack_end (fileEntry);
    //Connect the signals
    selectFileButton.signal_clicked ().connect (sigc::mem_fun (*this, &FileChooserSaveHBox::selectFileButtonClicked));
}

ustring
FileChooserSaveHBox::get_filename ()
{
    return fileEntry.get_text ();
}

void FileChooserSaveHBox::set_filename (const ustring& filename)
{
    fileEntry.set_text(filename);
    dialog.set_filename (filename);
}

void
FileChooserSaveHBox::selectFileButtonClicked ()
{
    dialog.set_filename(fileEntry.get_text());
    int result = dialog.run ();
    switch (result)
        {
        case Gtk::RESPONSE_OK :
            {
                fileEntry.set_text (dialog.get_filename ());
                break;
            }
        default: break;
        }
    dialog.hide ();
}