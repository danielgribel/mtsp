#include <fstream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <string>
#include <map>
#include <ctime>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits>
#include <queue>
#include "Solution.h"
#include "Heap.h"

using namespace std;

#define InputFile "../data/Tabela3/test.txt"

PbData * load(string dataFileName) {
    // Open the data file
    ifstream input(dataFileName.c_str());

    if (! input) {
        cerr << "Unable to open data file: " << dataFileName << endl;
    }
    
    // Read the size of the puzzle
    int n, m, c;
    input >> n; // Number of jobs
    input >> m; // Number of tools
    input >> c; // Machine capacity
    int x;

    vector< vector<int> > requiredTools (n);

    // Iterating over tools
    for(int j = 0; j < m; j++) {
	    // Iterating over jobs
	    for(int i = 0; i < n; i++) {
	    	input >> x;
	    	if(x == 1) {
	    		requiredTools[i].push_back(j);
	    	}
	    }
	}

	PbData * pbData = new PbData(n, m, c, requiredTools);

	return pbData;
}

vector<int> toolsDiff(const vector<int> all, const vector<int> required) {
    set<int> sAll( all.begin(), all.end() );
    set<int> sRequired( required.begin(), required.end() );
    vector<int> result;

    set_difference( sAll.begin(), sAll.end(), sRequired.begin(), sRequired.end(),
        back_inserter( result ) );

    return result;
}

vector<int> shuffle(size_t n) {
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

vector<int> shuffle(vector<int> vec) {
	size_t n = vec.size();
    vector<int> myArray = shuffle(n);
    vector<int> vecShf(n);
    for(int i = 0; i < n; i++) {
    	vecShf[i] = vec[myArray[i]];
    }
    return vecShf;
}

Solution * randomSolution(PbData * pbData) {
	vector< vector<int> > requiredTools = pbData->getRequiredTools();
	int n = pbData->N();
	int C = pbData->C();
	int m = pbData->M();

	vector< vector<int> > assignedTools (n, vector<int> (C));
	int nbToolsJob;
		
	for(int i = 0; i < n; i++) {
		// Add required tools to assigned tools
		nbToolsJob = requiredTools[i].size();
		for(int j = 0; j < nbToolsJob; j++) {
			assignedTools[i][j] = requiredTools[i][j];
		}
		// Get the difference between assigned and required sets and shuffle it
		vector<int> remaining = shuffle(pbData->getOptionalTools(i));
		// For the remaining tools (in case C > nb tools required by the job), assign random tools not assigned yet
		for(int q = nbToolsJob; q < C; q++) {
			assignedTools[i][q] = remaining[q-nbToolsJob];
		}
	}

	Solution * solution = new Solution(assignedTools, shuffle(n), pbData);

	return solution;
}

Solution * crossover(Solution * p1, Solution * p2, PbData * pbData) {
	int n = pbData->N();
	int i, r;
	vector<int> scheduling = shuffle(n);
	vector< vector<int> > assigned (n, vector<int> (pbData->C()));

	for(int i1 = 0; i1 < n; i1++) {
		i = scheduling[i1];
		r = rand() % 2;
		if(r == 0) { // Take the component of 1st parent
			assigned[i] = p1->getAssignedTools(i);
		}
		if(r == 1) { // Take the component of 2nd parent
			assigned[i] = p2->getAssignedTools(i);
		}
	}

	Solution * offspring = new Solution(assigned, scheduling, pbData);

	return offspring;
}

vector<Solution*> initialPopulation(int S, PbData * pbData) {
	vector<Solution*> initialPop;
	for(int i = 0; i < S; i++) {
		Solution * solution = randomSolution(pbData);
		initialPop.push_back(solution);
	}
	return initialPop;
}

Solution * tournamentSelection(vector<Solution*> population) {
    Solution * bestSolution;
    int bestCost = MAX_INT;
    int cost, r;

    for(int i = 0; i < 2; i++) {
        r = rand() % population.size();
        cost = population[r]->getCost();
        if(cost < bestCost) {
            bestSolution = population[r];
            bestCost = cost;
        }
    }

    return bestSolution;
}

void deletePopulation(vector<Solution*> population) {
	for(int i = 0; i < population.size(); i++) {
		delete population[i];
	}
}

vector<Solution*> selectSurvivors(vector<Solution*> largePopulation, const int Pi) {
	HeapPii * heap = new HeapPii();
	vector<Solution*> population (Pi);
	vector<int> remained (largePopulation.size());
	int id;
	
	// Fill the heap to have solutions ordered by min cost
	for(int i = 0; i < largePopulation.size(); i++) {
		heap->push_min(largePopulation[i]->getCost(), i);
	}
	
	// Keep the best solutions
	for(int i = 0; i < Pi; i++) {
		int id = heap->pop_min();
		population[i] = largePopulation[id];
		remained[id] = 1;
	}

	// Delete bad solutions from population 
	for(int i = 0; i < largePopulation.size(); i++) {
		if(remained[i] != 1) {
			delete largePopulation[i];
		}
	}

	return population;
}

void solve() {
	// Population size
	const int Pi = 100;

	// Max population size
	const int Mx = 500;

	// Number of Iterations
	const int It = 10000;

	// Initial population size
	const int Ip = 1000;

	PbData * pbData = load(InputFile);

	clock_t begin = clock();

	vector<Solution*> population = initialPopulation(Ip, pbData);
	Solution * p1;
	Solution * p2;
	Solution * off;
	int bestCost = MAX_INT;

	for(int i = 0; i < It; i++) {
		p1 = tournamentSelection(population); 
		p2 = tournamentSelection(population);
		off = crossover(p1, p2, pbData);
		population.push_back(off);
		if(off->getCost() < bestCost) {
			bestCost = off->getCost();
		}
		if(population.size() > Mx) {
			population = selectSurvivors(population, Pi);
		}
	}

	clock_t end = clock();
  	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  	
  	cout << "Best cost: " << bestCost << endl;
	cout << "-- Time: " << elapsed_secs << endl;

	deletePopulation(population);
	delete pbData;
}

int main(int argc, char** argv) {
	int seed = atoi(argv[1]);
	srand(seed);
  	solve();
	return 0;
}