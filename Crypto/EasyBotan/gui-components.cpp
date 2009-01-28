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
    //Make the dialog open when the button is clicked
    selectFileButton.signal_clicked().connect(sigc::mem_fun(*this,&FileChooserSaveHBox::selectFileButtonClicked));
}

void
FileChooserSaveHBox::selectFileButtonClicked ()
{
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
    dialog.sh
}

ustring
FileChooserSaveHBox::get_filename ()
{
    return fileEntry.get_text ();
}