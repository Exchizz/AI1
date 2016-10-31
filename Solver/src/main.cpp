#include "map.hpp"
#include "tree.hpp"
#include "DOTgraph.hpp"

int main(){
	Map map;
	map.LoadMap("map.txt");
	map.PrintMap();

	auto jewels = map.Find('J');

	// NOTE Test find
	for(auto j: jewels){
		j.println();
	}
  auto man = map.Find('M');
	man[0].println();
	// NOTE end test find

	Tree tree;
	tree.GenerateTree(map);
	std::cout << tree.Nodes() << std::endl;

	DOTgraph graph;
	graph.visualize(*tree.root);
	graph.SaveGraph("graph.dot");

return 0;
}
