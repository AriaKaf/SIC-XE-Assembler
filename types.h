
#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <vector>

enum Flag { RELATIVE, ABSOLUTE, NO_FLAG };

struct StabEntry {
  StabEntry(std::string csect, std::string symbol, int value, int length, Flag flag) :
    csect(csect), symbol(symbol), value(value), length(length), flag(flag) {}
  std::string csect;
  std::string symbol;
  int value;
  int length;
  Flag flag;
};

struct LtabEntry {
  std::string name;
  int operand;
  int address;
  int length;
};

typedef std::vector<StabEntry> SymbolTable;
typedef std::vector<LtabEntry> LiteralTable;

std::string to_string(const SymbolTable& stab);
std::string to_string(const LiteralTable& ltab);

#endif
