#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "point.hpp"
#include "colors.hpp"

#define UP 1
#define LEFT 2
#define RIGHT 3
#define DOWN 4

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
                bool TryToMove(Point pos, std::vector<Point> & Jews, int action);
                void Clean(std::string ToRemove);
                bool IsPosJew(std::vector<Point> & Jews, Point pos);
                bool IsPosWall(Point pos);
                bool IsPosFree(Point pos, std::vector<Point> &Jews);
};

#endif
