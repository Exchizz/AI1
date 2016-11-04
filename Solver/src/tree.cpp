#include "tree.hpp"
#include <iostream>

std::vector<Point> Tree::GenerateTree(Map &map){
  this->map = map;
  // NOTE find only returns one element since there is only one man in the map.
  Point PosMan = map.Find('M')[0];
  auto PosJew = map.Find('J');

  root = new Node(PosMan,PosJew);

  // NOTE Insert four nodes (depricated)
  //root->Insert(map, PosMan.Up(), PosJew );
  //root->Insert(map, PosMan.Down(), PosJew );
  //root->children[0]->Insert(map, root->children[0]->PosMan.Down(), PosJew);
  //root->Insert(map, PosMan.Left(), PosJew );
  //root->Insert(map, PosMan.Right(), PosJew );
  Insert(root, LEFT);
  Insert(root, DOWN);
  Insert(root, RIGHT);
  ///Insert(root, UP);



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



Node * Tree::GenerateNode(Node * child, int action){
  //if (map.inMap(child->PosMan) && map[child->PosMan] != 'X'){
    switch(action){
        case UP:
            if (map.inMap(child->PosMan.Up()) && map[child->PosMan.Up()] != 'X' ){
                Node * node = new Node(child->PosMan.Up(),child->PosJew); // Risk of memory leak - check smartpointer
                return node;
            }
        break;

        case DOWN:
            if (map.inMap(child->PosMan.Down()) && map[child->PosMan.Down()] != 'X'){
              Node * node = new Node(child->PosMan.Down(),child->PosJew); // Risk of memory leak - check smartpointer
              return node;
            }
        break;

        case LEFT:
            if (map.inMap(child->PosMan.Left()) && map[child->PosMan.Left()] != 'X'){
              Node * node = new Node(child->PosMan.Left(),child->PosJew); // Risk of memory leak - check smartpointer
              return node;
            }
        break;

        case RIGHT:
            if (map.inMap(child->PosMan.Right()) && map[child->PosMan.Right()] != 'X'){
              Node * node = new Node(child->PosMan.Right(),child->PosJew); // Risk of memory leak - check smartpointer
              return node;
            }
        break;
    }
  return nullptr;
}

void Tree::Insert(Node * child, int action){
  auto NewNode = GenerateNode(child, action);
  // If node can't be created, don't insert one
  if(NewNode == nullptr)
    return;

  auto retpair = NodesInTree.emplace(*NewNode,1);
  if(retpair.second){
    child->children.push_back(NewNode);
  } else {
    delete NewNode; // Cleanup memomory
    std::cout << "Node already exists, cleaning up" << std::endl;
  }
}

void Tree::_ExploreMap(Node *node){
  if(counter_debug++ > 50)  {
      std::cout << "too many recursive calls " << std::endl;
      return;
  }
  std::cout << FMAG("Current node: ") << node->PosMan.x << "," << node->PosMan.y << std::endl;
  for(auto &child : node->children){
      // NOTE Insert four nodes
      //child->Insert(map, child->PosMan.Up(), child->PosJew );
      //child->Insert(map, child->PosMan.Down(), child->PosJew );
      //child->Insert(map, child->PosMan.Left(), child->PosJew );
      //child->Insert(map, child->PosMan.Right(), child->PosJew );
      //Insert(child, UP);
      Insert(child, DOWN);
      Insert(child, LEFT);
      Insert(child, RIGHT);
      _ExploreMap(child);
  }
}