#include "map.hpp"
#include "node.hpp"
#include "colors.hpp"
#include <unordered_map>

#ifndef TREE_H
#define TREE_H

#define UP 1
#define LEFT 2
#define RIGHT 3
#define DOWN 4

class Tree {
private:
public:
  std::vector<Point> GenerateTree(Map &map);
  void Insert(Point , Point);
  //Map * ConstructMap();
  std::vector<Point> ExploreMap(Node *node);
  void _ExploreMap(Node *node);
  unsigned int Nodes();
  unsigned int _Nodes(Node*);
  Map map;
  Node * root;
  std::vector<Point> points;
  int counter_debug = 0;
  void Insert(Node * child, int action);
  Node * GenerateNode(Node * child, int action);

  std::unordered_map<Node, int> NodesInTree;
};
#endif
