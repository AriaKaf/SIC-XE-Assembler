
#include "types.h"

#include <iomanip>
#include <sstream>
#include <vector>

std::string to_hex_string(int num, int width) {
  std::stringstream ss;
  ss << std::right << std::setw(width) << std::hex << std::uppercase << std::setfill('0') << num;
  return ss.str();
}

std::string to_string(const SymbolTable& stab) {

  std::stringstream ss;

  ss << std::hex << std::uppercase << "CSect   Symbol  Value   LENGTH  Flags:\n--------------------------------------\n";

  for (int i = 0; i < stab.size(); i++)
  {
    if (!stab[i].csect.empty()) // the 'csect' entry requires special formatting
      ss << std::left << std::setw(16) << stab[i].csect << to_hex_string(stab[i].value, 6) << "  " << to_hex_string(stab[i].length, 6) << "\n";
    else
      ss << "        " << std::left << std::setw(8) << stab[i].symbol << std::setw(16) << to_hex_string(stab[i].value, 6) << "RA"[stab[i].flag] << "\n";
  }

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
