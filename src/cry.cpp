#include <cstdio>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <string>
#include <termios.h>
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

    private:
        int _fd;
        std::string _devName;
        speed_t _baud;

};

int main (int argc, char *argv[]) {

    Display d("/dev/tty");
}


