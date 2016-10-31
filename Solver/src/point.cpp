#include "point.hpp"
Point::Point(unsigned int x, unsigned int y){
    this->x = x;
    this->y = y;
}

std::ostream & operator<< (std::ostream &out, Point &t){
    out << " x,y (" << t.x << "," << t.y << ")";
    return out;
}

void Point::println(){
  std::cout << "x,y: " << x << "," << y << std::endl;
}

Point::Point(){}
