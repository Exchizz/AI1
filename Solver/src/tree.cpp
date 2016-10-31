#include "tree.hpp"
#include <iostream>

std::vector<Point> Tree::GenerateTree(Map &map){
  this->map = map;
  // NOTE find only returns one element since there is only one man in the map.
  Point PosMan = map.Find('M')[0];
  auto PosJew = map.Find('J');

  root = new Node(PosMan,PosJew);

  // NOTE Insert four nodes
  //root->Insert(map, PosMan.Up(), PosJew );
  root->Insert(map, PosMan.Down(), PosJew );
  //root->children[0]->Insert(map, root->children[0]->PosMan.Down(), PosJew);
  root->Insert(map, PosMan.Left(), PosJew );
  root->Insert(map, PosMan.Right(), PosJew );

  // NOTE recursively explore the map
  auto ManPositions = ExploreMap(root);
  return ManPositions;
}

unsigned int Tree::Nodes(){
  unsigned int count = 0;
  count = _Nodes(root);
  return count;
}
unsigned int Tree::_Nodes(Node* node){
  unsigned int count = 0;
  //std::cout << "children: " << node->children.size() << std::endl;
  for(auto &child : node->children){
    count = count + _Nodes(child) + 1;
    points.push_back( child->PosMan );
  }
  return count;
}

/*
Map * Tree::ConstructMap(){
  // Clone original map. Clone() simply makes a deep copy of the original map.
  Map *NewMap = map.Clone();
  auto PosMan = map.Find('M')[0];
  NewMap->SetMan(PosMan);
  return NewMap;
}
*/
std::vector<Point> Tree::ExploreMap(Node *node){
  _ExploreMap(node);
  return points;
}

void Tree::_ExploreMap(Node *node){
  if(counter_debug++ > 20)  return;
  std::cout << FMAG("Current node: ") << node->PosMan.x << "," << node->PosMan.y << std::endl;
  for(auto &child : node->children){
      // NOTE Insert four nodes
      //child->Insert(map, node.PosMan.Up(), node.PosJew );
      child->Insert(map, child->PosMan.Down(), child->PosJew );
      child->Insert(map, child->PosMan.Left(), child->PosJew );
      child->Insert(map, child->PosMan.Right(), child->PosJew );
      _ExploreMap(child);
  }
}
