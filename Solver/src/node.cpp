#include "node.hpp"

Node::Node(Point PosMan, std::vector<Point> &PosJew){
  static unsigned int counter = 0;

  if(counter++ % 1000 == 0){
    std::cout << "created nodes in % : " << (double(counter)/9107001)*100 << std::endl;
  }
  this->PosMan = PosMan;
  this->PosJew = PosJew;
  //children.reserve(8); // slows down

  if(PosMan.x == 1 or PosMan.x == 10){
    //std::cout << "Box in outersides" << PosMan<< std::endl;
  }

  if(PosMan.y == 1 or PosMan.y == 5){
    //std::cout << "Box in upper/lower sides:" << PosMan << std::endl;
  }

}
[[deprecated]]
void Node::Insert(Map & map,Point PosMan, std::vector<Point> &PosJew){
  if (map[PosMan] == '.'){
    Node * node = new Node(PosMan,PosJew);
    children.push_back(node);
  }
}
