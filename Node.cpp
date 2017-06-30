#include "Node.h"

using namespace std;

Node::Node(vector<int> tools, int job, int id) {
	this->tools = tools;
	this->job = job;
	this->id = id;
}