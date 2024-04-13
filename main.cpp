
#include "parse.h"
#include "types.h"

#include <iostream>
#include <fstream>

/*
g++ -std=c++11 main.cpp types.cpp parse.cpp -oasl && ./asl test.sic
g++ -g -std=c++11 main.cpp types.cpp parse.cpp -odebug && gdb debug
*/

int main(int argc, char* argv[]) {

  std::string s;

  SymbolTable symtab;

  std::ifstream file(argv[1]);

  if (!file.is_open()) {
    std::cout << "file open failed";
    return 1;
  }

  int location_counter = 0;
  std::string line;

  for (std::getline(file, line); mnemonic_of(line) != "START"; std::getline(file, line));

  location_counter = std::stoi(operand_of(line));
  symtab.csect = { symbol_of(line), location_counter, 0 };

  do
  {
    std::getline(file, line);

    if (is_a_comment(line))
      continue; // dont do mnemonic == END check

    std::cout << line << "\n";

  } while (mnemonic_of(line) != "END");

  std::cout << symtab.to_string();

  return 0;
}
