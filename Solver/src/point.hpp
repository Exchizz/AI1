#include <iostream>
#ifndef POINT_H
#define POINT_H
class Point {
public:
  Point(unsigned int x, unsigned int y);
  Point Up(Point pos){
    return Point( pos.x, pos.y - 1);
  }
  Point Down(Point pos){
    return Point( pos.x, pos.y + 1);
  }
  Point Left(Point pos){
    return Point( pos.x -1, pos.y);
  }
  Point Right(Point pos){
    return Point( pos.x + 1, pos.y);
  }
  Point();
  void println();
  unsigned int x;
  unsigned int y;
};

#endif
