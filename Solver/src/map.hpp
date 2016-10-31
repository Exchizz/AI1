#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "point.hpp"

#ifndef MAP_H
#define MAP_H
typedef char ** RawMap;

class Map {
        private:
                std::ifstream mapfile;
                int cols, rows, cans ;
                RawMap map;
        public:
                void LoadMap(std::string filename);
                void PrintMap();
                RawMap GetMap();
                std::vector<Point> Find(char);
                char operator[](Point);
                Map& operator=(Map& other){
                  this->cols = other.cols;
                  this->rows = other.rows;
                  this->map = other.map;
                  this->cans = other.cans;
                }
};

#endif
