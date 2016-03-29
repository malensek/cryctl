#ifndef _CRC16_H
#define _CRC16_H

#include <cstdlib>
#include <stdint.h>

class Crc16 {

    public:
        static uint16_t compute(uint8_t *data, size_t len);

    private:
        static const uint16_t lut[256];

};

#endif
