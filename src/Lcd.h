#ifndef LCD_H
#define LCD_H

#include <string>
#include <termios.h>

struct Command;

class Lcd {
    public:
        Lcd(std::string devName, speed_t baud = B115200);
        ~Lcd();

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
