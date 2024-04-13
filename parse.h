
#ifndef PARSE_H
#define PARSE_H

#include <string>

bool is_a_comment(const std::string& line);

std::string symbol_of(const std::string& line);
std::string mnemonic_of(const std::string& line);
std::string operand_of(const std::string& line);

#endif
