#include "map.hpp"
#include "node.hpp"
#include "colors.hpp"
#include <unordered_map>
#include <queue>
#include <sstream>
#include <functional>
#ifndef TREE_H
#define TREE_H



class Tree {
private:
public:
  void GenerateTree(Map &map);
  void Insert(Point , Point);
  //Map * ConstructMap();
  std::vector<Point> ExploreMap(Node *node);
  void _ExploreMap(Node *node);
  unsigned int Nodes();
  unsigned int _Nodes(Node*);
  Map map;
  Node * root;
  std::vector<Point> PosGoals;
  std::vector<Point> points;
  int counter_debug = 0;
  /* Solvers */
  void BredthFirst();
  void Dijkstra();
  void AStar(int (Tree::*H)( int), Tree& a);
  /* Solvers end */

  int h1(int);

  bool IsGoal(Node * node);
  void Insert(Node * child, int action);
  Node * GenerateNode(Node * child, int action);

  std::unordered_map<std::string, Node*> NodesInTree;


  std::string hash(Node * node){
    std::stringstream xy;

    xy << node->PosMan.x << node->PosMan.y << std::endl;

    std::sort(node->PosJew.begin(), node->PosJew.end());

    for(auto elm : node->PosJew){
        xy <<  elm << std::endl;
    }
    return xy.str();
  }
};
#endif
