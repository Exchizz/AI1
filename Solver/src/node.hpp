#include "point.hpp"
#include "map.hpp"
#include <limits>
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
  bool InOpenList = false;
  Node* parent = nullptr;
  int distance = std::numeric_limits<int>::max();

  bool operator==(const Node & rhs) const {
    bool retval = true;
    for(unsigned int i = 0; i < PosJew.size(); i++){
      retval = retval && (PosJew[i] == rhs.PosJew[i]);
    }

    return (PosMan == rhs.PosMan) && retval;
  }
/*
  bool operator>(const Node * rhs){
    std::cout << "works" << std::endl;
    return (distance < rhs->distance);
  }

*/
};



struct LessThanByDistance
{
  bool operator()(const Node * lhs, const Node * rhs) const
  {
    return (lhs->distance > rhs->distance);
  }
};

#endif
