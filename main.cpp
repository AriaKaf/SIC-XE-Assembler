
#include "parse.h"
#include "types.h"

#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {

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
  symtab.push_back(StabEntry(symbol_of(line), "", location_counter, 0, CSECT));

  do
  {
    std::getline(file, line);
    // update symtab
  } while (mnemonic_of(line) != "END");

  return 0;
}
