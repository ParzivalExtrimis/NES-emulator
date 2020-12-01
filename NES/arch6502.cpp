#include "arch6502.hpp"
#include "Bus.hpp"
#define arch arch6502

arch::arch() {
   //lookup table
   using a = arch6502;

   lookup = {
       { "BRK", &a::BRK, &a::IMM, 7 },{ "ORA", &a::ORA, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::ZPO, 3 },{ "ASL", &a::ASL, &a::ZPO, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHP", &a::PHP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::IMM, 2 },{ "ASL", &a::ASL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABS, 4 },{ "ASL", &a::ASL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
       { "BPL", &a::BPL, &a::REL, 2 },{ "ORA", &a::ORA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ZPX, 4 },{ "ASL", &a::ASL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLC", &a::CLC, &a::IMP, 2 },{ "ORA", &a::ORA, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABX, 4 },{ "ASL", &a::ASL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
       { "JSR", &a::JSR, &a::ABS, 6 },{ "AND", &a::AND, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "BIT", &a::BIT, &a::ZPO, 3 },{ "AND", &a::AND, &a::ZPO, 3 },{ "ROL", &a::ROL, &a::ZPO, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLP", &a::PLP, &a::IMP, 4 },{ "AND", &a::AND, &a::IMM, 2 },{ "ROL", &a::ROL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "BIT", &a::BIT, &a::ABS, 4 },{ "AND", &a::AND, &a::ABS, 4 },{ "ROL", &a::ROL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
       { "BMI", &a::BMI, &a::REL, 2 },{ "AND", &a::AND, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ZPX, 4 },{ "ROL", &a::ROL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEC", &a::SEC, &a::IMP, 2 },{ "AND", &a::AND, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ABX, 4 },{ "ROL", &a::ROL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
       { "RTI", &a::RTI, &a::IMP, 6 },{ "EOR", &a::EOR, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "EOR", &a::EOR, &a::ZPO, 3 },{ "LSR", &a::LSR, &a::ZPO, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHA", &a::PHA, &a::IMP, 3 },{ "EOR", &a::EOR, &a::IMM, 2 },{ "LSR", &a::LSR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::ABS, 3 },{ "EOR", &a::EOR, &a::ABS, 4 },{ "LSR", &a::LSR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
       { "BVC", &a::BVC, &a::REL, 2 },{ "EOR", &a::EOR, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ZPX, 4 },{ "LSR", &a::LSR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLI", &a::CLI, &a::IMP, 2 },{ "EOR", &a::EOR, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ABX, 4 },{ "LSR", &a::LSR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
       { "RTS", &a::RTS, &a::IMP, 6 },{ "ADC", &a::ADC, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ADC", &a::ADC, &a::ZPO, 3 },{ "ROR", &a::ROR, &a::ZPO, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLA", &a::PLA, &a::IMP, 4 },{ "ADC", &a::ADC, &a::IMM, 2 },{ "ROR", &a::ROR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::IND, 5 },{ "ADC", &a::ADC, &a::ABS, 4 },{ "ROR", &a::ROR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
       { "BVS", &a::BVS, &a::REL, 2 },{ "ADC", &a::ADC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ZPX, 4 },{ "ROR", &a::ROR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEI", &a::SEI, &a::IMP, 2 },{ "ADC", &a::ADC, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ABX, 4 },{ "ROR", &a::ROR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
       { "???", &a::NOP, &a::IMP, 2 },{ "STA", &a::STA, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZPO, 3 },{ "STA", &a::STA, &a::ZPO, 3 },{ "STX", &a::STX, &a::ZPO, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "DEY", &a::DEY, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 2 },{ "TXA", &a::TXA, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "STY", &a::STY, &a::ABS, 4 },{ "STA", &a::STA, &a::ABS, 4 },{ "STX", &a::STX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
       { "BCC", &a::BCC, &a::REL, 2 },{ "STA", &a::STA, &a::IZY, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZPX, 4 },{ "STA", &a::STA, &a::ZPX, 4 },{ "STX", &a::STX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "TYA", &a::TYA, &a::IMP, 2 },{ "STA", &a::STA, &a::ABY, 5 },{ "TXS", &a::TXS, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::NOP, &a::IMP, 5 },{ "STA", &a::STA, &a::ABX, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::XXX, &a::IMP, 5 },
       { "LDY", &a::LDY, &a::IMM, 2 },{ "LDA", &a::LDA, &a::IZX, 6 },{ "LDX", &a::LDX, &a::IMM, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "LDY", &a::LDY, &a::ZPO, 3 },{ "LDA", &a::LDA, &a::ZPO, 3 },{ "LDX", &a::LDX, &a::ZPO, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "TAY", &a::TAY, &a::IMP, 2 },{ "LDA", &a::LDA, &a::IMM, 2 },{ "TAX", &a::TAX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "LDY", &a::LDY, &a::ABS, 4 },{ "LDA", &a::LDA, &a::ABS, 4 },{ "LDX", &a::LDX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
       { "BCS", &a::BCS, &a::REL, 2 },{ "LDA", &a::LDA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "LDY", &a::LDY, &a::ZPX, 4 },{ "LDA", &a::LDA, &a::ZPX, 4 },{ "LDX", &a::LDX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "CLV", &a::CLV, &a::IMP, 2 },{ "LDA", &a::LDA, &a::ABY, 4 },{ "TSX", &a::TSX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 4 },{ "LDY", &a::LDY, &a::ABX, 4 },{ "LDA", &a::LDA, &a::ABX, 4 },{ "LDX", &a::LDX, &a::ABY, 4 },{ "???", &a::XXX, &a::IMP, 4 },
       { "CPY", &a::CPY, &a::IMM, 2 },{ "CMP", &a::CMP, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPY", &a::CPY, &a::ZPO, 3 },{ "CMP", &a::CMP, &a::ZPO, 3 },{ "DEC", &a::DEC, &a::ZPO, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INY", &a::INY, &a::IMP, 2 },{ "CMP", &a::CMP, &a::IMM, 2 },{ "DEX", &a::DEX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "CPY", &a::CPY, &a::ABS, 4 },{ "CMP", &a::CMP, &a::ABS, 4 },{ "DEC", &a::DEC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
       { "BNE", &a::BNE, &a::REL, 2 },{ "CMP", &a::CMP, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ZPX, 4 },{ "DEC", &a::DEC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLD", &a::CLD, &a::IMP, 2 },{ "CMP", &a::CMP, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ABX, 4 },{ "DEC", &a::DEC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
       { "CPX", &a::CPX, &a::IMM, 2 },{ "SBC", &a::SBC, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPX", &a::CPX, &a::ZPO, 3 },{ "SBC", &a::SBC, &a::ZPO, 3 },{ "INC", &a::INC, &a::ZPO, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INX", &a::INX, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::SBC, &a::IMP, 2 },{ "CPX", &a::CPX, &a::ABS, 4 },{ "SBC", &a::SBC, &a::ABS, 4 },{ "INC", &a::INC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
       { "BEQ", &a::BEQ, &a::REL, 2 },{ "SBC", &a::SBC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ZPX, 4 },{ "INC", &a::INC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SED", &a::SED, &a::IMP, 2 },{ "SBC", &a::SBC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ABX, 4 },{ "INC", &a::INC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
   };
}

arch::~arch() {}

   //------------Bus connectivity------------

uint8_t arch::read(uint16_t a) {
   return bus->read(a, false);
}

void arch::write(uint16_t a, uint8_t d) {
   bus->write(a, d);
}

void arch::clock() {
   if(cycles == 0) {
       opcode = read(pc);

#ifdef LOGMODE
       uint16_t log_pc = pc;
#endif

       setFlag(U, true);
       pc++;

       cycles = lookup[opcode].cycles;
       uint8_t additionalcycle1 = (this->*lookup[opcode].addrmode)();
       uint8_t additionalcycle2 = (this->*lookup[opcode].operate)();

       cycles += (additionalcycle1 & additionalcycle2);

#ifdef LOGMODE
       if(logfile == nullptr) fopen("arch6502.txt", "wt");
       if(logfile != nullptr) {
           fprintf(logfile, "%10d:%02d PC:%04X %s A:%02X X:%02X Y:%02X %s%s%s%s%s%s%s%s STKP:%02X\n",
                   clock_count, 0, log_pc, "XXX", a, x, y,
                   getFlag(N) ? "N" : ".",    getFlag(V) ? "V" : ".",    getFlag(U) ? "U" : ".",
                   getFlag(B) ? "B" : ".",    getFlag(D) ? "D" : ".",    getFlag(I) ? "I" : ".",
                   getFlag(Z) ? "Z" : ".",    getFlag(C) ? "C" : ".",    stkp);
       }
#endif
       //increment clock count --debugger
       clock_count++;

       cycles--;
   }
}

//flag functions
uint8_t arch::getFlag(FLAGS6502 flag) {
   return (status & flag) > 0 ? 1 : 0;
}

void arch::setFlag(FLAGS6502 flag, bool v) {
   if(v){
       status |= flag;
   }
   else {
       status &= ~flag;
   }
}

//-----------Addressing modes---------------------

uint8_t arch::IMP() {
   fetched = a;
   return 0;
}

uint8_t arch::IMM() {
   addr_abs = pc++;
   return 0;
}

uint8_t arch::ZPO() {
   addr_abs = read(pc);
   pc++;
   addr_abs &= 0x00FF;
   return 0;
}

uint8_t arch::ZPX() {
   addr_abs = (read(pc) + x);
   pc++;
   addr_abs &= 0x00FF;
   return 0;
}

uint8_t arch::ZPY() {
   addr_abs = (read(pc) + y);
   pc++;
   addr_abs &= 0x00FF;
   return 0;
}

uint8_t arch::ABS() {
   uint16_t hi = read(pc);
   pc++;
   uint16_t lo = read(pc);
   pc++;

   addr_abs = (hi << 8) | lo;
   return 0;
}

uint8_t arch::ABX() {
   uint16_t hi = read(pc);
   pc++;
   uint16_t lo = read(pc);
   pc++;

   addr_abs = (hi << 8) | lo;
   addr_abs += x;

   if((addr_abs & 0xFF00) != (hi << 8)) {
       return 1;
   }
   return 0;
}

uint8_t arch::ABY() {
   uint16_t hi = read(pc);
   pc++;
   uint16_t lo = read(pc);
   pc++;

   addr_abs = (hi << 8) | lo;
   addr_abs += y;

   if((addr_abs & 0xFF00) != (hi << 8)) {
       return 1;
   }
   return 0;
}

uint8_t arch::IND() {
   uint16_t ptr_lo = read(pc);
   pc++;
   uint16_t ptr_hi = read(pc);
   pc++;

   uint16_t ptr = (ptr_hi << 8) | ptr_lo;

   //emulate an original NES bug to remain on the same page at 0x00FF
   if(ptr == 0x00FF) {
       addr_abs = (read(ptr & 0xFF00) << 8) | read(ptr);
   }
   else {
       addr_abs = (read(ptr + 1) << 8) | read(ptr + 0);
   }

   return 0;
}

uint8_t arch::IZX() {
   //ptr can be retrieved on a single address, since it's a 0 page case
   uint16_t ptr = read(pc);
   pc++;

   uint16_t lo = ((uint16_t)(ptr + (uint16_t)x) & 0x00FF);
   uint16_t hi = ((uint16_t)(ptr + (uint16_t)x + 1) & 0x00FF);

   addr_abs = (hi << 8) | lo;
   return 0;
}

uint8_t arch::IZY() {
   uint16_t ptr = read(pc);
   pc++;

   uint16_t lo = (ptr & 0x00FF);
   uint16_t hi = (ptr & 0x00FF);

   addr_abs = (hi << 8) | lo;
   addr_abs += y;

   if((addr_abs & 0xFF00) != (hi << 8)) {
       return 1;
   }
   return 0;
}

uint8_t arch::REL() {
   addr_rel = read(pc);
   pc++;

   if(addr_rel & 0x80) {
       addr_rel |= 0xFF00;
   }

   return 0;
}

//---------------- INSTUCTIONS-------------------


uint8_t arch::fetch() {
   if(!(lookup[opcode].addrmode == &arch::IMP)) {
       fetched = (uint8_t)addr_abs;
   }
   return fetched;
}

// Logical AND on accumulator.
uint8_t arch::AND() {
   fetch();
   a &= fetched;

   setFlag(Z, a == 0x00);
   setFlag(N, a & 0x80);
   return 1;
}

//.....Branch instructions

//carry set
uint8_t arch::BCS() {
   if(getFlag(C) == 1) {
       addr_abs = pc + addr_rel;
       cycles++;

       if((addr_abs & 0xFF00) != (pc & 0xFF00))
           cycles++;

       pc = addr_abs;
   }
   return 0;
}

//carry clear
uint8_t arch::BCC() {
   if(getFlag(C) == 0) {
       addr_abs = pc + addr_rel;
       cycles++;

       if((addr_abs & 0xFF00) != (pc & 0xFF00))
           cycles++;

       pc = addr_abs;
   }
   return 0;
}

//if equal
uint8_t arch::BEQ() {
   if(getFlag(Z) == 1) {
       addr_abs = pc + addr_rel;
       cycles++;

       if((addr_abs & 0xFF00) != (pc & 0xFF00))
           cycles++;

       pc = addr_abs;
   }
   return 0;
}

//if minus exists
uint8_t arch::BMI() {
   if(getFlag(N) == 1) {
       addr_abs = pc + addr_rel;
       cycles++;

       if((addr_abs & 0xFF00) != (pc & 0xFF00))
           cycles++;

       pc = addr_abs;
   }
   return 0;
}

//not equal
uint8_t arch::BNE() {
   if(getFlag(Z) == 0) {
       addr_abs = pc + addr_rel;
       cycles++;

       if((addr_abs & 0xFF00) != (pc & 0xFF00))
           cycles++;

       pc = addr_abs;
   }
   return 0;
}

//if positive
uint8_t arch::BPL() {
   if(getFlag(N) == 0) {
       addr_abs = pc + addr_rel;
       cycles++;

       if((addr_abs & 0xFF00) != (pc & 0xFF00))
           cycles++;

       pc = addr_abs;
   }
   return 0;
}

// no overflow
uint8_t arch::BVC() {
   if(getFlag(V) == 0) {
       addr_abs = pc + addr_rel;
       cycles++;

       if((addr_abs & 0xFF00) != (pc & 0xFF00)) {
           cycles++;
       }
       pc = addr_abs;
   }
   return 0;
}

//overflow
uint8_t arch::BVS() {
   if(getFlag(V) == 1) {
       addr_abs = pc + addr_rel;
       cycles++;

       if((addr_abs & 0xFF00) != (pc & 0xFF00))
           cycles++;

       pc = addr_abs;
   }
   return 0;
}

//......clear instructions

//carry bit
uint8_t arch::CLC() {
   setFlag(C, false);
   return 0;
}

//decimal mode
uint8_t arch::CLD() {
   setFlag(D, false);
   return 0;
}

//clear interrupt.
uint8_t arch::CLI() {
   setFlag(I, false);
   return 0;
}

//clear overflow
uint8_t arch::CLV() {
   setFlag(V, false);
   return 0;
}

//..........

//ADD to accumulator
uint8_t arch::ADC() {
   fetch();

   temp = (uint16_t)a + (uint16_t)fetched + (uint16_t)getFlag(C);
   setFlag(C, temp > 255);
   setFlag(Z, (temp & 0x00FF) == 0);
   setFlag(N, (temp & 0x80) == 1);
   setFlag(V, (~((uint16_t)a ^ (uint16_t)fetched))&((uint16_t)a ^ (uint16_t)temp) & 0x0080);
   a = temp & 0x00FF;
   return 1;
}

//SUB from accumulator
uint8_t arch::SBC() {
   fetch();

   uint16_t flipped = (uint16_t)fetched ^ 0x00FF;
   temp = (uint16_t)a + (uint16_t)flipped + (uint16_t)getFlag(C);

   setFlag(C, temp > 255);
   setFlag(Z, (temp & 0x00FF) == 0);
   setFlag(N, temp & 0x80);
   setFlag(V, ((((uint16_t)temp)^ (uint16_t)a)&(temp ^ flipped))& 0x0080);
   a = temp & 0x0080;
   return 1;
}

//.....stack operations........

uint8_t arch::PHA() {
   write(0x0100 + stkp, a);
   stkp--;
   return  0;
}

uint8_t arch::PLA() {
   stkp++;
   a = read(0x0100 + stkp);
   setFlag(Z, a == 0x00);
   setFlag(N, a & 0x80);
   return 0;
}

uint8_t arch::RTI() {
   stkp++;
   status = read(0x0100 + stkp);
   status |= ~B;
   status |= ~U;

   stkp++;
   pc = (uint16_t)read(0x0100 + stkp);
   stkp++;
   pc |= (uint16_t)(read(0x0100 + stkp)) << 8;
   return 0;
}

//external inputs.

void arch::reset() {
   addr_abs = 0xFFFC;
   uint16_t hi = read(addr_abs);
   uint16_t lo = read(addr_abs + 1);

   //set pc to hi|lo
   pc = (hi << 8) | lo;

   //clear registers
   a = 0x00;
   x = 0x00;
   y = 0x00;
   stkp = 0xFD;
   status = 0x00 | U; // set ununsed flag to status reset.

   //clear internal vars.
   addr_abs = 0x0000;
   addr_rel = 0x0000;
   fetched = 0x00;

   cycles = 8;
}

void arch::irq() {
   if(getFlag(I) == 0) {
       write(0x0100 + stkp, (pc >> 8) & 0x00FF);
       stkp--;
       write(0x0100 + stkp, pc & 0x00FF);
       stkp--;

       setFlag(B, 0);
       setFlag(U, 1);
       setFlag(I, 1);
       write(0x0100 + stkp, status);
       stkp--;

       //set pc to coded location.
       addr_abs = 0xFFFE;
       uint16_t lo = read(addr_abs);
       uint16_t hi = read(addr_abs + 1);
       pc = (hi << 8) | lo;

       cycles = 7;
   }
}

void arch::nmi() {
   write(0x0100 + stkp, (pc >> 8) & 0x00FF);
   stkp--;
   write(0x0100 + stkp, pc & 0x00FF);
   stkp--;

   setFlag(B, 0);
   setFlag(U, 1);
   setFlag(I, 1);
   write(0x0100 + stkp, status);
   stkp--;

   //set pc to coded location.
   addr_abs = 0xFFFA;
   uint16_t lo = read(addr_abs);
   uint16_t hi = read(addr_abs + 1);
   pc = (hi << 8) | lo;

   cycles = 8;
}

//Arithmetic shift left
uint8_t arch::ASL() {
   fetch();

   temp = (uint16_t)fetched << 1;
   setFlag(C, (temp & 0xFF00) > 0);
   setFlag(Z, (temp & 0x00FF) == 0);
   setFlag(N, temp & 0x80);

   if(lookup[opcode].addrmode == &arch::IMP){
       a = temp & 0x00FF;
   }
   else addr_abs = temp & 0x00FF;
   return 0;
}

// Bit test
uint8_t arch::BIT() {
   fetch();

   temp = a & fetched;
   setFlag(Z, (temp & 0x00FF) == 0);
   setFlag(N, fetched & (1 << 7));
   setFlag(V, fetched & (1 << 6));
   return 0;
}

// break -- start a system interrupt instruction
uint8_t arch::BRK() {
   pc++;

   setFlag(I, true);
   write(0x0100 + stkp, (pc >> 8) & 0x00FF);
   stkp--;
   write(0x0100 + stkp, pc & 0x00FF);
   stkp--;

   setFlag(B, true);
   write(0x0100 , status);
   stkp--;
   setFlag(B, false);

   uint16_t ptr = 0xFFFE;
   pc = ((read(ptr) & 0x00FF) << 8) | (read(ptr + 1) & 0x00FF);
   return 0;
}

//compare acculmulator with a memory loc
uint8_t arch::CMP() {
   fetch();

   temp = (uint16_t)read(a) - (uint16_t)read(fetched);
   setFlag(C, a >= fetched);
   setFlag(Z, (temp & 0x00FF) == 0);
   setFlag(N, temp & 0x80);
   return 1;
}

//compare with x reg
uint8_t arch::CPX() {
   fetch();

   temp = (uint16_t)x - (uint16_t)fetched;
   setFlag(C, x >= fetched);
   setFlag(Z, (temp & 0x00FF) == 0);
   setFlag(N, temp & 0x80);
   return 1;
}

//compare with y reg
uint8_t arch::CPY() {
   fetch();

   temp = (uint16_t)y - (uint16_t)fetched;
   setFlag(C, y >= fetched);
   setFlag(Z, (temp & 0x00FF) == 0);
   setFlag(N, temp & 0x80);
   return 1;
}

//decrement mem loc.
uint8_t arch::DEC() {
   fetch();

   temp = fetched - 1;
   write(addr_abs, temp & 0x00FF);
   setFlag(Z, (temp & 0x00FF) == 0);
   setFlag(N, temp & 0x80);
   return  0;
}

// decrement x reg
uint8_t arch::DEX() {
   x--;
   setFlag(Z, x == 0);
   setFlag(N, x & 0x80);
   return 0;
}

//decrement y reg
uint8_t arch::DEY() {
   y--;
   setFlag(Z, y == 0);
   setFlag(N, y & 0x80);
   return  0;
}

//increment mem loc.
uint8_t arch::INC() {
   fetch();

   temp = fetched + 1;
   write(addr_abs, temp & 0x00FF);
   setFlag(Z, (temp & 0x00FF) == 0);
   setFlag(N, temp & 0x80);
   return  0;
}

// decrement x reg
uint8_t arch::INX() {
   x++;
   setFlag(Z, x == 0);
   setFlag(N, x & 0x80);
   return 0;
}

//decrement y reg
uint8_t arch::INY() {
   y++;
   setFlag(Z, y == 0);
   setFlag(N, y & 0x80);
   return  0;
}

//jump to location -- set pc to a specific address
uint8_t arch::JMP() {
   pc = addr_abs;
   return 0;
}

// bitwise XOR on accumulator and mem loc.
uint8_t arch::EOR() {
   fetch();

   a ^= fetched;
   setFlag(Z, a == 0);
   setFlag(N, a & 0x80);
   return 1;
}

//Bitwise OR
uint8_t arch::ORA() {
   fetch();

   a |= fetched;
   setFlag(Z, a == 0);
   setFlag(N, a & 0x80);
   return 1;
}

//jump to subroutine -- push pc into stack
uint8_t arch::JSR() {
   pc--;

   write(0x0100 + stkp, (pc >> 8) & 0x00FF);
   stkp--;
   write(0x0100 + stkp, pc & 0x00FF);
   stkp--;

   pc = addr_abs;
   return  0;
}

//load accumulator
uint8_t arch::LDA() {
   fetch();

   a = fetched;
   setFlag(Z, a == 0);
   setFlag(N, a & 0x80);
   return 1;
}

//load x reg
uint8_t arch::LDX() {
   fetch();

   x = fetched;
   setFlag(Z, x == 0);
   setFlag(N, x & 0x80);
   return 1;
}

//load y reg
uint8_t arch::LDY() {
   fetch();

   y = fetched;
   setFlag(Z, y == 0);
   setFlag(N, y & 0x80);
   return 1;
}

//left shift reg
uint8_t arch::LSR() {
   fetch();

   setFlag(C, fetched & 0x0001);
   temp = fetched >> 1;

   if(lookup[opcode].addrmode == &arch::IMP) {
       a = temp & 0x00FF;
   }
   else write(addr_abs, temp & 0x00FF);

   setFlag(Z, (temp & 0x00FF) == 0);
   setFlag(N, temp & 0x80);

   return 0;
}

//no operation
uint8_t arch::NOP() {

   switch (opcode) {
       case 0x1C:
       case 0x3C:
       case 0x5C:
       case 0x7C:
       case 0xDC:
       case 0xFC:
           return 1;
           break;
   }
   return 0;
}

//push status onto stack
uint8_t arch::PHP() {

   write(0x0100 + stkp, status | B | U);
   setFlag(B, 0);
   setFlag(U, 0);

   stkp++;
   return 0;
}

//pop status from stack.
uint8_t arch::PLP() {
   stkp++;

   status = read(0x0100 + stkp);
   setFlag(U, 1);
   return 0;
}

//Rotate left
uint8_t arch::ROL() {
   fetch();

   temp = (uint16_t)fetched << 1 | getFlag(C);
   setFlag(C, temp & 0xFF00);
   setFlag(Z, (temp & 0x00FF) == 0);
   setFlag(N, temp & 0x80);

   if(lookup[opcode].addrmode == &arch::IMP) {
       a = temp & 0x00FF;
   }
   else write(addr_abs, temp & 0x00FF);
   return 0;
}

//rotate right
uint8_t arch::ROR() {
   fetch();

   temp = (uint16_t)(getFlag(C) << 7) |(fetched >> 1);
   setFlag(C, fetched & 0x001);
   setFlag(Z, (temp & 0x00FF) == 0);
   setFlag(N, temp & 0x80);

   if (lookup[opcode].addrmode == &arch::IMP) {
       a = temp & 0x00FF;
   }
   else write(addr_abs, temp & 0x00FF);
   return 0;
}

//return from subroutine
uint8_t arch::RTS() {
   stkp++;

   pc = (uint16_t)read(0x0100 + stkp);
   stkp++;
   pc |= (uint16_t)(read(0x0100 + stkp) << 8);
   stkp++;

   pc++;
   return 0;
}

//............Set flags.................

//carry
uint8_t arch::SEC() {
   setFlag(C, true);
   return 0;
}

//decimal
uint8_t arch::SED() {
   setFlag(D, true);
   return 0;
}

//Interrupt
uint8_t arch::SEI() {
   setFlag(I, true);
   return 0;
}

//..........Transfer registers............

//store accumulator at address
uint8_t arch::STA() {
   write(addr_abs, a);
   return 0;
}

//store x at addr
uint8_t arch::STX() {
   write(addr_abs, x);
   return 0;
}

//store y at addr
uint8_t arch::STY() {
   write(addr_abs, y);
   return 0;
}

//transfer accumulator onto x
uint8_t arch::TAX() {
   x = a;
   setFlag(Z, x == 0);
   setFlag(N, x & 0x80);
   return 0;
}

//transfer accumulator onto y
uint8_t arch::TAY() {
   y = a;
   setFlag(Z, x == 0);
   setFlag(N, x & 0x80);
   return 0;
}

//transfer stack onto x.
uint8_t arch::TSX() {
   x = stkp;
   setFlag(Z, x == 0);
   setFlag(N, x & 0x80);
   return 0;
}

//transfer x onto stack
uint8_t arch::TXS() {
   stkp = x;
   return 0;
}

//tranfer x onto accumulator.
uint8_t arch::TXA() {
   a = x;
   setFlag(Z, a == 0);
   setFlag(N, a & 0x80);
   return 0;
}

//tranfer y onto accumulator.
uint8_t arch::TYA() {
   a = y;
   setFlag(Z, a == 0);
   setFlag(N, a & 0x80);
   return 0;
}

//illegal.
uint8_t arch::XXX() {
   return 0;
}

//---------helper func-----------------

bool arch::complete() {
   return cycles == 0;
}

//disassembler.

std::map<uint16_t, std::string> arch::disassemble(uint16_t nStart, uint16_t nStop) {
   uint32_t addr = nStart;
   uint8_t val = 0x00, lo = 0x00, hi = 0x00;
   std::map<uint16_t, std::string> maplines;
   uint16_t lineAddr = 0;

   //hex to string converter
   auto hex = [](uint32_t n, uint8_t d) {
      std::string s(d, '0');
      for(int i = d -1; i >= 0; i--, n>>=4) {
         s[i] = "0123456789ABCDEF"[n & 0xF];
      }
      return s;
   };

   while(addr <= (uint32_t)nStop) {
      lineAddr = addr;

      std::string sInstruct = "$" + hex(addr, 4) + ": ";
      //get opcode and instruction title
      uint8_t opcode = bus->read(addr, true); 
      addr++;
      sInstruct += lookup[opcode].name + " ";

      if(lookup[opcode].addrmode == &arch::IMP) {
         sInstruct += "{IMP}";
      }

      else if(lookup[opcode].addrmode == &arch::IMM) {
         val = bus->read(addr, true);
         addr++;
         sInstruct += "#$" + hex(val, 2) + "{IMM}";
      }

      else if(lookup[opcode].addrmode == &arch::ZPO) {
         lo = bus->read(addr, true);
         addr++;
         hi = 0x00;
         sInstruct += "$" + hex(lo, 2) + "{ZPO}";
      }

      else if(lookup[opcode].addrmode == &arch::ZPX) {
         lo = bus->read(addr, true);
         addr++;
         hi = 0x00;
         sInstruct += "$" + hex(lo, 2) + ", X {ZPX}";
      }

      else if(lookup[opcode].addrmode == &arch::ZPY) {
         lo = bus->read(addr, true);
         addr++;
         hi = 0x00;
         sInstruct += "$" + hex(lo, 2) + ", Y {ZPY}";
      }

      else if(lookup[opcode].addrmode == &arch::ABS) {
         lo = bus->read(addr, true);
         addr++;
         hi = bus->read(addr, true);
         addr++;

         sInstruct += "$" + hex(((uint16_t)hi << 8) | lo, 4) + "{ABS}";
      }

      else if(lookup[opcode].addrmode == &arch::ABX) {
         lo = bus->read(addr, true);
         addr++;
         hi = bus->read(addr, true);
         addr++;

         sInstruct += "$" + hex(((uint16_t)hi << 8) | lo, 4) + ", X {ABX}";
      }

      else if(lookup[opcode].addrmode == &arch::ABY) {
         lo = bus->read(addr, true);
         addr++;
         hi = bus->read(addr, true);
         addr++;

         sInstruct += "$" + hex(((uint16_t)hi << 8) | lo, 4) + ", Y {ABY}";
      }

      else if(lookup[opcode].addrmode == &arch::IND) {
         lo = bus->read(addr, true);
         addr++;
         hi = bus->read(addr, true);
         addr++;

         sInstruct += "($" + hex(((uint16_t)hi << 8) | lo, 4) + "), {IND}";
      }

      else if(lookup[opcode].addrmode == &arch::IZX) {
         lo = bus->read(addr, true);
         addr++;
         hi = 0x00;

         sInstruct += "($" + hex(lo , 2) + ", X) {ZPX}";
      }

      else if(lookup[opcode].addrmode == &arch::IZY) {
         lo = bus->read(addr, true);
         addr++;
         hi = 0x00;

         sInstruct += "($" + hex(lo, 2) + ", Y) {ZPY}";
      }

      else if(lookup[opcode].addrmode == &arch6502::REL) {
         val = bus->read(addr, true);
         addr++;

         sInstruct += "$" + hex(val, 2) + " " + "[$" + hex(addr + val, 4) + "] {REL}"; 
      }
      maplines[lineAddr] = sInstruct;
   }
   return maplines;
}