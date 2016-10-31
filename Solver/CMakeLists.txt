cmake_minimum_required (VERSION 2.8)
project (AI1-Solver)

ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    # Other flags
)

add_executable(parser src/point.cpp src/map.cpp src/tree.cpp src/node.cpp src/DOTgraph.cpp src/main.cpp)


