
#include "types.h"

#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) {

  SymbolTable st;
                //value   //length //flag
  st["SUM"]    = { 0,      0x2f0a, NO_FLAG  };
  st["FIRST"]  = { 0,      0,      RELATIVE };
  st["LOOP"]   = { 0XA,    0,      RELATIVE };
  st["MYLIT"]  = { 0X1D,   0,      RELATIVE };
  st["COUNT"]  = { 0X21,   0,      RELATIVE };
  st["TABLE"]  = { 0X24,   0,      RELATIVE };
  st["TABLE2"] = { 0X1794, 0,      RELATIVE };
  st["TOTAL"]  = { 0X2F04, 0,      RELATIVE };

  std::cout << to_string(st) << "\n";

  LiteralTable lt;

  lt["EOF"] = { 0x454f46, 0x2f07, 3 };

  std::cout << to_string(lt) << "\n";
  
  return 0;
}
