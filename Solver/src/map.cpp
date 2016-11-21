#include "map.hpp"


void Map::Clean(std::string ToRemove){
	for(unsigned int x = 0; x < cols; x++){
		for(unsigned int y = 0; y < rows; y++){
			for(unsigned int i = 0; i < ToRemove.length(); i++){
		    if(ToRemove[i] == map[x][y]){
						map[x][y] = '.';
				}
			}
		}
	}
}


int Map::FindDeadLocks(){
	std::vector<std::pair<Point, int>> deadlocks_list;
	for(unsigned int x = 1; x < cols-1; x++){
		for(unsigned int y = 1; y < rows-1; y++){
			// if the position is a wall, we can't put a jew here anyway..
			if(map[x][y] == 'X' or map[x][y] == 'G') continue;
			// Up left
			if(map[x][y-1] == 'X' and map[x-1][y] == 'X'){
				deadlocks.insert({ hashPos(Point(x, y)),1});
				deadlocks_list.push_back( std::make_pair(Point(x,y),0) );
				std::cout << "deadlock position(): " << "x: " << x << " y: " << y << std::endl;
			}
			// Up right
			if(map[x][y-1] == 'X' and map[x+1][y] == 'X'){
				deadlocks.insert({ hashPos(Point(x, y)),1});
				deadlocks_list.push_back( std::make_pair(Point(x,y),0) );
				std::cout << "deadlock position(): " << "x: " << x << " y: " << y << std::endl;
			}
			// Down right
			if(map[x][y+1] == 'X' and map[x+1][y] == 'X'){
				deadlocks.insert({ hashPos(Point(x, y)),1});
				deadlocks_list.push_back( std::make_pair(Point(x,y),0) );
				std::cout << "deadlock position(): " << "x: " << x << " y: " << y << std::endl;
			}
			// Down left
			if(map[x][y+1] == 'X' and map[x-1][y] == 'X'){
				deadlocks.insert({ hashPos(Point(x, y)),1});
				deadlocks_list.push_back( std::make_pair(Point(x,y),0) );
				std::cout << "deadlock position(): " << "x: " << x << " y: " << y << std::endl;
			}
		}
	}

	for(auto &deadlock1 : deadlocks_list){
		for(auto &deadlock2 : deadlocks_list){
			if (deadlock1 == deadlock2) {
				//std::cout << "skipping, same deadlock found" << std::endl;
				continue;
			}

			// check for horizontal lines
			if(deadlock1.first.y == deadlock2.first.y && !deadlock1.second && !deadlock2.second){
				deadlock1.second = 1;
				deadlock2.second = 1;
				bool valid_deadlock = true;
				for(unsigned int x = std::min(deadlock1.first.x, deadlock2.first.x); x <= std::max(deadlock1.first.x, deadlock2.first.x); x++){
					if( map[x][deadlock1.first.y] == 'G' or map[x][deadlock1.first.y] == 'M' ){
						valid_deadlock = false;
					}
					valid_deadlock = valid_deadlock && (map[x][deadlock1.first.y-1] == 'X' or map[x][deadlock1.first.y+1] == 'X');
				}

				if(valid_deadlock){
					for(unsigned int x = std::min(deadlock1.first.x, deadlock2.first.x); x <= std::max(deadlock1.first.x, deadlock2.first.x); x++){
							std::cout << "deadlock position: " << "x: " << x << " y: " << deadlock2.first.y << std::endl;
							deadlocks.insert({ hashPos(Point(x, deadlock1.first.y)),1});
					}
				}
			}
		}
	}
	// Reset "visisted" variables on each deadlock.
	for(auto &deadlock1 : deadlocks_list)
		deadlock1.second = 0;
	for(auto &deadlock2 : deadlocks_list)
		deadlock2.second = 0;



  std::cout << "deadlocks vertical" << std::endl;
	for(auto &deadlock1 : deadlocks_list){
		for(auto &deadlock2 : deadlocks_list){

				if (deadlock1 == deadlock2) {
				//std::cout << "skipping, same deadlock found" << std::endl;
					continue;
				}
				// check for vertical lines
				if(deadlock1.first.x == deadlock2.first.x && !deadlock1.second && !deadlock2.second){
					deadlock1.second = 1;
					deadlock2.second = 1;
					bool valid_deadlock = true;
					for(unsigned int y = std::min(deadlock1.first.y, deadlock2.first.y); y <= std::max(deadlock1.first.y, deadlock2.first.y); y++){
						if( map[deadlock1.first.x][y] == 'G' or map[deadlock1.first.x][y] == 'M' ){
							valid_deadlock = false;
						}
						valid_deadlock = valid_deadlock && (map[deadlock1.first.x-1][y] == 'X' or map[deadlock1.first.x +1 ][y] == 'X');
					}

					if(valid_deadlock){
						for(unsigned int y = std::min(deadlock1.first.y, deadlock2.first.y); y <= std::max(deadlock1.first.y, deadlock2.first.y); y++){
								std::cout << "deadlock position: " << "x: " << deadlock1.first.x << " y: " << y << std::endl;
								deadlocks.insert({ hashPos(Point(deadlock1.first.x, y)),1});
						}
					}
				}
			}
		}
		std::cout << "deadlocks: " << deadlocks.size() << std::endl;
return 0;
}

std::vector<Point> Map::Find(char needle){
	std::vector<Point> results;
	for (unsigned int x = 0; x < cols; x++){
		for(unsigned int y = 0; y < rows; y++){
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

	std::cout << "cols: " << cols << " rows: " << rows << std::endl;

	mapfile.get(c,4);
	cans = ((int)c[1]-'0')*10 + (int)c[2]-'0';

	AllocateMemory(cols, rows);

	char b;
	mapfile.get(b);
	// Read file to memory
	for(unsigned int y = 0; y < rows; y++ ){
		for(unsigned int x = 0; x< cols; x++){
			mapfile.get(b);
			map[x][y] = b;
		}
		mapfile.get(b);
	}
	mapfile.close();

}

void Map::AllocateMemory(int rows_p, int cols_p){
	// Initialize map
	map = new char*[ rows_p ];
	for(int i = 0; i < rows_p ; i++){
		map[i] = new char[cols_p];
	}

}

bool Map::inMap(Point position){
	if(position.x > cols -1 || position.y > rows -1){
		std::cerr << "Out of range" << position << std::endl;
		return false;
	}

	return true;
}

void Map::PrintMap(){
	std::cout << "   ";
	for(unsigned int x = 0; x < cols; x++){
		std::cout << x << "  ";
	}
	std::cout << std::endl;

	for(unsigned int y = 0; y < rows; y++ ){
		std::cout << y << " ";
		for(unsigned int x = 0; x < cols; x++){
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
	for(unsigned int y = 0; y < rows; y++ ){
		for(unsigned int x = 0; x < cols; x++){
			map_clone->map[x][y] = map[x][y];
		}
	}
	return map_clone;
}

bool Map::IsPosJew(std::vector<Point> & Jews, Point pos){
	for(auto elm : Jews){
		if(elm == pos){
			return true;
		}
	}
	return false;
}

bool Map::IsPosWall(Point pos){
	return (map[pos.x][pos.y] == 'X');
}

bool Map::IsPosFree(Point pos, std::vector<Point> &Jews){
	return(!IsPosJew(Jews, pos) && !IsPosWall(pos));
}


bool Map::MoveJew(std::vector<Point> &Jews, Point CurrentJewPos, Point NewJewPos){

	// NewJeWPos is in deadlock-list, don't move it
	auto search = deadlocks.find(hashPos(NewJewPos));
	if(search != deadlocks.end()) {
			return false;
	}
	// Find the node we want to move
	for(auto & jew: Jews){
		if(jew == CurrentJewPos){
				jew = NewJewPos;
			}
	}
	return true;
}


bool Map::DynamicDeadlock(Point PosJew, int action, std::vector<Point> & jews){
	switch(action){
		case RIGHT:
			if(map[PosJew.x+2][PosJew.y] == 'X' || IsPosJew(jews, Point(PosJew.x+2, PosJew.y)) ){ // Check outer right
				if(map[PosJew.x+1][PosJew.y+1] == 'X' ){//||  IsPosJew(jews, Point(PosJew.x+1, PosJew.y +1 )) ){ // Check lower
					if(map[PosJew.x+1][PosJew.y-1] == 'X' ){//||  IsPosJew(jews, Point(PosJew.x+1, PosJew.y-1)) ){ // Check upper
						//std::cout << "Dynamic deadlock found right" << std::endl;
						return true;
					}
				}
			}
		break;

		case LEFT:
			if(map[PosJew.x-2][PosJew.y] == 'X' || IsPosJew(jews, Point(PosJew.x-2, PosJew.y))){ // Check outer right
				if(map[PosJew.x-1][PosJew.y+1] == 'X'){ // || IsPosJew(jews, Point(PosJew.x-1, PosJew.y+1)) ){ // Check upper
					if(map[PosJew.x-1][PosJew.y-1] == 'X'){ // || IsPosJew(jews, Point(PosJew.x-1, PosJew.y-1))){ // Check lower
						//std::cout << "Dynamic deadlock found left" << std::endl;
						return true;
					}
				}
			}
		break;


		case UP:
			if(map[PosJew.x][PosJew.y-2] == 'X' ||  IsPosJew(jews, Point(PosJew.x, PosJew.y-2))){ // Check upper
				if(map[PosJew.x-1][PosJew.y-1] == 'X' ){ //|| IsPosJew(jews, Point(PosJew.x-1, PosJew.y-1))){ // Check left
					if(map[PosJew.x+1][PosJew.y-1] == 'X' ){ //|| IsPosJew(jews, Point(PosJew.x+1, PosJew.y-1))){ // Check right
						//std::cout << "Dynamic deadlock found up" << std::endl;
						return true;
					}
				}
			}
		break;


		case DOWN:
			if(map[PosJew.x][PosJew.y+2] == 'X' || IsPosJew(jews, Point(PosJew.x, PosJew.y+2))){ // Check upper
				if(map[PosJew.x-1][PosJew.y+1] == 'X' ){ //|| IsPosJew(jews, Point(PosJew.x-1, PosJew.y+1))){ // Check left
					if(map[PosJew.x+1][PosJew.y+1] == 'X' ){ //|| IsPosJew(jews, Point(PosJew.x+1, PosJew.y+1))){ // Check right
						//std::cout << "Dynamic deadlock found down" << std::endl;
						return true;
					}
				}
			}
		break;

	}

	return false;
}

bool Map::TryToMove(Point pos, std::vector<Point> & Jews, int action){
	if(IsPosJew(Jews, pos)){
		switch(action){
			case UP:
				if(map[pos.x][pos.y-1] == '.' && !IsPosJew(Jews, Point(pos.x, pos.y-1)) && !DynamicDeadlock(pos, action, Jews)){
					auto NewJewPos = Point(pos.x, pos.y-1);
					auto CurrentJewPos = Point(pos.x, pos.y);
					return MoveJew(Jews, CurrentJewPos, NewJewPos);
				} else {
					return false;
				}
			break;
			case DOWN:
				if(map[pos.x][pos.y+1] == '.' && !IsPosJew(Jews, Point(pos.x, pos.y+1)) && !DynamicDeadlock(pos, action, Jews)){
					auto NewJewPos = Point(pos.x, pos.y+1);
					auto CurrentJewPos = Point(pos.x, pos.y);
					return MoveJew(Jews, CurrentJewPos, NewJewPos);
				} else {
					return false;
				}
			break;

			case LEFT:
				if(map[pos.x -1][pos.y] == '.'&& !IsPosJew(Jews, Point(pos.x-1, pos.y)) && !DynamicDeadlock(pos, action, Jews)){
					auto NewJewPos = Point(pos.x - 1, pos.y);
					auto CurrentJewPos = Point(pos.x, pos.y);
					return MoveJew(Jews, CurrentJewPos, NewJewPos);
				} else {
					return false;
				}
				return true;
			break;
			case RIGHT:
				if(map[pos.x+1][pos.y] == '.' && !IsPosJew(Jews, Point(pos.x+1, pos.y)) && !DynamicDeadlock(pos, action, Jews)){
					auto NewJewPos = Point(pos.x+1, pos.y);
					auto CurrentJewPos = Point(pos.x, pos.y);
					return MoveJew(Jews, CurrentJewPos, NewJewPos);
				} else {
					return false;
				}
			break;
			default:
				std::cout << "ERROR: Action not defined, TryToMove" << std::endl;
		}
	}
	return false;
}
