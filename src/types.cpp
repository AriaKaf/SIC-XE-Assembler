
#include "types.h"

#include <algorithm>
#include <iomanip>
#include <sstream>

std::string to_hex_string(int num, int width) {
  std::stringstream ss;
  ss << std::right << std::setw(width) << std::hex << std::uppercase << std::setfill('0') << num;
  return ss.str();
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

std::string to_string(const LiteralTable& ltab) {

  return "";

  //std::vector<std::pair<std::string, LiteralInfo>> sorted_map(ltab.begin(), ltab.end());

  //std::sort(sorted_map.begin(), sorted_map.end(), [](auto& a, auto& b) {
  //  return a.second.address < b.second.address;
  //});

  //std::stringstream ss;

  //ss << std::hex << std::uppercase << "Name  Operand   Address  Length:\n--------------------------------\n";

  //for (auto pair : sorted_map)
  //  ss << std::left << std::setw(6) << pair.first << std::setw(10) << pair.second.operand << std::setw(9) << pair.second.address << pair.second.length << "\n";

  //return ss.str();
}
