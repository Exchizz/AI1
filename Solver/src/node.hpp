#include "point.hpp"
#include <vector>
#ifndef NODE_H
#define NODE_H

class Node {
public:
  Node(Point, std::vector<Point>&);
  bool Visited;
private:
  Point PosMan;
  std::vector<Point> PosJew;
};

#endif
