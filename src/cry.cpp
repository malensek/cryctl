#include <cstdio>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <string>
#include <termios.h>
#include <unistd.h>
#ifndef OFILL
#define OFILL   0000100
#endif
#ifndef OFDEL
#define OFDEL   0000200
#endif
#ifndef NLDLY
#define NLDLY   0000400
#endif
#ifndef CRDLY
#define CRDLY   0003000
#endif
#ifndef BSDLY
#define BSDLY   0020000
#endif
#ifndef VTDLY
#define VTDLY   0040000
#endif
#ifndef FFDLY
#define FFDLY   0100000
#endif

#include "Crc16.h"

struct Command {
    uint8_t type;
    uint8_t length;
    uint8_t data[22];
    uint16_t crc;
};

class Display {
    public:
        Display(std::string devName, speed_t baud = B115200) {
            _devName = devName;
            _baud = baud;
            std::cout << "Init device: " << _devName.c_str() << std::endl;

            _fd = open(_devName.c_str(), O_NOCTTY | O_NONBLOCK | O_RDWR );
            if (_fd == -1) {
                std::perror("Display():open");
            }

            struct termios term;
            tcgetattr(_fd, &term);

            term.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|INPCK|ISTRIP|INLCR|IGNCR|ICRNL
                    |IXON|IXOFF);
            term.c_iflag |= IGNPAR;

            //output modes
            term.c_oflag &= ~(OPOST|ONLCR|OCRNL|ONOCR|ONLRET|OFILL
                    |OFDEL|NLDLY|CRDLY|TABDLY|BSDLY|VTDLY|FFDLY);

            //control modes
            term.c_cflag &= ~(CSIZE|PARENB|PARODD|HUPCL|CRTSCTS);
            term.c_cflag |= CREAD|CS8|CSTOPB|CLOCAL;

            //local modes
            term.c_lflag &= ~(ISIG|ICANON|IEXTEN|ECHO);
            term.c_lflag |= NOFLSH;

            cfsetospeed(&term, baud);
            cfsetispeed(&term, baud);

            //set new device settings
            if(tcsetattr(_fd, TCSANOW, &term) == -1) {
                std::perror("Display():tcsetattr");
            }

        }

        ~Display() {
            close(_fd);
            _fd = -1;
        }

        void clear() {
            uint8_t data[4] = { 0 };
            data[0] = 0x06;
            data[1] = 0;

            uint16_t crc = Crc16::compute(data, 2);
            data[3] = (0xFF00 & crc) >> 8;
            data[2] = 0x00FF & crc;

            write(_fd, data, 4);

        }

        void text() {
            std::string text("hello world!");
            uint8_t data[1 + 1 + 22 + 2] = { 0 };
            data[0] = 0x1F;
            data[1] = text.length() + 2;
            data[2] = 0;
            data[3] = 1;
            std::copy(text.begin(), text.end(), &data[4]);
            uint16_t crc = Crc16::compute(data, data[1] + 2);
            data[16] = 0xFF & crc;
            data[17] = (0xFF00 & crc) >> 8;

            write(_fd, data, 18);

        }

    private:
        int _fd;
        std::string _devName;
        speed_t _baud;

};

int main (int argc, char *argv[]) {

    Display d("/dev/ttyU0");
    d.clear();
    d.text();

}


