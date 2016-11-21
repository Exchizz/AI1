#include "tree.hpp"
#include <iostream>
#include <cassert>
#include <stack>
#include <algorithm>
#include<list>




void Tree::GenerateTree(Map &map_p){
  this->map = map_p;

  // NOTE find only returns one element since there is only one man in the map.
  Point PosMan = map.Find('M').front();
  auto PosJew = map.Find('J');
  PosGoals = map.Find('G');

  for(auto elm: PosGoals){
    std::cout << "Found goals: " << elm << std::endl;
  }

  root = new Node(PosMan,PosJew);
  // Add root note to hashmap
  NodesInTree.emplace(hash(root),root);

  // Remove jew's and man from the map - we carry this information in each node anyways
  map.Clean("MJG");

  // NOTE Insert four nodes
  Insert(root, UP);
  Insert(root, DOWN);
  Insert(root, LEFT);
  Insert(root, RIGHT);

  // NOTE recursively explore the map Depth first method
  //auto ManPositions = ExploreMap(root);

  //BredthFirst(root);
  //Dijkstra(root);
  return;
}

unsigned int Tree::Nodes(){
  unsigned int count = 0;
  count = _Nodes(root);
  return count;
}

unsigned int Tree::_Nodes(Node * node){
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
        {
            if (map.inMap(node->PosMan.Up()) && !map.IsPosWall( node->PosMan.Up())){
              Node * Newnode = new Node(node->PosMan.Up(),node->PosJew); // Risk of memory leak - check smartpointer
              if(map.IsPosJew( node->PosJew,node->PosMan.Up())){
                if(map.TryToMove(node->PosMan.Up(), Newnode->PosJew, action)){
                  return Newnode;
                } else {
                  return nullptr;
                }
              }
              return Newnode;
            }
        }
        break;

        case DOWN:
        {
          if (map.inMap(node->PosMan.Down()) && !map.IsPosWall( node->PosMan.Down())){

              Node * Newnode = new Node(node->PosMan.Down(),node->PosJew); // Risk of memory leak - check smartpointer
              if(map.IsPosJew( node->PosJew,node->PosMan.Down())){
                if(map.TryToMove(node->PosMan.Down(), Newnode->PosJew, action)){
                  return Newnode;
                } else {
                  return nullptr;
                }
              }
              return Newnode;
            }
        }
        break;

        case LEFT:
        {
          if (map.inMap(node->PosMan.Left()) && !map.IsPosWall( node->PosMan.Left())){

              Node * Newnode = new Node(node->PosMan.Left(),node->PosJew); // Risk of memory leak - check smartpointer
              if(map.IsPosJew( node->PosJew,node->PosMan.Left())){
                if(map.TryToMove(node->PosMan.Left(), Newnode->PosJew, action)){
                  return Newnode;
                } else {
                  return nullptr;
                }
              }
              return Newnode;
            }
        }
        break;

        case RIGHT:
        {
          if (map.inMap(node->PosMan.Right()) && !map.IsPosWall( node->PosMan.Right())){

              Node * Newnode = new Node(node->PosMan.Right(),node->PosJew); // Risk of memory leak - check smartpointer
              if(map.IsPosJew( node->PosJew,node->PosMan.Right())){
                if(map.TryToMove(node->PosMan.Right(), Newnode->PosJew, action)){
                  return Newnode;
                } else {
                  delete Newnode;
                  return nullptr;
                }
              }
              return Newnode;
            }
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
  auto retpair = NodesInTree.emplace( hash(NewNode), NewNode);
    /*
      if = iterrator to element
        element:
          first: key
          second: value
      second = success if insert
    */
  if(!retpair.second){
    delete NewNode; // Delete the newly created node since it already exists. Use the variable NewNode anyways.
    NewNode = (*retpair.first).second;
  }

  parent->children.push_back(NewNode);
}

std::vector<Point> Tree::ExploreMap(Node *node){
  _ExploreMap(node);
  return points;
}


bool Tree::IsGoal(Node * node){
  unsigned int finish = 0;
  for(auto goal: PosGoals){
    for(auto jew : node->PosJew){
      finish += (goal == jew);
    }
  }
  if(finish == PosGoals.size()){
    std::cout << "Found solution" << std::endl;
    return true;
  }
  return false;
}



int Tree::h1(int data){
  return data;
}
Point BackTrackSolution(Node * node){
    if(node->parent == nullptr){
      return node->PosMan;
    }
    auto ManPosOld = BackTrackSolution(node->parent);

    char out;
    if(node->PosMan.x == ManPosOld.x+1) out = 'R';
    if(node->PosMan.x == ManPosOld.x-1) out = 'L';
    if(node->PosMan.y == ManPosOld.y-1) out = 'U';
    if(node->PosMan.y == ManPosOld.y+1) out = 'D';

    std::cout << out;
    return node->PosMan;
}


typedef int (funk)( int);
void Tree::AStar(int (Tree::*H_p)( int), Tree& obj){

  //funk H = obj.*H_p;
  std::cout << "H: " << (obj.*H_p)(1337) << std::endl;
  std::cout << "-------Using A* search -------" << std::endl;
  std::priority_queue<Node*,std::vector<Node*>,LessThanByDistance> OpenQueue;
  std::list<Node*> ClosedQueue;
  OpenQueue.push(root);
  root->distance = 0;
  while(!OpenQueue.empty()){
    auto current = OpenQueue.top();
    OpenQueue.pop();


    ClosedQueue.push_back(current);
    if(IsGoal(current)){
      std::cout << "Closed queue size: " << ClosedQueue.size() << std::endl;
      std::cout << "Reached goal" << std::endl;
      BackTrackSolution(current);
      std::cout << std::endl;
      std::cout << "Backtrack done" << std::endl;


      return;
    }
    Insert(current, RIGHT);
    Insert(current, LEFT);
    Insert(current, UP);
    Insert(current, DOWN);
    auto children = current->children;

    int NewDistance = current->distance + 1;
    for(auto &child: children){
      /*
      std::cout << "current: " << child->distance << " new: " << NewDistance << std::endl;

      if(child in OpenList){
        if(OpenList[child] < NewDistance){
          continue;
        }
      }



      if(child in ClosedList){
        if(ClosedList[child] < NewDistance){
          continue;
        }
      }
      */

      if(NewDistance < child->distance){
        child->parent = current;
        child->distance = NewDistance;
        OpenQueue.push(child);
      }
    }
  }
  std::cout << "Closed queue size: " << ClosedQueue.size() << std::endl;
  std::cout << "Reached bottom of while loop, no solution found" << std::endl;
}




void Tree::Dijkstra(){
  std::cout << "-------Using dijkstra search -------" << std::endl;
  std::priority_queue<Node*,std::vector<Node*>,LessThanByDistance> OpenQueue;
  std::list<Node*> ClosedQueue;
  OpenQueue.push(root);
  root->distance = 0;
  while(!OpenQueue.empty()){
    auto current = OpenQueue.top();
    OpenQueue.pop();


    ClosedQueue.push_back(current);
    if(IsGoal(current)){
      std::cout << "Closed queue size: " << ClosedQueue.size() << std::endl;
      std::cout << "Reached goal" << std::endl;
      //exit(0);
      BackTrackSolution(current);
      std::cout << std::endl;
      std::cout << "Backtrack done" << std::endl;

      //assert(ClosedQueue.size() == 248064);

      return;
      // BackTrack(curent)
    }
    Insert(current, RIGHT);
    Insert(current, LEFT);
    Insert(current, UP);
    Insert(current, DOWN);
    auto children = current->children;

    int NewDistance = current->distance + 1;
    for(auto &child: children){
      /*
      std::cout << "current: " << child->distance << " new: " << NewDistance << std::endl;

      if(child in OpenList){
        if(OpenList[child] < NewDistance){
          continue;
        }
      }



      if(child in ClosedList){
        if(ClosedList[child] < NewDistance){
          continue;
        }
      }
      */

      if(NewDistance < child->distance){
        child->parent = current;
        child->distance = NewDistance;
        OpenQueue.push(child);
      }
    }
  }
  std::cout << "Closed queue size: " << ClosedQueue.size() << std::endl;
  std::cout << "Reached bottom of while loop, no solution found" << std::endl;
}


void Tree::BredthFirst(){
  std::cout << "-------Using breadthFirst search -------" << std::endl;
  std::queue<Node*> OpenQueue;
  std::list<Node*> ClosedQueue;
  OpenQueue.push(root);
  root->discovered = true;
  while(!OpenQueue.empty()){
    auto current = OpenQueue.front();
    OpenQueue.pop();


    if(IsGoal(current)){
      std::cout << "Closed queue size: " << ClosedQueue.size() << std::endl;
      std::cout << "Reached goal" << std::endl;
      BackTrackSolution(current);
      std::cout << std::endl;

      return;
      // BackTrack(curent)
    }
    ClosedQueue.push_back(current);

    Insert(current, RIGHT);
    Insert(current, LEFT);
    Insert(current, UP);
    Insert(current, DOWN);
    auto children = current->children;

    for(auto &child: children){
      if(!child->discovered){


        child->discovered = true;
        child->parent = current;
        OpenQueue.push(child);
      }
    }
  }

  std::cout << "Closed queue size: " << ClosedQueue.size() << std::endl;
  std::cout << "Reached bottom of while loop, no solution found" << std::endl;
}



void Tree::_ExploreMap(Node *node){
  if(node->discovered){
    return ;
  }

  node->discovered = true;

  if(counter_debug++ > 10000000)  {
      std::cout << FMAG("Too many recursive calls") << std::endl;
      return;
  }

  IsGoal(node);
  for(auto &child : node->children){
      // NOTE Insert four nodes
      Insert(child, UP);
      Insert(child, DOWN);
      Insert(child, LEFT);
      Insert(child, RIGHT);

      _ExploreMap(child);
  }
}
