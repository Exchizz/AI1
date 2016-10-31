#include "tree.hpp"
#include <iostream>

void Tree::GenerateTree(Map &map){
  this->map = map;
  // NOTE find only returns one element since there is only one man in the map.
  Point PosMan = map.Find('M')[0];
  auto PosJew = map.Find('J');

  root = new Node(PosMan,PosJew);

  // NOTE Insert four nodes
  //root->Insert(map, PosMan.Up(), PosJew );
  root->Insert(map, PosMan.Down(), PosJew );
  //root->children[0]->Insert(map, root->children[0]->PosMan.Down(), PosJew);
  //root->Insert(map, PosMan.Left(), PosJew );
  //root->Insert(map, PosMan.Right(), PosJew );

  // NOTE recursive generte the tree
  RecursiveSomething(*root);

}

unsigned int Tree::Nodes(){
  unsigned int count = 0;
  count = _Nodes(root);
  return count;
}

unsigned int Tree::_Nodes(Node* node){
  unsigned int count = 0;
  std::cout << "children: " << node->children.size() << std::endl;
  for(auto &child : node->children){
    count = count + _Nodes(child) + 1;
  }
  return count;
}


void Tree::RecursiveSomething(Node &node){
  std::cout << "Current node: " << node.PosMan.x << "," << node.PosMan.y << std::endl;
  for(auto &child : node.children){
      // NOTE Insert four nodes
      //child->Insert(map, node.PosMan.Up(), node.PosJew );
      child->Insert(map, node.PosMan.Down(), node.PosJew );
      //child->Insert(map, node.PosMan.Left(), node.PosJew );
      //child->Insert(map, node.PosMan.Right(), node.PosJew );
      //std::cout << "cp: " << node.PosMan.x << "," << node.PosMan.y << " size: " << node.children.size() <<  std::endl;

      RecursiveSomething(*child);
  }
}
