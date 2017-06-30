#ifndef Node_h
#define Node_h

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Node {

	private:

		// Tools of the node
		vector<int> tools;

		// Corresponding job of the node
		int job;

		int id;

    public:

    	Node(vector<int> tools, int job, int id);

    	vector<int> getTools() { return tools; }; 

    	int getJob() { return job; };

    	int getId() { return id; };
};

#endif