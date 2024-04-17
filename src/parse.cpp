
#include "optab.h"
#include "parse.h"

#include <iomanip>
#include <sstream>

void trim(std::string& s) {
  size_t begin = s.find_first_not_of(" \t\r");
  size_t end = s.find_last_not_of(" \t\r");
  s = s.substr(begin, end - begin + 1);
}

bool is_numeric(const std::string& s) {
  for (char c : s)
    if (!std::isdigit(c))
      return false;
  return true;
}

int evaluate_term(std::string term, const SymbolTable& stab, int locctr) {
  trim(term);
  if (term == "*")
    return locctr;
  if (is_numeric(term))
    return std::stoi(term);
  if (stab.contains(term))
    return stab[term].value;
}

size_t least_precedence_operator_pos(const std::string& str) {
  if (str.find_first_of("+-") != std::string::npos) {
    for (int i = str.size() - 1; i >= 0; i--)
      if (str[i] == '+' || str[i] == '-')
	return i;
  } else {
    for (int i = str.size() - 1; i >= 0; i--)
      if (str[i] == '*' || str[i] == '/')
	return i;
  }
}

Flag evaluate_flag(const std::string& expr, const SymbolTable& stab) {

  int relative_additions = 0, relative_subtractions = 0;

  std::stringstream token;
  char c, last_operator;
  std::istringstream is(expr);

  is >> std::skipws;
  
  while (is >> c && std::string("*=-/").find(c) == std::string::npos)
    token << c;
  last_operator = c;

  if (stab.contains(token.str()) && stab[token.str()].flag == RELATIVE)
    relative_additions++;
  token.str("");

  while (is >> c) {
    if (std::string("*+-/").find(c) != std::string::npos) {
      if (stab.contains(token.str()) && stab[token.str()].flag == RELATIVE) {
        if (last_operator == '+')
          relative_additions++;
        else if (last_operator == '-')
          relative_subtractions++;
      }
      last_operator = c;
      token.str("");
    } else
      token << c;
  }

  if (stab.contains(token.str()) && stab[token.str()].flag == RELATIVE) {
    if (last_operator == '+')
      relative_additions++;
    else if (last_operator == '-')
      relative_subtractions++;  
  }
  
  return relative_additions == relative_subtractions ? ABSOLUTE : RELATIVE;
}

int evaluate_expr(const std::string& expr, const SymbolTable& stab, int locctr) {

  if (expr.find_first_of("+*-/") == std::string::npos || expr.find_first_not_of("* \t\r") == std::string::npos)
    return evaluate_term(expr, stab, locctr);

  size_t split = least_precedence_operator_pos(expr);

  switch (expr[split])
  {
    case '+': return evaluate_expr(expr.substr(0, split), stab, locctr) + evaluate_expr(expr.substr(split + 1), stab, locctr);
    case '-': return evaluate_expr(expr.substr(0, split), stab, locctr) - evaluate_expr(expr.substr(split + 1), stab, locctr);
    case '*': return evaluate_expr(expr.substr(0, split), stab, locctr) * evaluate_expr(expr.substr(split + 1), stab, locctr);
    case '/': return evaluate_expr(expr.substr(0, split), stab, locctr) / evaluate_expr(expr.substr(split + 1), stab, locctr);
  }
}

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

  if (line.size() >= 42 && !is_whitespace(line.substr(41)))
    return line.substr(18, line.substr(18, 23).find_last_not_of(" \t\r") + 1);
  
  return line.size() < 19 || is_whitespace(line.substr(18)) ? "" : line.substr(18, line.substr(18).find_last_not_of(" \t\r") + 1);
}
