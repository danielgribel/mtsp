#ifndef Solution_h
#define Solution_h

#include <algorithm>
#include <math.h>
#include <limits>
#include "PbData.h"
#include "Node.h"
#include "Edge.h"

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

    	vector<Node*> jobNodes(int j, int c);

    	void printCost();

    	void printAssignedTools();

    	void printScheduling();
};

#endif