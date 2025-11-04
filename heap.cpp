//
// Created by miyaz on 11/3/2025.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64]; // this will store node indexes
    int size;     // current number of items in the heap

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        if (size >= 64) return;   // just in case heap gets full
        data[size] = idx;        // put new item at the end
        upheap(size, weightArr); // fix order by moving it up if needed
        size++;                  // heap now has more item

    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        if (size == 0) return -1;
        int root = data[0];        // smallest item is at the top

        size--;
        if (size > 0) {
            data[0] = data[size];  // moves the last item to the top
            downheap(0, weightArr);
        }
        return root; // gives back the smallest index
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while (pos > 0) {
            int parent    = (pos - 1) / 2;
            int childIdx  = data[pos];
            int parentIdx = data[parent];

            // if child weight is less, or equal weight but smaller index, swap
            if (weightArr[childIdx] < weightArr[parentIdx] ||
                (weightArr[childIdx] == weightArr[parentIdx] && childIdx < parentIdx)) {

                // swaps child and parent
                int temp   = data[pos];
                data[pos]  = data[parent];
                data[parent] = temp;

                pos = parent;
                } else {
                    break;
                }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (true) {
            int left     = 2 * pos + 1;  // left child
            int right    = 2 * pos + 2;  // right child
            int smallest = pos;

            // check left child
            if (left < size) {
                int childIdx    = data[left];
                int smallestIdx = data[smallest];
                if (weightArr[childIdx] < weightArr[smallestIdx] ||
                    (weightArr[childIdx] == weightArr[smallestIdx] && childIdx < smallestIdx)) {
                    smallest = left;   // <-- was 'smallestIdx = left;' in your code
                    }
            }

            // check right child
            if (right < size) {
                int childIdx    = data[right];
                int smallestIdx = data[smallest];
                if (weightArr[childIdx] < weightArr[smallestIdx] ||
                    (weightArr[childIdx] == weightArr[smallestIdx] && childIdx < smallestIdx)) {
                    smallest = right;
                    }
            }

            // if no change needed, stop
            if (smallest != pos) {
                int temp       = data[pos];
                data[pos]      = data[smallest];
                data[smallest] = temp;
                pos = smallest;
            } else {
                break;
            }
        }
    }
};

#endif