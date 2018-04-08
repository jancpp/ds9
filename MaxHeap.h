/*
Author: Jan Polzer
File:   MaxHeap.h
Date:   3/12/2018
Updated: 4/2/2018
*/

#ifndef MAX_HEAP
#define MAX_HEAP

#include <iostream>
#include <queue>
#include <math.h>

class MaxHeap {
    
public:
    MaxHeap();
    
    // @pre:    Heap
    // @post:   None
    // @return: Size of heap.
    int getSize();
    
    // @pre:    File with numbers
    // @Post:   Max 5 - heap
    // @Return: None
    void buildheap(int m, int size, int seed);

    // @pre:    5 - max heap
    // @Post:   Inserted a new element
    // @Return: None
    void insert(int key);

    // @pre:    5 - max heap
    // @post:   Deleted min key
    // @return: None
    void deletemin();

    // @pre:    5 - max heap
    // @post:   Deleted max key
    // @return: None
    void deletemax();

    // @pre:    5 - max heap
    // @post:   Found the smallest element in the 5 - max heap
    // @return: A value of the smallest element.
    int findmin();

    // @pre:    5 - max heap
    // @post:   Found the largest element in the 5 - max heap
    // @return: A value the largest element in max heap.
    int findmax();

    // @pre:    5 - max heap
    // @post:   Printed out all the elements of the max heap by level using levelorder traversal.
    // @return: None
    void levelorder();

    // @pre:    5 - max heap
    // @post:   None
    // @return: True if element is a leaf, false otherwise
    bool isLeaf(int index);

    // @pre:    Two indexes from heap
    // @post:   Swapped valued based on indexes
    // @return: None
    void swap(int index1, int index2);

    // @pre:    5 - heap
    // @post:   Element is moved to position where belongs preserving a heap structure
    // @return: None
    void heapify(int index);

    // @pre:    An index of element
    // @post:   None
    // @return: An index of its child
    int childOf(int index, int atPosition);

    // @pre:    An index of parent in heap
    // @post:   None
    // @return: An index of the parents largest child
    int maxChild(int parent);

    // @pre:    An index of a child in a heap
    // @post:   None
    // @return: An index of parent of the child
    int parentOf(int index);

private:
    int m_array[10000000];
    int m_size;
    static const int M_K = 2; // for K-ary heap (5-heap)

    // @pre:    5 - max heap
    // @post:   Found the largest index of element in the 5 - max heap
    // @return: The index of the largest element
    int findminindex();
};

#endif
