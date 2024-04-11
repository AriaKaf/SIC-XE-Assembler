
#include "parse.h"
#include "types.h"

#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {

  SymbolTable st;

  std::ifstream file(argv[1]);

  if (!file.is_open()) {
    std::cout << "file open failed";
    return 1;
  }

  int location_counter = 0;
  std::string line, csect = "";

  std::getline(file, line);

  if (mnemonic_of(line) == "START") {
    location_counter = std::stoi(operand_of(line));
    csect = symbol_of(line);
  } else {
    file.clear();
    file.seekg(0, std::ios::beg);
  }

  do
  {
    std::getline(file, line);
    // update symtab
  } while (mnemonic_of(line) != "END");

  return 0;
}
