
#include "globals.hpp"

EasyBotanWindow::EasyBotanWindow()
: Gtk::Window(),
        genKeysTable()
{
    //Set the title
    set_title("EasyBotan");
    //Add the notebook tabs
    mainNotebook.append_page(genKeysTable, "Generate keys");
    //Add the notebook to the window
    add(mainNotebook);
    //Show all widgets
    show_all_children();
}

GenerateKeysTable::GenerateKeysTable ()
: Gtk::Table (),
algorithmLabel ("Algorithm:"),
algorithmComboBox (),
sizeLabel ("Keysize:"),
sizeComboBox (),
pubOutFileChooser ("Public key file",Gtk::FILE_CHOOSER_ACTION_SAVE),
privOutFileChooser ("Private key file",Gtk::FILE_CHOOSER_ACTION_SAVE),
okButton ("OK")
{
    //Algorithm
    algorithmComboBox.append_text("RSA");
    algorithmComboBox.append_text("DSA");
    algorithmComboBox.append_text("ECDSA");
    algorithmComboBox.append_text("ElGamal");
    algorithmComboBox.append_text("Diffie-Hellman");
    attach(algorithmLabel, 0, 1, 0, 1);
    attach(algorithmComboBox, 1, 2, 0, 1);
    //Keysize
    sizeComboBox.append_text("256");
    sizeComboBox.append_text("512");
    sizeComboBox.append_text("1024");
    sizeComboBox.append_text("2048");
    sizeComboBox.append_text("4096");
    sizeComboBox.append_text("8192");
    sizeComboBox.append_text("16384");
    sizeComboBox.append_text("32768");
    attach(sizeLabel, 0, 1, 1, 2);
    attach(sizeComboBox, 1, 2, 1, 2);
    //Public key output
    attach(pubOutFileChooser, 1, 2, 2, 3);
    //Private key output
    attach(privOutFileChooser, 1, 2, 3, 4);
    //OK Button
    attach(okButton, 0, 2, 4, 5);
    //Connect the signals
    okButton.signal_clicked().connect(sigc::mem_fun(*this,&GenerateKeysTable::okButtonClicked));
    //Show all children
    show_all_children();
}

void GenerateKeysTable::okButtonClicked()
{
    //Check which algorithm to use
    ustring algorithm = algorithmComboBox.get_active_text();
    //Get the public key output file
    ustring pubFilename = pubOutFileChooser.get_filename();
    //Get the private key output file
    ustring privFilename = privOutFileChooser.get_filename();
    //Call the right function
    if (algorithm == "RSA")
        {
            
        }
}