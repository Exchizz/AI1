#include "node.hpp"

Node::Node(Point PosMan, std::vector<Point> &PosJew){
  this->PosMan = PosMan;
  this->PosJew = PosJew;
}
[[deprecated]]
void Node::Insert(Map & map,Point PosMan, std::vector<Point> &PosJew){
  if (map[PosMan] == '.'){
    Node * node = new Node(PosMan,PosJew);
    children.push_back(node);
  }
}
