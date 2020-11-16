#pragma once

#include <cstdint>
#include <array>

#include "olc6502.hpp"

class Bus {
public:
    Bus();
    ~Bus();
    
public:
    olc6502 cpu;
    
    //virtual ram as memory buffer
    std::array<uint8_t, 64 * 1024> ram;
    
public: // Bus Read & Write
    uint8_t read(uint16_t a, bool bReadOnly=false);
    void write(uint16_t a, uint8_t d);
};
