#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "point.hpp"
#include "colors.hpp"
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include "node.hpp"


#define UP 0
#define LEFT 1
#define RIGHT 2
#define DOWN 3

#ifndef MAP_H
#define MAP_H
typedef char ** RawMap;

class Map {
        private:
                std::ifstream mapfile;
                RawMap map;
        public:
                unsigned int cols, rows, cans ;
                void LoadMap(std::string filename);
                void PrintMap();
                RawMap GetMap();
                std::vector<Point> Find(char);
                char operator[](Point);
                void SetJew(Point Pos);
                void SetMan(Point PosMan);
                void SetGoal(Point pos);
                void SetJewOnGoal(Point pos);
                std::unordered_map<std::string, int> deadlocks;

                Map* Clone();
                void AllocateMemory(int,int);
                void operator=(Map& other){
                  this->cols = other.cols;
                  this->rows = other.rows;
                  this->map = other.map;
                  this->cans = other.cans;
                  this->deadlocks = other.deadlocks;
                }
                bool inMap(Point position);
                bool TryToMove(Point pos, std::vector<Point> & Jews, int action);
                void Clean(std::string ToRemove);
                bool IsPosJew(std::vector<Point> & Jews, Point pos);
                bool IsPosWall(Point pos);
                bool IsPosFree(Point pos, std::vector<Point> &Jews);
                bool MoveJew(std::vector<Point> &Jews, Point CurrentJewPos, Point NewJewPos);
                int  FindDeadLocks();
                bool DynamicDeadlock(Point PosJewm, int action, std::vector<Point> & jews);

                std::string hashPos(Point pos){
                  std::stringstream xy;
                  xy << pos.x << pos.y;
                  return xy.str();
                }

};

#endif
