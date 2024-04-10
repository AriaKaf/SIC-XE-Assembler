
#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <unordered_map>

enum Flag { RELATIVE, ABSOLUTE, NO_FLAG };

struct SymbolInfo {
  int value;
  int length;
  Flag flag;
};

struct LiteralInfo {
  int operand;
  int address;
  int length;
};

typedef std::unordered_map<std::string, SymbolInfo> SymbolTable;
typedef std::unordered_map<std::string, LiteralInfo> LiteralTable;

std::string to_string(const SymbolTable& stab);
std::string to_string(const LiteralTable& ltab);

#endif
