
#include "Display.h"

int main (int argc, char *argv[]) {

    Display d("/dev/ttyU0");
    d.clear();
    d.addText("--  sigma.lan  --", 0, 1);
    d.addText("-- uptime: 24d --", 0, 2);
    d.setLedState();

}


