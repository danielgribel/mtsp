#include "Heap.h"

using namespace std;

HeapPii::HeapPii() {

}

HeapPii::~HeapPii() {

}

void HeapPii::push_max(int cost, int val) {
    heap.push_back( pair<int, int>(cost, val) );
    push_heap(heap.begin(), heap.end());
}

void HeapPii::push_min(int cost, int val) {
    heap.push_back( pair<int, int>(cost, val) );
    push_heap(heap.begin(), heap.end(), greater< pair<int, int> >());
}

int HeapPii::pop_max() {
    make_heap(heap.begin(), heap.end());
    pair<int, int> pair = heap.front();
    pop_heap(heap.begin(), heap.end());
    heap.pop_back();
    return pair.second;
}

int HeapPii::pop_min() {
    make_heap(heap.begin(), heap.end(), greater< pair<int, int> >());    
    pair<int, int> pair = heap.front();
    pop_heap(heap.begin(), heap.end());
    heap.pop_back();
    return pair.second;
}

pair<int, int> HeapPii::front_max() {
    make_heap(heap.begin(), heap.end());
    return heap.front();
}

pair<int, int> HeapPii::front_min() {
    make_heap(heap.begin(), heap.end(), greater< pair<int, int> >());
    return heap.front();
}