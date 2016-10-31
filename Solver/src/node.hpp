#include "point.hpp"
#include "map.hpp"
#include <vector>
#ifndef NODE_H
#define NODE_H

class Node {
public:
  Node(Point, std::vector<Point>&);
  bool Visited = false;
  std::vector<Node*> children;

  void Insert(Map &,Point, std::vector<Point> &);
  Point PosMan;
  std::vector<Point> PosJew;
};

#endif
