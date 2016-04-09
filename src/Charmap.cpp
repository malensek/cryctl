#include "Charmap.h"

std::unordered_map<uint8_t, uint8_t> Charmap::toLcdMap = {
    {36,  162}, // $
    {64,  160}, // @
    {91,  250}, // [
    {92,  251}, // backslash
    {93,  252}, // ]
    {94,  29},  // ^
    {95,  196}, // _
    {123, 253}, // {
    {124, 254}, // |
    {125, 255}, // }
    {126, 206}, // ~
};
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

    return map;
}
