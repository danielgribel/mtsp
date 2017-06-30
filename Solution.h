#ifndef Solution_h
#define Solution_h

#include <math.h>
#include <limits>
#include "PbData.h"
#include "Edge.h"
#include "ShortestPath.h"
#include "Graph.h"

using namespace std;

const int MAX_INT = numeric_limits<int>::max();

class Solution {

	private:

		vector< vector<int> > assignedTools;

		vector<int> scheduling;

		int cost;

		PbData * pbData;

    public:

    	Solution();

    	Solution(vector< vector<int> > assignedTools, vector<int> scheduling, PbData * pbData);

    	vector< vector<int> > getAssignedTools();

    	vector<int> getAssignedTools(int i);

    	vector<int> getScheduling(); 

    	int getCost();

    	void computeCost();

    	vector<int> toolsDiff(int i, int j);

    	int switchCost(const vector<int> tools1, const vector<int> tools2);

    	vector<Node*> jobNodes(int j, int c, int &nodeId);

    	Graph * buildGraph(int col);

    	void localSearch();

    	void localSearch(int col);

    	void printCost();

    	void printAssignedTools();

    	void printScheduling();

    	int minDistance(vector<int> dist, vector<bool> sptSet, int V);

    	vector<int> getPath(vector<int> parent, int j, int src);

    	ShortestPath * dijkstra(Graph * graph, int src);
};

#endif