#include "Edge.h"

using namespace std;

Edge::Edge(Node * source, Node * target, int cost) {
	this->source = source;
	this->target = target;
	this->cost = cost;
}
