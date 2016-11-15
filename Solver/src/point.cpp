#include "point.hpp"
Point::Point(unsigned int xparam, unsigned int yparam){
    x = xparam;
    y = yparam;
}

std::ostream & operator<< (std::ostream &out, Point &t){
    out << " x,y (" << t.x << "," << t.y << ")";
    return out;
}

void Point::println(){
  std::cout << "x,y: " << x << "," << y << std::endl;
}

Point::Point(){}
