#include "map.hpp"
#include "tree.hpp"
#include "DOTgraph.hpp"

int main(){
	Map map;
	map.LoadMap("map.txt");
	map.PrintMap();
	//map.Clean("MJ");
	//map.PrintMap();
	//exit(1);

	auto jewels = map.Find('J');

	// NOTE Test find
	/*
	for(auto j: jewels){
		j.println();
	}
	*/
  //auto man = map.Find('M');
	//man[0].println();
	// NOTE end test find
	Tree tree;
	auto ManPositions = tree.GenerateTree(map);
	DOTgraph graph;
	graph.visualize(tree.root);
	graph.SaveGraph("graph.dot");


	//Map * NewMap = tree.ConstructMap();
	//NewMap->PrintMap();
std::cout << "Hello world" << std::endl;
return 0;
}
