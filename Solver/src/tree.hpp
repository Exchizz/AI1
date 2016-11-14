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

    std::vector<uint16_t> points;


    for(auto jew : node->PosJew){
      point.in[0] = jew.x;
      point.in[1] = jew.y;

      points.push_back( point.out );
    }

    point.in[0] = node->PosMan.x;
    point.in[1] = node->PosMan.y;

    points.push_back( point.out );


    std::sort(points.begin(), points.end());
    uint64_t sum = 0 ;
    //for(auto elm : points){
    for(int i = 0; i < points.size(); i++){
      sum += (uint64_t)points[i] << i*sizeof(uint16_t);
    }

    xy << sum << std::endl;
    std::cout << node->PosMan << "sum : "<< xy.str() << std::endl;
    return xy.str();
  }
};
#endif
