#ifndef Heap_Pii_H
#define Heap_Pii_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <functional>

using namespace std;

class HeapPii {

    private:
    
        vector< pair<int, int> > heap;
    
    public:
    
        HeapPii();
    
        ~HeapPii();
    
        void push_max(int cost, int val);
    
        void push_min(int cost, int val);
        
        int pop_max();

        int pop_min();
    
        pair<int, int> front_max();
	
    	pair<int, int> front_min();

        vector< pair<int, int> > getHeap() { return heap; };
};

#endif