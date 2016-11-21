#include "map.hpp"
#include "tree.hpp"
#include "DOTgraph.hpp"
#include <chrono>
#include <thread>

int main(){

	auto start = std::chrono::steady_clock::now();

	Map map;
	map.LoadMap("map.txt");
	map.PrintMap();

	map.FindDeadLocks();

	Tree tree;
	tree.GenerateTree(map);
	tree.BredthFirst();
	//tree.Dijkstra();
	//tree.AStar(&Tree::h1,tree); // Start Astar using h1 as heuristics

	auto finish = std::chrono::steady_clock::now();
	double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double> >(finish - start).count();

	for(auto node : tree.SolutionList){
		std::cout << "\033[2J\033[1;1H"; // Clear terminal
		tree.SetState(node);
		tree.map.PrintMap();
		tree.map.Clean("MJG");
	  std::this_thread::sleep_for (std::chrono::milliseconds(150));
	}


	std::cout << "Time it took to solve map: " <<  floor(elapsed_seconds/60) << " min " << std::fmod(elapsed_seconds,60) << " secs" << std::endl;



	/* DOTgraph graph *//*
	graph.visualize(tree.root);
	graph.SaveGraph("graph.dot");
	*/

std::cout << "Hello world" << std::endl;
return 0;
}
