#include "point.hpp"
#include "map.hpp"
#include <vector>
#ifndef NODE_H
#define NODE_H

class Node {
public:
  Node(Point, std::vector<Point>&);
  std::vector<Node*> children;

  void Insert(Map &,Point, std::vector<Point> &);
  Point PosMan;
  std::vector<Point> PosJew;
  bool discovered = false;
  bool vizDotVisit = false;

  bool operator==(const Node & rhs) const {
    std::cerr << "Hit collision " << std::endl;
    bool retval = true;
    for(int i = 0; i < PosJew.size(); i++){
      retval = retval && (PosJew[i] == rhs.PosJew[i]);
    }

    return (PosMan == rhs.PosMan) && retval;
  }
};


namespace std {
  template <>
  struct hash<Node>
  {
    std::size_t operator()(const Node& k) const
    {
      using std::size_t;
      using std::hash;
      //using std::string;

      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:
      //std::cout << "hashing " << ((hash<int>()(k.PosMan.x) ^ (hash<int>()(k.PosMan.y) << 1)) >> 1) << std::endl;
      // Method 1
      int hashz = 0;
      for (size_t i = 0; i < k.PosJew.size(); i++) {
        hashz ^= ( (hash<int>()(k.PosJew[i].x)) ^ (hash<int>()(k.PosJew[i].y) << 1) >> 1 );
      }
      hashz ^= hash<int>()(k.PosMan.x) ^ hash<int>()(k.PosMan.y);
      return hashz;
    }
  };

}

#endif
