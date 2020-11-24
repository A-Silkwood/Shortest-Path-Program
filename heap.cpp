#include <iostream>
#include "heap.h"

const int INT_INF = 2147483647;

// return position of the parent in a min-heap
int Parent(int i) {return (i - 1) / 2;}
// return position of the left child in a min-heap
int Left(int i) {return 2 * i + 1;}
// return position of the right child in a min-heap
int Right(int i) {return 2 * i + 2;}

// maintain the min-heap property at given position
// assumes its left and right subtrees are min-heaps
// n is vertices in heap not size of heap array
void MinHeapify(Vertex **heap, int i, int n) {
    // get positions of left and right children
    int l = Left(i);
    int r = Right(i);

    // find the smallest key between a parent and its left and right child
    int smallest = i;
    if(l < n && heap[l]->dist < heap[smallest]->dist) {smallest = l;}
    if(r < n && heap[r]->dist < heap[smallest]->dist) {smallest = r;}

    // correct min-heap if the parent does not have the smallest key
    if(smallest != i) {
        // swap parent with smallest child
        Vertex *temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        // check subtree affected for maintenance
        MinHeapify(heap, smallest, n);
    }
}

// create a min-heap from an array of Vertex pointers
// n is vertices in heap not size of heap array
void BuildMinHeap(Vertex **heap, int n) {
    for(int i = n / 2 - 1; i >= 0; i--) {MinHeapify(heap, i, n);}
}

// inserts a vertex into the min-heap; assumes heap has space
void Insert(Vertex **heap, Vertex *vertex) {
    // stop at first null pointer in min-heap
    int ix = 0;
    while(heap[ix] != NULL) {ix++;}
    // add vertex at first null pointer
    heap[ix] = vertex;

    // rebuild min-heap
    BuildMinHeap(heap, ix + 1);
}

// returns the vertex with the smallest key
Vertex* Minimum(Vertex **heap) {return heap[0];}

// returns and removes the vertex with the smallest key
Vertex* ExtractMin(Vertex **heap, int size) {
    Vertex *min = heap[0]; // save min

    // remove min
    int n = 0;
    while(n < size && heap[n] != NULL) {n++;}
    heap[0] = heap[n-1];
    // rebuild min-heap
    BuildMinHeap(heap, size);

    return min;
}

// changes the key of a vertex to a value less than or equal to its current key
void DecreaseKey(Vertex **heap, int size, Vertex *vertex, int key) {
    // check if key is less than
    if(key < vertex->dist) {
        vertex->dist = key; // change key

        // rebuild min-heap
        BuildMinHeap(heap, size);
    }
}
