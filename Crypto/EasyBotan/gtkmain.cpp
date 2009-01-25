
/**
 * The GTKmm code is compiled only if NOGUI isn't defined.
 */
#ifndef NOGUI
#include "globals.hpp"
int
main (int argc, char *argv[])
{
    Gtk::Main mainObj (argc, argv);
    EasyBotanWindow mainWindow;
    mainObj.run (mainWindow);
    return 0;
}

#endif //NOGUI
