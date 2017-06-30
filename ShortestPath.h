#ifndef ShortestPath_h
#define ShortestPath_h

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class ShortestPath {

	private:

		vector<int> path;

		int cost;

    public:

    	ShortestPath(vector<int> path, int cost);

		vector<int> getPath() { return path; };

		int getCost() { return cost; };    	
};

#endif