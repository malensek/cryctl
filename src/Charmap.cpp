#include "Charmap.h"

const std::unordered_map<uint8_t, uint8_t> Charmap::toLcdMap = createLcdMap();

std::unordered_map<uint8_t, uint8_t> Charmap::createLcdMap() {
    std::unordered_map<uint8_t, uint8_t> map;

    map[36 ] = 162; // $
    map[64 ] = 160; // @
    map[91 ] = 250; // [
    map[92 ] = 251; // backslash
    map[93 ] = 252; // ]
    map[94 ] = 29;  // ^
    map[95 ] = 196; // _
    map[123] = 253; // {
    map[124] = 254; // |
    map[125] = 255; // }
    map[126] = 206; // ~
    map[171] = 20;  // «
    map[187] = 21;  // »

    return map;
}
