#include "map.hpp"
#include "node.hpp"
#include "colors.hpp"
#include <unordered_map>
#include <queue>
#include <sstream>
#include "murmur3.h"
#ifndef TREE_H
#define TREE_H



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
  std::vector<Point> PosGoals;
  std::vector<Point> points;
  int counter_debug = 0;
  void BredthFirst(Node * root);
  bool IsGoal(Node * node);
  void Insert(Node * child, int action);
  Node * GenerateNode(Node * child, int action);

  std::unordered_map<std::string, Node*> NodesInTree;

  Tree(){
    NodesInTree.reserve(32000000);
  }

  union {
    uint8_t in[2];
    uint16_t out;
  } point;

  std::string hash(Node * node){
    std::stringstream xy;

    xy << node->PosMan.x << node->PosMan.y << std::endl;

    std::vector<Point> points;


    for(auto jew : node->PosJew){
      points.push_back( jew );
    }

    std::sort(points.begin(), points.end());


    for(auto elm : points){
        xy <<  elm << std::endl;
    }

  //  xy << sum << std::endl;
    //std::cout << node->PosMan << "sum : "<< xy.str() << std::endl;
    //std::cout << xy.str() << std::endl;
    return xy.str();
  }
};
#endif
