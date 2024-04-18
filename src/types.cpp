

#include "types.h"

#include "format.h"
#include "parse.h"

#include <algorithm>
#include <iomanip>
#include <sstream>

void LiteralTable::set_visited(const std::string& name) {
  for (Literal& l : literals)
    if (l.name == name)
      l.visited = true;
}

void SymbolTable::handle(const std::string& line, int locctr) {
  if (line.find("EQU") == std::string::npos)
    table[symbol_of(line)] = { locctr, RELATIVE };
  else
    table[symbol_of(line)] = { evaluate_expr(operand_of(line), *this, locctr), evaluate_flag(operand_of(line), *this) };
}

bool SymbolTable::contains(const std::string& key) const {
  return table.find(key) != table.end();
}

std::string LiteralTable::to_string() {

  std::stringstream ss;
  ss << std::left << std::uppercase << std::hex << "Name  Operand   Address  Length:\n--------------------------------\n";

  for (Literal l : literals)
    ss << std::hex << std::setw(6) << l.name << std::setw(10) << l.value << std::setw(9) << l.address << l.length << "\n";

  return ss.str();
}

bool LiteralTable::contains(const std::string& name) {
  for (Literal l : literals)
    if (l.name == name)
      return true;
  return false;
}

std::string SymbolTable::to_string() {

  std::stringstream ss;

  ss << std::left << "CSect   Symbol  Value   LENGTH  Flags:\n--------------------------------------\n"
    << std::setw(16) << csect.name << to_hex_string(csect.address, 6) << "  " << to_hex_string(csect.length, 6) << "\n";

  std::vector<std::pair<std::string, SymbolInfo>> stab_sorted(table.begin(), table.end());

  std::sort(stab_sorted.begin(), stab_sorted.end(),
    [](const std::pair<std::string, SymbolInfo>& a, const std::pair<std::string, SymbolInfo>& b) { return a.second.value < b.second.value; });

  for (auto& pair : stab_sorted)
    ss << "        " << std::setw(8) << pair.first << std::setw(16) << to_hex_string(pair.second.value, 6) << "RA"[pair.second.flag] << "\n";

  return ss.str();
}

void LiteralTable::pool(int& locctr) {
  for (Literal& l : literals) {
    if (l.address == NO_ADDR) {
      l.address = locctr;
      locctr += l.length;
    }
  }
}
