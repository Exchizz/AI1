#include "map.hpp"

std::vector<Point> Map::Find(char needle){
	std::vector<Point> results;
	for (int x = 0; x < cols; x++){
		for(int y = 0; y < rows; y++){
			//If needle is in haystack
			if(needle == map[x][y]){
				results.push_back( Point(x,y) );
			}
		}
	}
	return results;
}
char Map::operator[](Point man){
	return map[man.x][man.y];
}


void Map::SetMan(Point PosMan){
	auto OldPose = Find('M')[0];
	map[OldPose.x][OldPose.y] = '.';
	map[PosMan.x][PosMan.y] = 'M';
}

void Map::LoadMap(std::string filename){
	mapfile.open (filename.c_str());

	if (!mapfile.is_open()){
		std::cout << "file not found " << std::endl;
		return ;
	}

	char c[4];
	mapfile.get(c,3);
	cols = ((int)c[0]-'0')*10 + (int)c[1]-'0';

	mapfile.get(c,4);
	rows = ((int)c[1]-'0')*10 + (int)c[2]-'0' ;


	mapfile.get(c,4);
	cans = ((int)c[1]-'0')*10 + (int)c[2]-'0';

	// Initialize map
	/*map = new char*[cols];
	for(int i = 0; i < cols; i++){
		map[i] = new char[rows];
	}
	*/
	AllocateMemory(cols, rows);

	char b;
	mapfile.get(b);
	// Read file to memory
	for(int y = 0; y < rows; y++ ){
		int newline = false;
		for(int x = 0; x< cols; x++){
			mapfile.get(b);
			map[x][y] = b;
		}
		mapfile.get(b);
	}
	mapfile.close();
}

void Map::AllocateMemory(int rows, int cols){
	// Initialize map
	map = new char*[cols];
	for(int i = 0; i < cols; i++){
		map[i] = new char[rows];
	}
}


void Map::PrintMap(){
	for(int y = 0; y < rows; y++ ){
		for(int x = 0; x < cols; x++){
			switch(map[x][y]){
				case 'M':
					std::cout <<  " " << KYEL << map[x][y] << RST << " ";
				break;
				case 'J':
					std::cout <<  " " << KGRN << map[x][y] << RST << " ";
				break;
				case 'G':
					std::cout << " " << KBLU << map[x][y] << RST << " ";
				break;
				default:
					std::cout <<  " " << map[x][y] << " ";
				break;
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

RawMap Map::GetMap(){
	return map;
}

Map* Map::Clone(){
	Map * map_clone = new Map();
	map_clone->cols = cols;
	map_clone->rows = rows;
	map_clone->cans = cans;
	map_clone->AllocateMemory(rows, cols);
	for(int y = 0; y < rows; y++ ){
		for(int x = 0; x < cols; x++){
			map_clone->map[x][y] = map[x][y];
		}
	}
	return map_clone;
}
