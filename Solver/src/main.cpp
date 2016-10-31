#include "map.hpp"
#include "tree.hpp"

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

return 0;
}
