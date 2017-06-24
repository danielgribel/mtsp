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

		// Optional tools for jobs
		vector< vector<int> > optionalTools;

		// Number of jobs
		int n;

		// Number of tools
		int m; 

		// Machine capacity
		int c;

		void fillOptionalTools(int i);

    public:

    	PbData(int n, int m, int c, vector< vector<int> > requiredTools);

    	int N() { return n; };

    	int M() { return m; };

    	int C() { return c; };

    	vector< vector<int> > getRequiredTools() { return requiredTools; };

    	vector< vector<int> > getOptionalTools() { return optionalTools; };

    	vector<int> getOptionalTools(int i) { return optionalTools[i]; };
};

#endif