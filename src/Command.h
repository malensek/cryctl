#ifndef COMMAND_H
#define COMMAND_H

#include <cstdint>

struct Command {
    uint8_t type;
    uint8_t length;
    uint8_t data[24];
    uint16_t crc;
};

#endif
