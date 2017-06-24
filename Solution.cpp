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

// Get job nodes considering job j and column c of assigned tools
vector<Node*> Solution::jobNodes(int j, int c) {
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

	for(int i = 0; i < optionalTools.size(); i++) {
		if(!prohibited[optionalTools[i]]) {
			vector<int> nd = baseTools;
			nd.push_back(optionalTools[i]);
			Node * node = new Node(nd, j);
			nodes.push_back(node);
		}
	}

	return nodes;
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