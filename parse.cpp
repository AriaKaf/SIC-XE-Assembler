
#include "parse.h"

bool is_a_comment(const std::string& line) {
  return line[0] == '.';
}

std::string symbol_of(const std::string& line) {
  return std::isspace(line[0]) ? "" : line.substr(0, line.find_first_of(" \t\r"));
}

std::string mnemonic_of(const std::string& line) {
  return line.size() < 11 ? "" : line.substr(10, line.substr(10).find_first_of(" \t\r"));
}

bool is_whitespace(const std::string str) {
  for (char c : str)
    if (!std::isspace(c))
      return false;
  return true;
}

std::string operand_of(const std::string& line) {
  return line.size() < 19 || is_whitespace(line.substr(18)) ? "" : line.substr(18, line.substr(18).find_first_of(" \t\r"));
}
