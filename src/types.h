
#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <unordered_map>
#include <vector>

#define NO_ADDR -1

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

struct Literal {
  std::string name;
  int value;
  int address;
  int length;
};

class LiteralTable {  
public:
  void pool(int& locctr);
  std::vector<Literal> literals;
  bool contains(const std::string& name);
  std::string to_string();
};

class SymbolTable {

public:
  void handle(const std::string& line, int locctr);
  bool contains(const std::string& key) const;
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
