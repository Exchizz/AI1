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

  // Remove jew's and man from the map - we carry this information in each node anyways
  map.Clean("MJ");

  // NOTE Insert four nodes
  Insert(root, UP);
  Insert(root, DOWN);
  Insert(root, LEFT);
  Insert(root, RIGHT);

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

Node * Tree::GenerateNode(Node * node, int action){

    switch(action){
        case UP:
            if (map.inMap(node->PosMan.Up()) &&  map.IsPosFree(node->PosMan.Up(), node->PosJew) ){
                Node * Newnode = new Node(node->PosMan.Up(),node->PosJew); // Risk of memory leak - check smartpointer
                return Newnode;
            }
        break;

        case DOWN:
            if (map.inMap(node->PosMan.Down()) &&  map.IsPosFree(node->PosMan.Down(), node->PosJew)){
              Node * Newnode = new Node(node->PosMan.Down(),node->PosJew); // Risk of memory leak - check smartpointer
              return Newnode;
            }
        break;

        case LEFT:
            if (map.inMap(node->PosMan.Left()) && !map.IsPosWall( node->PosMan.Left())){
              //std::cout << "Before move: " << node->PosJew[0] << std::endl;
              Node * Newnode = new Node(node->PosMan.Left(),node->PosJew); // Risk of memory leak - check smartpointer
              if(map.TryToMove(node->PosMan.Left(), Newnode->PosJew, action)){
                  return Newnode;
              }
              // If we don't use the node we just created, why save it then
              delete Newnode;
            }
        break;

        case RIGHT:
            if (map.inMap(node->PosMan.Right()) &&  map.IsPosFree(node->PosMan.Right(), node->PosJew)){
              Node * Newnode = new Node(node->PosMan.Right(),node->PosJew); // Risk of memory leak - check smartpointer
              return Newnode;
            }
        break;

        default:
            std::cout << "ERROR: No action given in GenerateNode"  << std::endl;
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
    delete NewNode; // Delete the newly created node since it already exists. Use the variable NewNode anyways.
    NewNode = (*retpair.first).second;


    int tjek = 0;
    for(auto elm: parent->children ){
    if(*elm == *NewNode){
          tjek = 1;
          return;
      }
    }

    assert(tjek <= 1);
    if(tjek == 0){
      parent->children.push_back(NewNode);
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
  for(auto &child : node->children){
      // NOTE Insert four nodes
      Insert(child, UP);
      Insert(child, DOWN);
      Insert(child, LEFT);
      Insert(child, RIGHT);
      _ExploreMap(child);
  }
}
