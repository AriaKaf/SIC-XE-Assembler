
#include "parse.h"

bool is_whitespace(const std::string& str) {
  for (int i = 0; i < str.size(); i++)
    if (!std::isspace(str[i]))
      return false;
  return true;
}

std::string symbol_of(const std::string& line) {
  return std::isspace(line[0]) ? "" : line.substr(0, line.find_first_of(" \t\r"));
}

std::string mnemonic_of(const std::string& line) {
  return line.substr(10, line.substr(10).find_first_of(" \t\r"));
}

std::string operand_of(const std::string& line) {

  if (line.size() < 19 || is_whitespace(line.substr(18)))
    return "";

  return line.substr(18, line.substr(18).find_first_of(" \t\r"));
}
