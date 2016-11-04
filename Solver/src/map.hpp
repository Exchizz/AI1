#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "point.hpp"
#include "colors.hpp"

#ifndef MAP_H
#define MAP_H
typedef char ** RawMap;

class Map {
        private:
                std::ifstream mapfile;
                RawMap map;
        public:
                int cols, rows, cans ;
                void LoadMap(std::string filename);
                void PrintMap();
                RawMap GetMap();
                std::vector<Point> Find(char);
                char operator[](Point);
                void SetMan(Point PosMan);
                Map* Clone();
                void AllocateMemory(int,int);
                Map& operator=(Map& other){
                  this->cols = other.cols;
                  this->rows = other.rows;
                  this->map = other.map;
                  this->cans = other.cans;
                }
                bool inMap(Point position);
};

#endif
