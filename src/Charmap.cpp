#include "Charmap.h"


const std::unordered_map<uint8_t, uint8_t> Charmap::toLcdMap = {
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
