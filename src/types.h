
#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <unordered_map>

enum Flag { RELATIVE, ABSOLUTE };

struct CsectInfo {
  std::string name;
  int address;
  int length;
};

struct SymbolInfo {
  int value;
  Flag flag;
};

class SymbolTable {

public:
  std::string to_string();

  CsectInfo csect;
  std::unordered_map<std::string, SymbolInfo> table;

  const SymbolInfo& operator[](const std::string& key) const {
    auto it = table.find(key);
    if (it != table.end())
      return it->second;
    else
      throw std::out_of_range("Key not found in SymbolTable");
  }

  SymbolInfo& operator[](const std::string& key) {
    return table[key];
  }
};

#endif
