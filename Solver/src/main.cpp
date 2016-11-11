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

	std::cout << "node1: " << tree.root->PosMan << " jew: " << tree.root->PosJew[0] << std::endl;

	std::cout << "node2: " << tree.root->children[0]->PosMan << " jew: " << tree.root->children[0]->PosJew[0] << std::endl;
	DOTgraph graph;
	graph.visualize(tree.root);
	graph.SaveGraph("graph.dot");


	//Map * NewMap = tree.ConstructMap();
	//NewMap->PrintMap();
std::cout << "Hello world" << std::endl;
return 0;
}
