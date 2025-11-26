#ifndef UTIL_H
#define UTIL_H


#include <iostream> 
#include "colors.h"

namespace util {
inline void errorInvalidMove() {
  std::cout << RED << "\n** ERROR: invalid move, please re-enter your move" << RESET;
}

inline void errorNoTokenHere(int y, int x) {
  std::cout << RED << "** ERROR: no token at row " << y << " column " << x << RESET;
} 

inline void debugPrint(std::string message) {
  std::cout << GREEN << "** Debug: " << message << RESET << std::endl;
}
}

#endif 

