#ifndef LCD_H
#define LCD_H

#include <string>
#include <termios.h>
#include <vector>

struct Command;

class Lcd {
    public:
        Lcd(std::string devName, speed_t baud = B115200);
        ~Lcd();

        void addText(std::string text, uint8_t x = 0, uint8_t y = 0);
        void clear();
        void ping();
        void ping(std::vector<uint8_t> &data);
        void reboot();
        void setLedState();

    private:
        int _fd;
        std::string _devName;
        speed_t _baud;

        ssize_t send(Command &cmd);
};

#endif
