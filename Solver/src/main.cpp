#include "map.hpp"
#include "tree.hpp"
#include "DOTgraph.hpp"
#include <chrono>

int main(){

	auto start = std::chrono::steady_clock::now();

	Map map;
	map.LoadMap("map.txt");
	map.PrintMap();

	map.FindDeadLocks();

	Tree tree;
	tree.GenerateTree(map);
	tree.BredthFirst();

	auto finish = std::chrono::steady_clock::now();
	double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double> >(finish - start).count();


	std::cout << "Time it took to solve map: " <<  floor(elapsed_seconds/60) << " min " << std::fmod(elapsed_seconds,60) << " secs" << std::endl;
  //tree.Dijkstra();
	//tree.AStar(&Tree::h1,tree); // Start Astar using h1 as heuristics


	/* DOTgraph graph *//*
	graph.visualize(tree.root);
	graph.SaveGraph("graph.dot");
	*/

std::cout << "Hello world" << std::endl;
return 0;
}
