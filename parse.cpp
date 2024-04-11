
#include "parse.h"

#include <sstream>

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

  std::istringstream ss(line.substr(10));
  std::string mnemonic;

  ss >> mnemonic;

  return mnemonic;
}

std::string operand_of(const std::string& line) {

  if (line.size() < 19 || is_whitespace(line.substr(18)))
    return "";

  std::istringstream ss(line.substr(18));
  std::string operand;

  ss >> operand;

  return operand;
}
