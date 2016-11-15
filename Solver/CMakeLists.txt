cmake_minimum_required (VERSION 2.8)
project (AI1-Solver)

ADD_DEFINITIONS(
    -Wno-error=unused-function  
    -Wno-error=unused-variable  
    -Ofast			
    -std=c++14 		
    -Wall 			
    -Wextra 		
    -Wshadow 		
    -Wpointer-arith 	
    -ffunction-sections 	
    -fdata-sections		
    -Wcast-qual		
    -Werror			
    -Wno-unused-variable 	
    -pedantic		
    -Wunused-variable	
    -g			
)

add_executable(parser src/point.cpp src/map.cpp src/tree.cpp src/node.cpp src/DOTgraph.cpp src/xxhash.cpp src/murmur3.cpp src/main.cpp)


