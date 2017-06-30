#include "Graph.h"

using namespace std;

Graph::Graph(vector< vector<int> > graph, vector<Node*> idNodes, vector<int> sourceNodes, vector<int> targetNodes, int nbNodes) {
	this->graph = graph;
	this->idNodes = idNodes;
	this->sourceNodes = sourceNodes;
	this->targetNodes = targetNodes;
	this->nbNodes = nbNodes;
}

Graph::Graph() {

}