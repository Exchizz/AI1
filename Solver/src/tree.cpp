#include "tree.hpp"

void Tree::GenerateTree(Map &map){
  // NOTE find only returns one element since there is only one man in the map.
  Point PosMan = map.Find('M')[0];
  auto PosJew = map.Find('J');

  Node * root = new Node(PosMan,PosJew);

  // NOTE Insert four nodes
  root.Insert( PosMan.Up(), PosJew );
  root.Insert( PosMan.Down(), PosJew );
  root.Insert( PosMan.Left(), PosJew );
  root.Insert( PosMan.Right(), PosJew );

  // NOTE recursive generte the tree
  RecursiveSomething(root);

}


void Tree::Insert(PosMan, PosJew){
  if (Map[PosMan] == 'X'){
      return nullptr;
  } else {
    Node * root = new Node(PosMan,PosJew);
    return root;
  }
}
