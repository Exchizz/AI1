#include "map.hpp"
#include "node.hpp"

#ifndef TREE_H
#define TREE_H

class Tree {
private:
public:
  void GenerateTree(Map &map);
  void Insert(Point , Point);
  void RecursiveSomething(Node &node);
  unsigned int Nodes();
  unsigned int _Nodes(Node*);
  Map map;
  Node * root;
};
#endif
