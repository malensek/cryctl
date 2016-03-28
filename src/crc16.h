#ifndef _CRC16_H
#define _CRC16_H

#include <stdint.h>

class CRC16 {
    public:
        static uint16_t compute(unsigned char *data);

    private:
        static const uint16_t lut[256];

};

#endif
