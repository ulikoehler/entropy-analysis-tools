
/**
 * The GTKmm code is compiled only if NOGUI isn't defined.
 */
#ifndef NOGUI
#include "globals.hpp"
int
main (int argc, char *argv[])
{
    //Init Glib with thread support if neccessary
    if (!Glib::thread_supported()) {Glib::thread_init();}
    Gtk::Main mainObj (argc, argv);
    EasyBotanWindow mainWindow;
    rootWindow = &mainWindow;
    mainObj.run (mainWindow);
    return 0;
}

#endif //NOGUI
