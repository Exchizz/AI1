#include "map.hpp"
#include "tree.hpp"
#include "DOTgraph.hpp"

int main(){
	Map map;
	map.LoadMap("map.txt");
	map.PrintMap();

	map.FindDeadLocks();

	Tree tree;
	tree.GenerateTree(map);
	tree.BredthFirst();
  //tree.Dijkstra();
	//tree.AStar(&Tree::h1,tree); // Start Astar using h1 as heuristics


	/* DOTgraph graph *//*
	graph.visualize(tree.root);
	graph.SaveGraph("graph.dot");
	*/

std::cout << "Hello world" << std::endl;
return 0;
}
