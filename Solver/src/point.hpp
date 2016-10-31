#include <iostream>
#ifndef POINT_H
#define POINT_H
class Point {
public:
  Point(unsigned int x, unsigned int y);
  Point Up(){
    return Point( x, y - 1);
  }
  Point Down(){
    return Point( x, y + 1);
  }
  Point Left(){
    return Point( x -1,  y);
  }
  Point Right(){
    return Point( x + 1, y);
  }
  Point();
  void println();
  unsigned int x;
  unsigned int y;
};
std::ostream & operator<< (std::ostream &out, Point  &t);

#endif
