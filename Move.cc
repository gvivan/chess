#include "Move.h"


int coordinateToInt(std::string coordinate) {
  int x = coordinate[0] - 'a';
  int y = (int)(coordinate[1] - '0' - 1);
  return y * 8 + x;
}
