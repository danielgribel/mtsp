#ifndef Data_h
#define Data_h

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class PbData {

	private:

		// Required tools by jobs
		vector< vector<int> > requiredTools;

		// Number of jobs
		int n;

		// Number of tools
		int m; 

		// Machine capacity
		int c;

    public:

    	PbData(int n, int m, int c, vector< vector<int> > requiredTools);

    	int N() { return n; };

    	int M() { return m; };

    	int C() { return c; };

    	vector< vector<int> > getRequiredTools() { return requiredTools; }; 

    	vector<int> missingTools(int i);
};

#endif