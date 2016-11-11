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

std::string ConcatenatePosAndJew(Node *node){
	std::string xy = std::to_string(node->PosMan.x) + std::to_string(node->PosMan.y);

	for(auto elm: node->PosJew){
		xy+= std::to_string(elm.x) + std::to_string(elm.y);
	}
	return xy;
}
void DOTgraph::SaveGraph(std::string filename){
	ofstream myfile;
	myfile.open (filename.c_str());
	myfile << "digraph G {" << std::endl;

	// Generate nodes
	for(auto node : uniq_nodes){
		auto name = ConcatenatePosAndJew(node);
		myfile <<  name << " [label=<<TABLE BORDER=\"0\" CELLBORDER=\"0\" CELLSPACING=\"0\"><TR><TD>" << node->PosMan << "</TD></TR>";
		for(auto jew : node->PosJew){
			myfile << "<TR><TD>" <<jew << "</TD></TR>";
		}
		myfile << "</TABLE>>" << ", shape=\"box\"]" << std::endl;
	}
	// Assign edges between nodes
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

std::string name(Node* node){
	std::string str = ConcatenatePosAndJew(node);
	return str;
}

std::string DOTgraph::visualize(Node *node){
	if(!node->vizDotVisit){
		node->vizDotVisit = true;
		uniq_nodes.push_back(node);
		auto textParent = name(node);
		for(auto &child : node->children){
		    auto text = visualize(child);
		    addEdge(textParent,text);
		}
	}

	return name(node);
}
