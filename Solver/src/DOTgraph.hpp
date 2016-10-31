/*
 * DOTgraph.h
 *
 *  Created on: Dec 17, 2015
 *      Author: exchizz
 */

#ifndef DOTGRAPH_H_
#define DOTGRAPH_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "point.hpp"
#include "node.hpp"
using namespace std;

class DOTgraph {
private:
	std::vector<std::pair<std::string, std::string> > edges;
public:
	DOTgraph();
	virtual ~DOTgraph();
	void SaveGraph(std::string);
	void addEdge(std::string, std::string);

	std::string visualize(Node);
};

#endif /* DOTGRAPH_H_ */
