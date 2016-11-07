/*
 * DOTgraph.cpp
 *
 *  Created on: Dec 17, 2015
 *      Author: exchizz
 */

#include "DOTgraph.hpp"

/*
 * USAGE:
 * dot -Tps testdot.dot -o graph1.ps
 * open using:
 * gimp graph1.ps
 */

DOTgraph::DOTgraph() {

}

DOTgraph::~DOTgraph() {
	// TODO Auto-generated destructor stub
}

void DOTgraph::SaveGraph(std::string filename){
	ofstream myfile;
	myfile.open (filename.c_str());
	myfile << "digraph G {" << std::endl;
	for(unsigned int i = 0; i < edges.size(); ++i){
		myfile << edges[i].first << " -> " <<  edges[i].second << std::endl;
	}
	myfile << "}" << std::endl;
	myfile.close();
}
void DOTgraph::addEdge(std::string string1, std::string string2){
	auto elm = std::make_pair(string1, string2);
	edges.push_back(elm);

}

std::string name(Point point){
	std::stringstream ss;
	ss  << point.x << "." << point.y;
	std::string str = ss.str();
	return str;
}


std::string DOTgraph::visualize(Node *node){
	if(!node->vizDotVisit){
		node->vizDotVisit = true;
		for(auto &child : node->children){
		    auto textParent = name(node->PosMan);
		    auto text = visualize(child);
		    addEdge(textParent,text);
		}
	}

	return name(node->PosMan);
}
