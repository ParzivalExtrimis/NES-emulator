#include "Bus.hpp"

Bus::Bus() {
   // connect the cpu onto bus
   cpu.connectBus(this);
   
   //clear ram < init >
   for(auto &i : ram) { i = 0x00; }
}

Bus::~Bus() {}

uint8_t Bus::read(uint16_t a, bool bReadOnly) {
   if(a >= 0x0000 && a <= 0xFFFF)
       return ram[a];
   return 0x00;
}

void Bus::write(uint16_t a, uint8_t d) {
   if (a >= 0x0000 && a <= 0xFFFF) {
       ram[a] = d;
   }
}
