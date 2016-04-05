#ifndef CRC16_H
#define CRC16_H

#include <cstdint>
#include <cstdlib>

struct Command;

class Crc16 {

    public:
        static uint16_t compute(const Command &cmd);
        static uint16_t compute(const uint8_t *data, const size_t len);

    private:
        static const uint16_t lut[256];

};

#endif
