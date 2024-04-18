
#ifndef OPTAB_H
#define OPTAB_H

#include <string>
#include <unordered_map>

enum NIXBPE {
  FLAG_N = 1 << 5,
  FLAG_I = 1 << 4,
  FLAG_X = 1 << 3,
  FLAG_B = 1 << 2,
  FLAG_P = 1 << 1,
  FLAG_E = 1
};

enum InstructionFormat {
  FORMAT_1 = 1, FORMAT_2, FORMAT_3, FORMAT_4
};

struct OpInfo {
  InstructionFormat format;
  int opcode;
};

extern std::unordered_map<std::string, OpInfo> optab;
extern std::unordered_map<std::string, int> register_table;

namespace OpTab {
  void init();
}

#endif
