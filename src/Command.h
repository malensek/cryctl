#ifndef COMMAND_H
#define COMMAND_H

#include <cstdint>

#define MAX_COMMAND_LEN 22

struct Command {
    uint8_t type;
    uint8_t length;
    uint8_t data[MAX_COMMAND_LEN];
    uint16_t crc;
};

#endif
