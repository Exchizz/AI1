#include "map.hpp"
#include "tree.hpp"
#include "DOTgraph.hpp"
#include "wavefront.hpp"

int main(){
	Map map;
	map.LoadMap("map.txt");
	map.PrintMap();

	auto jewels = map.Find('J');

	Wavefront wf1(map);
	wf1.generate_wavefront( Point(3,3) );
	wf1.LocalMap.PrintMap();


	//DOTgraph graph;
	//graph.visualize(tree.root);
	//graph.SaveGraph("graph.dot");


	//Map * NewMap = tree.ConstructMap();
	//NewMap->PrintMap();
std::cout << "Hello world" << std::endl;
return 0;
}
