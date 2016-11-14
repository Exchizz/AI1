#include "node.hpp"

Node::Node(Point PosMan, std::vector<Point> &PosJew){
  this->PosMan = PosMan;
  this->PosJew = PosJew;
  //children.reserve(8); // slows down
/*
  if(PosMan.x == 1 or PosMan.x == 6){
    std::cout << "Box in outersides" << PosMan<< std::endl;
  }

  if(PosMan.y == 1 or PosMan.y == 6){
    std::cout << "Box in upper/lower sides:" << PosMan << std::endl;
  }
  */
}
[[deprecated]]
void Node::Insert(Map & map,Point PosMan, std::vector<Point> &PosJew){
  if (map[PosMan] == '.'){
    Node * node = new Node(PosMan,PosJew);
    children.push_back(node);
  }
}
