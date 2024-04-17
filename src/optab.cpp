
#include "optab.h"

std::unordered_map<std::string, OpInfo> optab; // global optab object

void OpTab::init() {
  optab["ADDR"]   = { FORMAT_2,   0x90 };
  optab["ADD"]    = { FORMAT_3_4, 0x18 };
  optab["ADDF"]   = { FORMAT_3_4, 0x58 };
  optab["AND"]    = { FORMAT_3_4, 0x40 };
  optab["COMPR"]  = { FORMAT_2,   0xA0 };
  optab["CLEAR"]  = { FORMAT_2,   0xB4 };
  optab["COMP"]   = { FORMAT_3_4, 0x28 };
  optab["COMPF"]  = { FORMAT_3_4, 0x88 };
  optab["DIVR"]   = { FORMAT_2,   0x9C };
  optab["DIV"]    = { FORMAT_3_4, 0x24 };
  optab["DIVF"]   = { FORMAT_3_4, 0x64 };
  optab["FLOAT"]  = { FORMAT_1,   0xC0 };
  optab["FIX"]    = { FORMAT_1,   0xC4 };
  optab["HIO"]    = { FORMAT_1,   0xF4 };
  optab["J"]      = { FORMAT_3_4, 0x3C };
  optab["JEQ"]    = { FORMAT_3_4, 0x30 };
  optab["JGT"]    = { FORMAT_3_4, 0x34 };
  optab["JLT"]    = { FORMAT_3_4, 0x38 };
  optab["JSUB"]   = { FORMAT_3_4, 0x48 };
  optab["LDA"]    = { FORMAT_3_4, 0x00 };
  optab["LDB"]    = { FORMAT_3_4, 0x68 };
  optab["LDCH"]   = { FORMAT_3_4, 0x50 };
  optab["LDF"]    = { FORMAT_3_4, 0x70 };
  optab["LDL"]    = { FORMAT_3_4, 0x08 };
  optab["LDS"]    = { FORMAT_3_4, 0x6C };
  optab["LDT"]    = { FORMAT_3_4, 0x74 };
  optab["LDX"]    = { FORMAT_3_4, 0x04 };
  optab["LPS"]    = { FORMAT_3_4, 0xD0 };
  optab["MULR"]   = { FORMAT_2,   0x98 };
  optab["MUL"]    = { FORMAT_3_4, 0x20 };
  optab["MULF"]   = { FORMAT_3_4, 0x60 };
  optab["NORM"]   = { FORMAT_1,   0xC8 };
  optab["OR"]     = { FORMAT_3_4, 0x44 };
  optab["RD"]     = { FORMAT_3_4, 0xD8 };
  optab["RSUB"]   = { FORMAT_3_4, 0x4C };
  optab["RMO"]    = { FORMAT_2,   0xAC };
  optab["SUB"]    = { FORMAT_3_4, 0x1C };
  optab["SUBF"]   = { FORMAT_3_4, 0x5C };
  optab["SIO"]    = { FORMAT_1,   0xF0 };
  optab["SHIFTL"] = { FORMAT_2,   0xA4 };
  optab["SHIFTR"] = { FORMAT_2,   0xA8 };
  optab["SUBR"]   = { FORMAT_2,   0x94 };
  optab["SVC"]    = { FORMAT_2,   0xB0 };
  optab["SSK"]    = { FORMAT_3_4, 0xEC };
  optab["STA"]    = { FORMAT_3_4, 0x0C };
  optab["STB"]    = { FORMAT_3_4, 0x78 };
  optab["STCH"]   = { FORMAT_3_4, 0x54 };
  optab["STF"]    = { FORMAT_3_4, 0x80 };
  optab["STI"]    = { FORMAT_3_4, 0xD4 };
  optab["STL"]    = { FORMAT_3_4, 0x14 };
  optab["STS"]    = { FORMAT_3_4, 0x7C };
  optab["STSW"]   = { FORMAT_3_4, 0xE8 };
  optab["STT"]    = { FORMAT_3_4, 0x84 };
  optab["STX"]    = { FORMAT_3_4, 0x10 };
  optab["TIXR"]   = { FORMAT_2,   0xB8 };
  optab["TD"]     = { FORMAT_3_4, 0xE0 };
  optab["TIX"]    = { FORMAT_3_4, 0x2C };
  optab["TIO"]    = { FORMAT_1,   0xF8 };
  optab["WD"]     = { FORMAT_3_4, 0xDC };
}
