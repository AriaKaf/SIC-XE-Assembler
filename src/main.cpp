
#include "format.h"
#include "optab.h"
#include "parse.h"
#include "types.h"

#include <iomanip>
#include <iostream>
#include <fstream>

/*
g++ -std=c++11    main.cpp types.cpp parse.cpp optab.cpp format.cpp -oasl && ./asl test.sic
g++ -g -std=c++11 main.cpp types.cpp parse.cpp optab.cpp format.cpp -odebug && gdb debug

TODO
wants specific number of cpp/h?
don't print comments before start
",X" on format 4?
2's complement for disp
base is unsigned (only sees forward)
no pc relative if i and no n, or e flag is set
evaluate_expr for BASE operand (?)

2.3.2 symbol defining statements
handle sourcecode litpools (can ignore (?))

*/

int main(int argc, char* argv[]) {

  if (argc == 1) {
    std::cout << "error: please provide one or more file paths\n";
    return 1;
  }

  SymbolTable symtab;
  LiteralTable littab;
  std::ifstream source(argv[1]);

  if (!source.is_open()) {
    std::cout << "file open failed";
    return 1;
  }

  OpTab::init();

  int location_counter = 0;
  std::string line;

  for (std::getline(source, line); is_a_comment(line); std::getline(source, line)); // get the first non-comment line

  location_counter = mnemonic_of(line) == "START" ? std::stoi(operand_of(line)) : 0;
  symtab.csect = { symbol_of(line), location_counter, 0 };

  do // first pass to fill up the symtab & littab
  {
    std::getline(source, line);

    if (is_a_comment(line) || line[0] == '*')
      continue;

    if (operand_prefix_of(line) == '=' && !littab.contains(line.substr(20, line.substr(20).find("\'"))))
    { // found a new literal on this line
      char literal_prefix = line[18];

      std::string literal_name;
      int literal_value;
      int literal_length; // can't deduce the address until LTORG or end of source

      literal_name = literal_name_of(line);

      if (literal_prefix == 'X') {
        literal_value = std::stoi(literal_name, nullptr, 16);
        literal_length = literal_name.size() / 2;
        littab.literals.push_back
        ({ literal_name, literal_value, NO_ADDR, literal_length, false, false, 'C' });
      }
      else if (literal_prefix == 'C') {
        literal_value = ascii_to_int(literal_name);
        literal_length = literal_name.size();
        littab.literals.push_back
        ({ literal_name, literal_value, NO_ADDR, literal_length, false, false, 'C' });
      }
    }

    if (!symbol_of(line).empty() && line[0] != '*')
      symtab.handle(line, location_counter);

    if (mnemonic_of(line) == "END" || mnemonic_of(line) == "LTORG")
      littab.pool(location_counter); // assign addresses to all literals encountered thus far

    location_counter += instruction_length_of(line);
  } while (mnemonic_of(line) != "END");

  symtab.csect.length = location_counter - symtab.csect.address;

  source.clear();
  source.seekg(0, std::ios::beg);

  location_counter = symtab.csect.address;
  int program_counter = location_counter;
  int base = NO_ADDR;

  do // second pass to create the listing file
  {
    std::getline(source, line);

    if (operand_prefix_of(line) == '=')
      littab.set_visited(literal_name_of(line));

    if (is_a_comment(line)) {
      std::cout << "        " << line << "\n";
      continue;
    }
    if (line[0] == '*')
      continue;

    if (line.size() >= 42)
      line = line.substr(0, 41); // erase trailing comments

    if (mnemonic_of(line) == "BASE")
      base = symtab[operand_of(line)].value;

    if (mnemonic_of(line) == "NOBASE")
      base = NO_ADDR;

    program_counter += instruction_length_of(line);

    if (mnemonic_of(line) == "END" || mnemonic_of(line) == "LTORG")
    { // make a literal pool in the listing file
      if (mnemonic_of(line) == "LTORG")
        std::cout << std::right << std::setw(23) << "LTORG" << "\n";
      for (Literal& l : littab.literals) {
        if (l.visited && !l.defined) {
          l.defined = true;
          std::cout
            << std::left << std::setw(8) << to_hex_string(location_counter, 4)
            << "*        =" << l.prefix << "\'" << l.name << std::setw(28)
            << "\'" << std::hex << std::uppercase << l.value << "\n";
          location_counter += l.length;
          program_counter += l.length;
        }
      }
    }

    std::string object_code =
      generate_object_code(line, symtab, littab, location_counter, program_counter, base);

    if (mnemonic_of(line) != "LTORG")
      std::cout
      << std::left << std::setw(8) << to_hex_string(location_counter, 4)
      << std::setw(43) << line << object_code << "\n";

    location_counter += instruction_length_of(line);

  } while (mnemonic_of(line) != "END");

  std::cout << "\n" << symtab.to_string() << "\n" << littab.to_string();

  return 0;
}
