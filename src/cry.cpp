
#include "Lcd.h"

int main (int argc, char *argv[]) {

    Lcd l("/dev/ttyU0");
    l.clear();
    l.addText("hello world!", 0, 1);
    l.addText("hello world! (again)", 0, 2);
    l.setLedState();

}


