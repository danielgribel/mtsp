#ifndef Edge_h
#define Edge_h

#include "Node.h"

using namespace std;

class Edge {

	private:

		// Source node
		Node * source;

		// Target node
		Node * target;

		// Edge cost (weigth)
		int cost;

    public:

    	Edge(Node * source, Node * target, int cost);

    	Node * getSource() { return source; } ;

    	Node * getTarget() { return target; } ;

    	int getCost() { return cost; };
};

#endif