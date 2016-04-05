#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <termios.h>

struct Command;

class Display {
    public:
        Display(std::string devName, speed_t baud = B115200);
        ~Display();

        void addText(std::string text, int x = 0, int y = 0);
        void clear();
        void setLedState();

    private:
        int _fd;
        std::string _devName;
        speed_t _baud;

        ssize_t send(Command &cmd);
};

#endif
