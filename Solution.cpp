#include "Solution.h"

using namespace std;

Solution::Solution() {
	
}

Solution::Solution(vector< vector<int> > assignedTools, vector<int> scheduling, PbData * pbData) {
	this->assignedTools = assignedTools;
	this->scheduling = scheduling;
	this->pbData = pbData;
	computeCost();
}

vector< vector<int> > Solution::getAssignedTools() {
	return this->assignedTools;
}

vector<int> Solution::getAssignedTools(int i) {
	return this->assignedTools[i];
}

vector<int> Solution::getScheduling() {
	return this->scheduling;
}

int Solution::getCost() {
	return this->cost;
}

void Solution::computeCost() {
	vector<int> diff;
	cost = 0;
	for(int i = 0; i < pbData->N() - 1; i++) {
		diff = toolsDiff(scheduling[i], scheduling[i+1]);
		cost = cost + diff.size();
	}
}

vector<int> Solution::toolsDiff(int i, int j) {
    set<int> setI( assignedTools[i].begin(), assignedTools[i].end() );
    set<int> setJ( assignedTools[j].begin(), assignedTools[j].end() );
    vector<int> result;

    set_difference( setI.begin(), setI.end(), setJ.begin(), setJ.end(),
        back_inserter( result ) );

    return result;
}

int Solution::switchCost(const vector<int> tools1, const vector<int> tools2) {
    set<int> stools1( tools1.begin(), tools1.end() );
    set<int> stools2( tools2.begin(), tools2.end() );
    vector<int> result;

    set_difference( stools1.begin(), stools1.end(), stools2.begin(), stools2.end(),
        back_inserter( result ) );

    return result.size();
}

// Get job nodes considering job j and column c of assigned tools
vector<Node*> Solution::jobNodes(int j, int c, int &nodeId) {
	vector<int> optionalTools = pbData->getOptionalTools(j);
	vector<int> baseTools (assignedTools[j].size() - 1);
	vector<bool> prohibited (pbData->M(), false); 
	vector<Node*> nodes;

	int q = 0;
	for(int i = 0; i < assignedTools[j].size(); i++) {
		if(i != c) {
			baseTools[q] = assignedTools[j][i];
			prohibited[assignedTools[j][i]] = true;
			q++;	
		}
	}

	if(pbData->isToolRequired(j, assignedTools[j][c])) {
		Node * node = new Node(assignedTools[j], j, nodeId);
		nodes.push_back(node);
		nodeId++;
	} else {
		for(int i = 0; i < optionalTools.size(); i++) {
			if(!prohibited[optionalTools[i]]) {
				vector<int> nd = baseTools;
				nd.push_back(optionalTools[i]);
				Node * node = new Node(nd, j, nodeId);
				nodes.push_back(node);
				nodeId++;
			}
		}
	}

	return nodes;
}

Graph * Solution::buildGraph(int col) {
	vector< vector<Node*> > nodes (pbData->N());
	// vector<Node*> idNodes ((pbData->M() - pbData->C() - 1)*pbData->N());
	vector<Node*> idNodes;
	int nodeId = 0;

	for(int j = 0; j < pbData->N(); j++) {
		nodes[j] = jobNodes(j, col, nodeId);
		
		// cout << nodes[j].size() << endl;

		// cout << "Job " << j << ": " << endl;
		for(int i = 0; i < nodes[j].size(); i++) {
			idNodes.push_back(nodes[j][i]);
			// idNodes[nodes[j][i]->getId()] = nodes[j][i];
			// cout << idNodes.size() - 1 << ": " << endl;
			// for(int k = 0; k < pbData->C(); k++) {
			// 	cout << nodes[j][i]->getTools()[k] <<  " ";
			// }
			// cout << endl;
		}
		// cout << "\n---------------" << endl;
	}

	// for(int i = 0; i < idNodes.size(); i++) {
	// 	for(int j = 0; j < idNodes[i]->getTools().size(); j++) {
	// 		cout << idNodes[i]->getTools()[j] << " ";
	// 	} cout << endl;
	// }

	int edgeCost;
	int totalNodes = idNodes.size();
	// cout << totalNodes << endl;

	// cout << "totalNodes: " << totalNodes << endl;
	vector< vector<int> > graph (totalNodes, vector<int> (totalNodes));

	for(int i = 0; i < totalNodes; i++) {
		for(int j = i; j < totalNodes; j++) {
			graph[i][j] = 99;
			graph[j][i] = 99;
		}
	}

	int j;
	for(int j0 = 0; j0 < pbData->N() - 1; j0++) {
		j = scheduling[j0];
		for(int j1 = 0; j1 < nodes[j].size(); j1++) {
			Node * node1 = nodes[j][j1];
			for(int j2 = 0; j2 < nodes[scheduling[j0+1]].size(); j2++) {
				Node * node2 = nodes[scheduling[j0+1]][j2];
				edgeCost = switchCost(node1->getTools(), node2->getTools());
				graph[node1->getId()][node2->getId()] = edgeCost;
				graph[node2->getId()][node1->getId()] = edgeCost;
			}
		}
	}

	// for(int i = 0; i < graph[0].size(); i++) {
	// 	for(int j = 0; j < graph[0].size(); j++) {
	// 		cout << graph[i][j] << " ";
	// 	} cout << "\n--------------" << endl;
	// }
	// printScheduling();
	// cout << "\n--------------" << endl;
	// printAssignedTools();

	vector<int> sourceNodes;
    vector<int> targetNodes;

	int S = scheduling[0];
	int T = scheduling[pbData->N() - 1];

	for(int i = 0; i < nodes[S].size(); i++) {
		sourceNodes.push_back(nodes[S][i]->getId());
	}

	for(int i = 0; i < nodes[T].size(); i++) {
		targetNodes.push_back(nodes[T][i]->getId());
	}

	Graph * G = new Graph(graph, idNodes, sourceNodes, targetNodes, totalNodes);

	return G;
}

void Solution::localSearch() {
	int col = pbData->C()-1;

	// localSearch(col);

	for(int c = col; c > 0; c--) {
		localSearch(c);
	}
	
	// Graph * graph = buildGraph(col);
	// ShortestPath * path = dijkstra(graph, 7);
}

vector<int> shuffleN(size_t n) {
    vector<int> myArray(n);
    for(int i = 0; i < n; i++) {
        myArray[i] = i;
    }
    if(n > 1) {
        size_t i;
        for (int i = 0; i < n - 1; i++) {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = myArray[j];
            myArray[j] = myArray[i];
            myArray[i] = t;
        }
    }
    return myArray;
}

vector<int> shuffleV(vector<int> vec) {
	size_t n = vec.size();
    vector<int> myArray = shuffleN(n);
    vector<int> vecShf(n);
    for(int i = 0; i < n; i++) {
    	vecShf[i] = vec[myArray[i]];
    }
    return vecShf;
}

void Solution::localSearch(int col) {
	Graph * graph = buildGraph(col);
	
	vector<int> sourceNodes = graph->getSourceNodes();
	
	// printScheduling();

	int src;

	vector<int> bestPath (pbData->N());
	int bestCost = MAX_INT;

	vector<int> sh = shuffleV(sourceNodes);

	for(int i = 0; i < sourceNodes.size(); i++) {
		src = sh[i];
		ShortestPath * path = dijkstra(graph, src);

		// cout << "path = ";
		// for(int i = 0; i < path->getPath().size(); i++)
		// 	cout << path->getPath()[i] << " ";
		// cout << endl;
		
		if(path->getCost() < bestCost) {
			bestCost = path->getCost();
			bestPath = path->getPath();
			// for(int q = 0; q < pbData->N(); q++) {
			// 	bestPath[q] = path->getPath()[q];
			// }
		}
		delete path;
	}

	vector<Node*> idNodes = graph->getIdNodes();

	// Update solution
	for(int i = 0; i < bestPath.size(); i++) {
		assignedTools[scheduling[i]] = idNodes[bestPath[i]]->getTools();
	}
	cost = bestCost;

	// for(int i = 0; i < idNodes.size(); i++) {
	// 	delete idNodes[i];
	// }

	delete graph;
}

void Solution::printCost() {
	cout << cost << endl;
}

void Solution::printAssignedTools() {
	for(int i = 0; i < pbData->N(); i++) {
		for(int j = 0; j < pbData->C(); j++) {
			cout << assignedTools[i][j] << " ";
		}
		cout << endl;
	}
}

void Solution::printScheduling() {
	for(int i = 0; i < pbData->N(); i++) {
		cout << scheduling[i] << " ";
	}
	cout << endl;
}

int Solution::minDistance(vector<int> dist, vector<bool> sptSet, int V) {
    // Initialize min value
    int min = MAX_INT, min_index;
 
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
 
    return min_index;
}

vector<int> Solution::getPath(vector<int> parent, int j, int src) {
	// cout << "j = " << j << endl;
	// cout << "src = " << src << endl;
	// cout << "parent = ";

	// for(int i = 0; i < parent.size(); i++)
	// 	cout << parent[i] << " ";
	// cout << endl;

	const int n = pbData->N();
    vector<int> path (n);
    int p = j;
    path[n-1] = j;
    int q = n-2;

    while(p != src) {
        p = parent[p];
        path[q] = p;
        q--;
    }

    // cout << "path = ";
	// for(int i = 0; i < path.size(); i++)
	// 	cout << path[i] << " ";
	// cout << endl;

    return path;
}

ShortestPath * Solution::dijkstra(Graph * G, int src) {

	const int V = G->getNbNodes();

	vector< vector<int> > graph = G->getGraph();

    vector<int> dist(V);  // The output array. dist[i] will hold
                  // the shortest distance from src to i
 
    // sptSet[i] will true if vertex i is included / in shortest
    // path tree or shortest distance from src to i is finalized
    vector<bool> sptSet(V);
 
    // Parent array to store shortest path tree
    vector<int> parent(V);
 
    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
    {
        parent[src] = -1;
        dist[i] = MAX_INT;
        sptSet[i] = false;
    }

    // cout << "--- after Initialize" << endl;
 
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
 
    // Find shortest path for all vertices
    for (int count = 0; count < V-1; count++)
    {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to src
        // in first iteration.
        int u = minDistance(dist, sptSet, V);
 
        // Mark the picked vertex as processed
        sptSet[u] = true;
 
        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < V; v++)
 
            // Update dist[v] only if is not in sptSet, there is
            // an edge from u to v, and total weight of path from
            // src to v through u is smaller than current value of
            // dist[v]
            if (!sptSet[v] /*&& graph[u][v]*/ &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v]  = u;
                dist[v] = dist[u] + graph[u][v];
            }  
    }

    // cout << "--- after COmputing shortest path" << endl;

    int min = MAX_INT;
    int minIdx = 0;

    vector<int> targetNodes = G->getTargetNodes();

	for (int i = 0; i < targetNodes.size(); i++) {		
    	if(dist[targetNodes[i]] < min) {
    		min = dist[targetNodes[i]];
    		minIdx = targetNodes[i];
    	}
    }

    // cout << "--- after targetNodes" << endl;

    vector<int> path = getPath(parent, minIdx, src);

    ShortestPath * sp = new ShortestPath(path, min);

    // cout << "--- after creating SP" << endl;

    return sp;
}