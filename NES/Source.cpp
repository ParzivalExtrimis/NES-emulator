#include <iostream>
#include "Bus.hpp"
#include "arch6502.hpp"
#include "olcPixelGameEngine.h"

#define OLC_PGE_APPLICATION

class Profiler : public olc::PixelGameEngine {

public:
   Profiler() { sAppName = "Nes-profiler"; }

   Bus nes;
   std::map<uint16_t, std::string> mapAsm;

   //drawing functions.
   std::string hex(uint32_t, short);
   void drawRam(int, int, uint16_t, int, int);
   void drawCpu(int, int);
   void drawCode(int, int, int);

   //overrides.
   bool OnUserUpdate(float fElapsedtime) {
      Clear(olc::BLACK);

      //step instruction.
      if(GetKey(olc::Key::SPACE).bPressed) {
         do {
            nes.cpu.clock();
         } while(!nes.cpu.complete());
      }

      //reset
      if(GetKey(olc::Key::R).bPressed) {
         nes.cpu.reset();
      }

      //interrupt key.
      if(GetKey(olc::Key::I).bPressed) {
         nes.cpu.irq();
      }

      //non-maskable
      if(GetKey(olc::Key::N).bPressed) {
         nes.cpu.nmi();
      }

      drawRam(2, 2, 0x0000, 16, 16);
      drawRam(2, 182, 0x8000, 16, 16);
      drawCpu(448, 2);
      drawCode(448, 72, 26);

      DrawString(10, 370, "SPACE = Step Instruction    R = Reset    I = IRQ    N = NMI");
   
      return true;
   }

   bool OnUserCreate() {
      std::stringstream ss;
      ss << "A2 0A 8E 00 00 A2 03 8E 01 00 AC 00 00 A9 00 18 6D 01 00 88 D0 FA 8D 02 00 EA EA EA";

      uint16_t nOffset = 0x8000;
      while(!ss.eof()) {
         std::string byte;
         ss >> byte;

         nes.ram[nOffset++] = std::stoul(byte, nullptr, 16);
      }

      //set vectors
      nes.ram[0xFFFC] = 0x00;
      nes.ram[0xFFFD] = 0x80;

      nes.cpu.disassemble(0x0000, 0xFFFF);

      //reset
      nes.cpu.reset();
      return true;
   }
};

std::string Profiler::hex(uint32_t addr, short d) {
      std::string val(d, '0');
      for(int i = d-1; i >= 0; i++, addr >> 4) {
         val[i] = "0123456789ABCDEF"[addr & 0xF];
      }
      return val;
   }

void Profiler::drawRam(int x, int y, uint16_t nAddr, int nRows, int nCols) {
      int nRamX = x, nRamY = y;
      for(int i = 0; i < nRows; i++) {
         std::string sOffset = "$" + hex(nAddr, 4) + ":";

         for(int j = 0; j < nCols; j++) {
            sOffset += " " + hex((nes.read(nAddr, true)), 2);
            nAddr++;
         }
         DrawString(nRamX, nRamY, sOffset);
         nRamY += 10;
      } 
   }

   void Profiler::drawCpu(int x, int y) {
      DrawString(x, y, "Status: ");
      DrawString(x + 64, y, "N", nes.cpu.status & arch6502::N ? olc::GREEN : olc::RED);
      DrawString(x + 80, y, "V", nes.cpu.status & arch6502::V ? olc::GREEN : olc::RED);
      DrawString(x + 96, y, "-", nes.cpu.status & arch6502::U ? olc::GREEN : olc::RED);
      DrawString(x + 112, y, "B", nes.cpu.status & arch6502::B ? olc::GREEN : olc::RED);
      DrawString(x + 128, y, "D", nes.cpu.status & arch6502::D ? olc::GREEN : olc::RED);
      DrawString(x + 144, y, "I", nes.cpu.status & arch6502::I ? olc::GREEN : olc::RED);
      DrawString(x + 160, y, "Z", nes.cpu.status & arch6502::Z ? olc::GREEN : olc::RED);
      DrawString(x + 172, y, "C", nes.cpu.status & arch6502::C ? olc::GREEN : olc::RED);

      DrawString(x, y + 10, "PC: $" + hex(nes.cpu.pc, 4));
      DrawString(x, y + 20, "A: $" + hex(nes.cpu.a, 2) + " [" + std::to_string(nes.cpu.a) + "]");
      DrawString(x, y + 30, "X: $" + hex(nes.cpu.x, 2) + " [" + std::to_string(nes.cpu.x) + "]");
      DrawString(x, y + 40, "Y: $" + hex(nes.cpu.y, 2) + " [" + std::to_string(nes.cpu.y) + "]");
      DrawString(x, y + 50, "Stack P: $" + hex(nes.cpu.stkp, 4));
   }

   void Profiler::drawCode(int x, int y, int nLines) {
      auto it = mapAsm.find(nes.cpu.pc);
      int nLinesY = (nLines >> 1) * 10 + y;

      if(it != mapAsm.end()) {
         DrawString(x, nLinesY, it->second, olc::CYAN);
         while(nLinesY < (nLines * 10) + y) {
            nLinesY += 10;
            if(it++ != mapAsm.end()) {
               DrawString(x, nLinesY, it->second);
            }
         }
      }

      it = mapAsm.find(nes.cpu.pc);
      nLinesY = (nLines >> 1) * 10 + y;
      
      it--; nLinesY -= 10;
      while(it != mapAsm.end() && nLines > y) {
         DrawString(x, nLinesY, it->second);
         it--; nLinesY -= 10;
      }
   }