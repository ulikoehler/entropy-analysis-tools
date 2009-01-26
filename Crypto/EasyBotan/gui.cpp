
#include "rsa.hpp"


#include "globals.hpp"

EasyBotanWindow::EasyBotanWindow ()
: Gtk::Window (),
genKeysTable (),
genRandFileTable ()
{
    //Set the title
    set_title ("EasyBotan");
    //Add the notebook tabs
    mainNotebook.append_page (genKeysTable, "Generate keys");
    mainNotebook.append_page (genRandFileTable, "Generate random file");
    //Add the notebook to the window
    add (mainNotebook);
    //Show all widgets
    show_all_children ();
    /**
     * Init the RNG member in a new thread.
     */
    Glib::Thread *cryptoInitThread = Glib::Thread::create(sigc::mem_fun(*this, &EasyBotanWindow::initCrypto), true);
}

/**
 * Inits the RNG member
 * Should be called in a separate thread to avoid a GUI displaying delay
 */
void EasyBotanWindow::initCrypto()
{
    rng = shared_ptr<AutoSeeded_RNG>(new AutoSeeded_RNG());
}

GenerateKeysTable::GenerateKeysTable ()
: Gtk::Table (),
algorithmLabel ("Algorithm:"),
algorithmComboBox (),
sizeLabel ("Keysize:"),
sizeComboBox (),
pubOutLabel ("Public key:"),
privOutLabel ("Private key:"),
pubOutFileChooser ("Public key file", Gtk::FILE_CHOOSER_ACTION_SAVE),
privOutFileChooser ("Private key file", Gtk::FILE_CHOOSER_ACTION_SAVE),
passwordLabel ("Password:"),
passwordEntry (),
okButton ("OK")
{
    /**
     * Init the GUI
     */
    //Set some options for this table
    set_spacings(5);
    //Algorithm
    algorithmComboBox.append_text("RSA");
    algorithmComboBox.append_text("DSA");
    algorithmComboBox.append_text("ECDSA");
    algorithmComboBox.append_text("ElGamal");
    algorithmComboBox.append_text("Diffie-Hellman");
    attach(algorithmLabel, 0, 1, 0, 1, FILL, EXPAND);
    attach(algorithmComboBox, 1, 2, 0, 1, FILL, EXPAND);
    //Keysize
    sizeComboBox.append_text("256");
    sizeComboBox.append_text("512");
    sizeComboBox.append_text("1024");
    sizeComboBox.append_text("2048");
    sizeComboBox.append_text("4096");
    sizeComboBox.append_text("8192");
    sizeComboBox.append_text("16384");
    sizeComboBox.append_text("32768");
    attach(sizeLabel, 0, 1, 1, 2, FILL, EXPAND);
    attach(sizeComboBox, 1, 2, 1, 2, FILL, EXPAND);
    //Public key output
    attach(pubOutLabel, 0, 1, 2, 3, FILL, EXPAND);
    attach(pubOutFileChooser, 1, 2, 2, 3, FILL, EXPAND);
    //Private key output
    attach(privOutLabel, 0, 1, 3, 4, FILL, EXPAND);
    attach(privOutFileChooser, 1, 2, 3, 4, FILL, EXPAND);
    //Password entry
    attach(passwordLabel, 0, 1, 4, 5, FILL, EXPAND);
    passwordEntry.set_visibility(false);
    attach(passwordEntry, 1, 2, 4, 5, FILL, EXPAND);
    //OK Button
    attach(okButton, 0, 2, 5, 6);
    //Connect the signals
    okButton.signal_clicked().connect(sigc::mem_fun(*this,&GenerateKeysTable::okButtonClicked));
    //Show all children
    show_all_children();
}

GenerateRandomFileTable::GenerateRandomFileTable ()
: Gtk::Table (2,2,false),
sizeHBox (false, 5),
sizeLabel ("Size:"),
sizeAdjustment (100, 0, 1000000000, 1, 100, 0),
sizeSpinButton (sizeAdjustment),
sizeSuffixComboBox (),
fileLabel ("File:"),
outputFileChooser (),
okButton ("OK")
{
    //Set some options for this table
    set_spacings(5);
    //Size suffix combo box
    sizeSuffixComboBox.append_text("Bytes");
    sizeSuffixComboBox.append_text("Kilobytes");
    sizeSuffixComboBox.append_text("Megabytes");
    sizeSuffixComboBox.append_text("Gigabytes");
    sizeSuffixComboBox.set_active (1);
    sizeHBox.pack_end(sizeSpinButton);
    sizeHBox.pack_end(sizeSuffixComboBox);
    attach(sizeLabel, 0, 1, 0, 1, FILL, EXPAND);
    attach(sizeHBox, 1, 2, 0, 1 , FILL, EXPAND);
    //OK Button
    attach(okButton, 0, 2, 2, 3, FILL, EXPAND);
    //Show all children
    show_all_children();
}

void GenerateRandomFileTable::okButtonClicked ()
{
    ustring file = outputFileChooser.get_filename();
    ulong size = sizeSpinButton.get_value_as_int();
    ustring suffix = sizeSuffixComboBox.get_active_text();
    //Apply the suffix (using bit shift)
    if(suffix == "Kilobytes")
        {
            size << 10; //*1024
        }
    else if(suffix == "Megabytes")
        {
            size << 20; //*1024*1024
        }
    else if(suffix == "Gigabytes")
        {
            size << 30; //*1024*1024*1024
        }
    generateEntropyFile (file.raw(), size);
}

void GenerateKeysTable::okButtonClicked()
{
    //Get the UI parameters
    uint keySize = lexical_cast<uint>(sizeComboBox.get_active_text ().raw());
    ustring algorithm = algorithmComboBox.get_active_text();
    ustring pubFilename = pubOutFileChooser.get_filename();
    ustring privFilename = privOutFileChooser.get_filename();
    ustring password = passwordEntry.get_text ();
    //Call the right function
    //TODO implement all
    if (algorithm == "RSA")
        {
            generateRSAKey (pubFilename.raw(), privFilename.raw(), password.raw(), keySize);
        }
    else if (algorithm == "ECDSA")
        {
            
        }
}