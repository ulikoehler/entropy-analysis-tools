/*
 * File:   random.cpp
 * Author: uli
 *
 * Created on 19. Januar 2009, 16:10
 */

#include "globals.hpp"

#define BUF_SIZE 4096

GenerateRandomFileTable::GenerateRandomFileTable ()
: Gtk::Table (),
sizeHBox (false, 5),
sizeLabel ("Size:"),
sizeAdjustment (100, 0, 1000000000, 1, 100, 0),
sizeSpinButton (sizeAdjustment),
sizeSuffixComboBox (),
fileLabel ("File:"),
outputFileChooser ("File", FILE_CHOOSER_ACTION_SAVE),
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
    attach(fileLabel, 0, 1, 1, 2, FILL, EXPAND);
    attach(outputFileChooser, 1, 2, 1, 2, FILL, EXPAND);
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

/**
 * Generates a file containing random data ("entropy")
 * @param outfile The filename to write the entropy to
 * @param size The number of bytes to write out
 */
void generateEntropyFile(string outfile, ulong size)
{    
    shared_ptr<AutoSeeded_RNG> rng = rootWindow->rng;
    /**
     * Generate the entropy in BUF_SIZE (default 4096) blocks and write the buffer content
     */
    ofstream fout(outfile.c_str(), ofstream::out | ofstream::binary); //The filename should be supplied in argv[3]
    char* buffer = new char[BUF_SIZE]; //sizeof(char) == 1
    for(;size >= BUF_SIZE;size -= BUF_SIZE) //Write all full blocks, counts down the size counter
        {
            rng->randomize ((byte*)buffer, BUF_SIZE);
            fout.write(buffer, BUF_SIZE);
        }
    /**
     * Write the last block
     * (less than BUF_SIZE bytes or none if the desired file size is divisible by BUF_SIZE)
     */
    delete buffer; //Deletes the original buffer
    if(!(size % BUF_SIZE == 0))
        {
            buffer = new char[size];
            rng->randomize ((byte*)buffer, size);
            fout.write(buffer, size);
        }
    delete buffer; //Deletes the last-block buffer
    fout.close();
}
