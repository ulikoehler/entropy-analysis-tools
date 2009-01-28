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
pubOutFileChooser ("Public key file"),
privOutFileChooser ("Private key file"),
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
    //Set the default selections/values
    algorithmComboBox.set_active (0);
    sizeComboBox.set_active (3); //1024
    pubOutFileChooser.set_filename("pubkey.pem");
    privOutFileChooser.set_filename("privkey.pem");
    //Show all children
    show_all_children();
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