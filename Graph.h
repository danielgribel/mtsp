#ifndef Graph_h
#define Graph_h

#include <iostream>
#include <vector>
#include <algorithm>
#include "Node.h"

using namespace std;

class Graph {

	private:

		vector< vector<int> > graph;
		
		vector<Node*> idNodes;

		vector<int> sourceNodes;

		vector<int> targetNodes;

		int nbNodes;

    public:

    	Graph(vector< vector<int> > graph, vector<Node*> idNodes, vector<int> sourceNodes, vector<int> targetNodes, int nbNodes);

    	Graph();

		vector< vector<int> > getGraph() { return graph; };
		
		vector<Node*> getIdNodes() { return idNodes; };

		vector<int> getSourceNodes() { return sourceNodes; };

		vector<int> getTargetNodes() { return targetNodes; };

		int getNbNodes() { return nbNodes; };
};

#endif