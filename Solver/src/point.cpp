#include "point.hpp"
Point::Point(unsigned int x, unsigned int y){
    this->x = x;
    this->y = y;
}


void Point::println(){
  std::cout << "x,y: " << x << "," << y << std::endl;
}

Point::Point(){}
