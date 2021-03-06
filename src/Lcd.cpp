#include "Lcd.h"

#include <chrono>
#include <fcntl.h>
#include <iostream>
#include <thread>
#include <unistd.h>

#include "Crc16.h"
#include "Command.h"

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

Lcd::Lcd(std::string devName, speed_t baud) {
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

Lcd::~Lcd() {
    close(_fd);
    _fd = -1;
}

void Lcd::clear() {
    Command cmd;
    cmd.type = 0x06;
    cmd.length = 0;
    send(cmd);
}

void Lcd::addText(std::string text, uint8_t x, uint8_t y) {
    Command cmd;
    cmd.type = 0x1F;
    cmd.length = text.length() + 2;
    cmd.data[0] = x;
    cmd.data[1] = y;
    std::copy(text.begin(), text.end(), &cmd.data[2]);
    send(cmd);
}

void Lcd::ping() {
    Command cmd;
    cmd.type = 0x0;
    send(cmd);
}

void Lcd::ping(std::vector<uint8_t> &data) {
    Command cmd;
    cmd.type = 0x0;

    std::vector<uint8_t>::size_type len = data.size();
    if (len > 16) {
        len = 16;
    }
    cmd.length = len;

    std::copy(data.begin(), data.begin() + len, &cmd.data[0]);

    send(cmd);
}

void Lcd::setLedState() {
    Command cmd;
    cmd.type = 0x22;
    cmd.length = 2;
    cmd.data[0] = 6;
    cmd.data[1] = 100;
    send(cmd);
}

void Lcd::reboot() {
    Command cmd;
    cmd.type = 0x05;
    cmd.length = 3;
    cmd.data[0] = 8;
    cmd.data[1] = 18;
    cmd.data[2] = 99;
}

ssize_t Lcd::send(Command &cmd) {
    if (cmd.length > MAX_COMMAND_LEN) {
        return -1;
    }

    uint16_t crc = Crc16::compute(cmd);
    memcpy(&cmd.data[cmd.length], &crc, sizeof(crc));
    size_t numBytes = sizeof(cmd.data) * (cmd.length + 2) + sizeof(crc);
    ssize_t out = write(_fd, &cmd, numBytes);
    if (out == -1) {
        std::perror("Display::send()");
    }

    receive();
    return out;
}

void Lcd::receive() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    uint8_t buffer[1024];
    int bytesRead = read(_fd, &buffer, 1024);
    printf("Read %d bytes\n", bytesRead);
}


