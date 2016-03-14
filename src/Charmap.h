#ifndef CHARMAP_H
#define CHARMAP_H

#include <unordered_map>

class Charmap {
    public:
        void lcdToAscii();
        void asciiToLcd();

    private:
        std::unordered_map<uint8_t, uint8_t> map;
};

#endif
