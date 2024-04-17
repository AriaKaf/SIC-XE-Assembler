
#include "optab.h"
#include "parse.h"
#include "types.h"

#include <iostream>
#include <fstream>

/*
g++ -std=c++11    main.cpp types.cpp parse.cpp optab.cpp -oasl && ./asl test.sic
g++ -g -std=c++11 main.cpp types.cpp parse.cpp optab.cpp -odebug && gdb debug

TODO
handle no start directive
2.3.2 symbol defining statements
handle sourcecode litpools
literal length in bytes could decimal (odd # of hex chars)
calculate flags
*/

int main(int argc, char* argv[]) {

  if (argc == 1) {
    std::cout << "error: please provide one or more file paths\n";
    return 1;
  }

  SymbolTable symtab;
  LiteralTable littab;
  std::ifstream file(argv[1]);

  if (!file.is_open()) {
    std::cout << "file open failed";
    return 1;
  }

  OpTab::init();

  int location_counter = 0;
  std::string line;

  for (std::getline(file, line); is_a_comment(line); std::getline(file, line)); // get the first non-comment line

  location_counter = std::stoi(operand_of(line));
  symtab.csect = { symbol_of(line), location_counter, 0 };

  do // first pass to fill up the symtab & littab
  {
    std::getline(file, line);

    if (is_a_comment(line))
      continue;

    if (operand_prefix_of(line) == '=' && !littab.contains(line.substr(20, line.substr(20).find("\'"))))
    { // found a new literal in this line
      char literal_prefix = line[18];

      std::string literal_name;
      int literal_value;
      int literal_length; // can't deduce the address until LTORG or end of file

      literal_name = line.substr(20, line.substr(20).find("\'"));

      if (literal_prefix == 'X') {
        literal_value = std::stoi(literal_name, nullptr, 16);
        literal_length = literal_name.size() / 2;
      }
      else if (literal_prefix == 'C') {
        literal_value = ascii_to_int(literal_name);
        literal_length = literal_name.size();
      }

      littab.literals.push_back({ literal_name, literal_value, NO_ADDR, literal_length });
    }

    if (!symbol_of(line).empty() && line[0] != '*')
      symtab[symbol_of(line)] = { location_counter, RELATIVE };

    if (mnemonic_of(line) == "END" || mnemonic_of(line) == "LTORG")
    { // create a 'literal pool' (calculate all currently unresolved literal addresses)
      for (Literal& l : littab.literals) {
        if (l.address == NO_ADDR) {
          l.address = location_counter;
          location_counter += l.length;
        }
      }
    }

    location_counter += instruction_length_of(line);
  } while (mnemonic_of(line) != "END");

  symtab.csect.length = location_counter - symtab.csect.address;

  std::cout << symtab.to_string() << "\n" << littab.to_string();

  return 0;
}
