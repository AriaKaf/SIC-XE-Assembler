
#include "optab.h"
#include "parse.h"

int ascii_to_int(const std::string& ascii) {

  int value = 0;

  for (char c : ascii) {
    value <<= 8;
    value |= static_cast<unsigned char>(c);
  }

  return value;
}

int instruction_length_of(const std::string& line) {

  std::string mnemonic = mnemonic_of(line);

  if (optab.find(mnemonic) != optab.end())
    return mnemonic_prefix_of(line) == '+' ? 4 : optab[mnemonic].format;
  else if (mnemonic == "WORD")
    return 3;

  std::string operand = operand_of(line);

  if (mnemonic == "RESW")
    return 3 * std::stoi(operand);
  else if (mnemonic == "RESB")
    return std::stoi(operand);
  else if (mnemonic == "BYTE")
    return 3 * (operand.find_last_of("\'") - operand.find("\'") - 1);

  return 0;
}

bool is_a_comment(const std::string& line) {
  return line[0] == '.';
}

std::string symbol_of(const std::string& line) {
  return std::isspace(line[0]) ? "" : line.substr(0, line.find_first_of(" \t\r"));
}

std::string mnemonic_of(const std::string& line) {
  return line.size() < 11 || is_a_comment(line) ? "" : line.substr(10, line.substr(10).find_first_of(" \t\r"));
}

bool is_whitespace(const std::string str) {
  for (char c : str)
    if (!std::isspace(c))
      return false;
  return true;
}

char mnemonic_prefix_of(const std::string& line) {
  return line.size() < 10 ? ' ' : line[9];
}

char operand_prefix_of(const std::string& line) {
  return line.size() < 18 ? ' ' : line[17];
}

std::string operand_of(const std::string& line) {
  return line.size() < 19 || is_whitespace(line.substr(18)) ? "" : line.substr(18, line.substr(18).find_first_of(" \t\r"));
}
