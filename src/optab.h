

#ifndef OPTAB_H
#define OPTAB_H

#include <string>
#include <unordered_map>

enum InstructionFormat {
  FORMAT_1 = 1, FORMAT_2, FORMAT_3_4
};

struct OpInfo {
  InstructionFormat format;
  int opcode;
};

extern std::unordered_map<std::string, OpInfo> optab;

namespace OpTab {
  void init();
}

#endif
