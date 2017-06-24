#include "PbData.h"

using namespace std;

PbData::PbData(int n, int m, int c, vector< vector<int> > requiredTools) {
	this->n = n;
	this->m = m;
	this->c = c;
	this->requiredTools = requiredTools;
	this->optionalTools = vector< vector<int> > (n);
	for(int i = 0; i < n; i ++) {
		fillOptionalTools(i);
	}
}

void PbData::fillOptionalTools(int i) {
	vector<int> all (m);
	for(int j = 0; j < m; j++) {
		all[j] = j;
	}

    set<int> sAll( all.begin(), all.end() );
    set<int> sRequired( requiredTools[i].begin(), requiredTools[i].end() );
    vector<int> result;

    set_difference( sAll.begin(), sAll.end(), sRequired.begin(), sRequired.end(),
        back_inserter( result ) );

    optionalTools[i] = result;
}