
#ifndef PARSE_H
#define PARSE_H

#include <string>

int ascii_to_int(const std::string& ascii);

char mnemonic_prefix_of(const std::string& line);

char operand_prefix_of(const std::string& line);

int instruction_length_of(const std::string& line);

bool is_a_comment(const std::string& line);

std::string symbol_of(const std::string& line);

std::string mnemonic_of(const std::string& line);

std::string operand_of(const std::string& line);

#endif
