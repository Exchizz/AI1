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
//	tree.Dijkstra();


	/* DOTgraph graph *//*
	graph.visualize(tree.root);
	graph.SaveGraph("graph.dot");
	*/

std::cout << "Hello world" << std::endl;
return 0;
}
