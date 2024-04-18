
#ifndef PARSE_H
#define PARSE_H

#include "types.h"

#include <string>

Flag evaluate_flag(const std::string& expr, const SymbolTable& stab);

int evaluate_expr(const std::string& expr, const SymbolTable& stab, int locctr);
int ascii_to_int(const std::string& ascii);
int instruction_length_of(const std::string& line);

char mnemonic_prefix_of(const std::string& line);
char operand_prefix_of(const std::string& line);

bool is_a_comment(const std::string& line);

std::string generate_object_code(const std::string& line,
  const SymbolTable& stab,
  const LiteralTable& littab,
  int locctr,
  int program_counter,
  int base);

std::string symbol_of(const std::string& line);
std::string mnemonic_of(const std::string& line);
std::string operand_of(const std::string& line);
std::string literal_name_of(const std::string& line);

#endif
