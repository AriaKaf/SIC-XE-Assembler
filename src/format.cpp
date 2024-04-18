
#include "format.h"

#include "types.h"

#include <iomanip>
#include <sstream>

std::string to_hex_string(int num, int width) {
  std::stringstream ss;
  if (width != 0)
    ss << std::right << std::setw(width) << std::hex << std::uppercase << std::setfill('0') << num;
  else
    ss << std::hex << std::uppercase << num;
  return ss.str();
}
