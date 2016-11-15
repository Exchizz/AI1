#include "node.hpp"

Node::Node(Point PosMan_p, std::vector<Point> &PosJew_p){
/*
  if(counter++ % 1000 == 0){
    std::cout << "created nodes in % : " << (double(counter)/9107001)*100 << std::endl;
  }
  */
  this->PosMan = PosMan_p;
  this->PosJew = PosJew_p;
  //children.reserve(8); // slows down

  if(PosMan.x == 1 or PosMan.x == 10){
    //std::cout << "Box in outersides" << PosMan<< std::endl;
  }

  if(PosMan.y == 1 or PosMan.y == 5){
    //std::cout << "Box in upper/lower sides:" << PosMan << std::endl;
  }

}
[[deprecated]]
void Node::Insert(Map & map,Point PosMan_p, std::vector<Point> &PosJew_p){
  if (map[PosMan_p] == '.'){
    Node * node = new Node(PosMan_p,PosJew_p);
    children.push_back(node);
  }
}
