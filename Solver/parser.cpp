#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

int main(){
	std::ifstream mapfile;
	mapfile.open ("map.txt");
	int cols = 0, rows = 0, cans = 0;

	if (!mapfile.is_open()){
		std::cout << "file not found " << std::endl;
	}

	char c[4];
	mapfile.get(c,3);
	cols = ((int)c[0]-'0')*10 + (int)c[1]-'0';

	mapfile.get(c,4);
	rows = ((int)c[1]-'0')*10 + (int)c[2]-'0' ;


	mapfile.get(c,4);
	cans = ((int)c[1]-'0')*10 + (int)c[2]-'0';

	char ** map = new char*[cols];

	for(int i = 0; i < cols; i++){
		map[i] = new char[rows];
	}

	char b;
	mapfile.get(b);
	for(int y = 0; y < rows; y++ ){
		int newline = false;
		for(int x = 0; x< cols; x++){
			mapfile.get(b);
			map[x][y] = b;
		}
		mapfile.get(b);
	}
	mapfile.close();

	for(int y = 0; y < rows; y++ ){
		for(int x = 0; x < cols; x++){
			std::cout <<  " " << map[x][y] << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}
