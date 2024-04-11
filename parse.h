
#ifndef PARSE_H
#define PARSE_H

#include <string>

std::string symbol_of(const std::string& line);
std::string mnemonic_of(const std::string& line);
std::string operand_of(const std::string& line);

#endif
