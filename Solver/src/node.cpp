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
}
