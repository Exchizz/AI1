#include "tree.hpp"
#include <iostream>
#include <cassert>

std::vector<Point> Tree::GenerateTree(Map &map){
  this->map = map;
  // NOTE find only returns one element since there is only one man in the map.
  Point PosMan = map.Find('M')[0];
  auto PosJew = map.Find('J');

  root = new Node(PosMan,PosJew);
  // Add root note to hashmap
  NodesInTree.emplace(*root,root);

  // NOTE Insert four nodes
  Insert(root, LEFT);
  Insert(root, DOWN);
  Insert(root, RIGHT);
  Insert(root, UP);

  // NOTE recursively explore the map
  auto ManPositions = ExploreMap(root);
  return ManPositions;
}

unsigned int Tree::Nodes(){
  unsigned int count = 0;
  count = _Nodes(root);
  return count;
}

unsigned int Tree::_Nodes(Node * node){
      std::cout << "Node: " << node->PosMan  << std::endl;
      if(node->children.size() == 0){
        return 0;
      }
      int count = 0;
      for(auto child : node->children){
        count += _Nodes(child);
      }
      return count + 1;
}
/*
unsigned int Tree::_Nodes(Node* node){
  unsigned int count = 0;
  //std::cout << "children: " << node->children.size() << std::endl;
  for(auto &child : node->children){
    count = count + _Nodes(child) + 1;
    points.push_back( child->PosMan );
  }
  return count;
}
*/
/*
Map * Tree::ConstructMap(){
  // Clone original map. Clone() simply makes a deep copy of the original map.
  Map *NewMap = map.Clone();
  auto PosMan = map.Find('M')[0];
  NewMap->SetMan(PosMan);
  return NewMap;
}
*/
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

void Tree::Insert(Node * parent, int action){
  auto NewNode = GenerateNode(parent, action);
  // If node can't be created, don't insert one
  if(NewNode == nullptr)
    return;

  auto retpair = NodesInTree.emplace(*NewNode,NewNode); // returns 1 if new node inserted, else 0
    /*
      if = iterrator to element
        element:
          first: key
          second: value
      second = success if insert
    */
  if(retpair.second){
    parent->children.push_back(NewNode);
  } else {
    std::cout << "Dublicate node: " << NewNode->PosMan << " parent: " << parent->PosMan << std::endl;
    delete NewNode; // Delete the newly created node since it already exists. Use the variable NewNode anyways.
    NewNode = (*retpair.first).second;


    int tjek = 0;
    for(auto elm: parent->children ){
      std::cerr << "\t if: "<< elm->PosMan <<  " newNode: " << NewNode->PosMan << std::endl;
      if( elm->PosMan == NewNode->PosMan){
          tjek = 1;
          std::cerr << "child exists, continuing, number of children in parents: " << parent->children.size() << std::endl;
          return;
      }
    }

    assert(tjek <= 1);
    if(tjek == 0){
      parent->children.push_back(NewNode);
      std::cerr << "Creating first relation node: child:" << NewNode->PosMan <<  " parent: " << parent->PosMan << " children: " << parent->children.size()  <<  std::endl;
    }
  }
}

std::vector<Point> Tree::ExploreMap(Node *node){
  _ExploreMap(node);
  return points;
}

void Tree::_ExploreMap(Node *node){
  if(node->discovered){
    return ;
  }
  node->discovered = true;

  if(counter_debug++ > 100)  {
      std::cout << FMAG("Too many recursive calls") << std::endl;
      return;
  }
  //std::cout << FMAG("Current node: ") << node->PosMan.x << "," << node->PosMan.y << std::endl;
  for(auto &child : node->children){
      // NOTE Insert four nodes
      //child->Insert(map, child->PosMan.Up(), child->PosJew );
      //child->Insert(map, child->PosMan.Down(), child->PosJew );
      //child->Insert(map, child->PosMan.Left(), child->PosJew );
      //child->Insert(map, child->PosMan.Right(), child->PosJew );
      Insert(child, UP);
      Insert(child, DOWN);
      Insert(child, LEFT);
      Insert(child, RIGHT);
      _ExploreMap(child);
  }
}
