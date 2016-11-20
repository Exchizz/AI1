#include "point.hpp"
#include "map.hpp"
#include <vector>
#ifndef NODE_H
#define NODE_H

class Node {
public:
  Node(Point, std::vector<Point>&);
  std::vector<Node*> children;

  void Insert(Map &,Point, std::vector<Point> &);
  Point PosMan;
  std::vector<Point> PosJew;
  bool discovered = false;
  bool vizDotVisit = false;
  Node* parent = nullptr;

  bool operator==(const Node & rhs) const {
    bool retval = true;
    for(unsigned int i = 0; i < PosJew.size(); i++){
      retval = retval && (PosJew[i] == rhs.PosJew[i]);
    }

    return (PosMan == rhs.PosMan) && retval;
  }
};

#endif
