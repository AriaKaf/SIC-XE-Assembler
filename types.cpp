
#include "types.h"

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <vector>

std::string to_hex_string(int num, int width) {
  std::stringstream ss;
  ss << std::right << std::setw(width) << std::hex << std::uppercase << std::setfill('0') << num;
  return ss.str();
}

std::string to_string(const SymbolTable& stab) {

  std::vector<std::pair<std::string, SymbolInfo>> sorted_map(stab.begin(), stab.end());

  std::sort(sorted_map.begin(), sorted_map.end(),
    [](auto& a, auto& b) { return a.second.value < b.second.value; });

  for (int i = 0; i < sorted_map.size(); i++)
    if (sorted_map[i].second.flag == NO_FLAG)
      std::swap(sorted_map[i], sorted_map[0]);

  std::stringstream ss;

  ss << std::hex << std::uppercase << "CSect   Symbol  Value   LENGTH  Flags:\n--------------------------------------\n";

  for (auto pair : sorted_map)
  {
    if (pair.second.flag == NO_FLAG)
      ss << std::left << std::setw(16) << pair.first << to_hex_string(pair.second.value, 6) << "  " << to_hex_string(pair.second.length, 6) << "\n";
    else
      ss << "        " << std::left << std::setw(8) << pair.first << std::setw(16) << to_hex_string(pair.second.value, 6) << "RA"[pair.second.flag] << "\n";
  }

  return ss.str();
}

std::string to_string(const LiteralTable& ltab) {

  std::vector<std::pair<std::string, LiteralInfo>> sorted_map(ltab.begin(), ltab.end());

  std::sort(sorted_map.begin(), sorted_map.end(), [](auto& a, auto& b) {
    return a.second.address < b.second.address;
  });

  std::stringstream ss;

  ss << std::hex << std::uppercase << "Name  Operand   Address  Length:\n--------------------------------\n";

  for (auto pair : sorted_map)
    ss << std::left << std::setw(6) << pair.first << std::setw(10) << pair.second.operand << std::setw(9) << pair.second.address << pair.second.length << "\n";

  return ss.str();
}