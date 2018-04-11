/*
Author: Jan Polzer
File:   MaxHeap.cpp
Date:   3/12/2018
Updated: 4/2/2018
*/

#include "MaxHeap.h"
#include <iostream>
#include <fstream>
#include <climits>

MaxHeap::MaxHeap() {
    m_size = 0;
    for (int i=0; i<10000000; i++) {
        m_array[i] = -1;
    }
}

int MaxHeap::getSize() {
    return m_size;
}

void MaxHeap::buildheap(int m, int size, int seed) {
    int randomNumber = 0;
    srand(seed);
//    start = clock();
    for (int i=0; i<size; i++) {
        randomNumber = rand()%(5*m) + 1;
        m_array[m_size] = randomNumber;
        m_size++;
    }
    for (int i=m_size-1; 0<=i; i--) {
        if (!isLeaf(i)) {
            heapify(i);
        }
    }
}

void MaxHeap::heapify(int index) {
    if (maxChild(index) < 10000000) {
        int max = maxChild(index);
        if ((m_array[index] != -1) && (m_array[index] < m_array[max])) {
            swap(index, max);
            heapify(max);
        }
    }
}

int MaxHeap::maxChild(int parent) {
    int max = parent;
    for (int childPos = M_K; 0<childPos; childPos--) {
        int child = childOf(parent, childPos);
        if ((m_array[child] != -1) && (m_array[child] > m_array[max])) {
            max = child;
        }
    }
    return max;
}

int MaxHeap::childOf(int ofIndex, int atPosition) {
    // The jth child of A[i] is at A[M_Ki+j], 1<= j <=M_K, if it exists.
    return (M_K * ofIndex + atPosition);
}

int MaxHeap::parentOf(int index) {
    // The parent of A[i] is at A[floor((i-1)/M_K)], if it exists.
    return (floor((index-1) / M_K));
    
}

void MaxHeap::swap(int index1, int index2) {
    int temp = m_array[index1];
    m_array[index1] = m_array[index2];
    m_array[index2] = temp;
}

bool MaxHeap::isLeaf(int index) {
    // The jth child of A[i] is at A[M_Ki+j], 1<= j <=M_K, if it exists.
    bool leaf = false;
    int firstchild = m_array[M_K*index+1];
    if (firstchild == -1) {
        leaf = true;
    }
    return leaf;
}

void MaxHeap::insert(int key) {
    m_size++;
    m_array[m_size-1] = key;
    int parent = parentOf(m_size-1);
    heapify(parent);
    while (parent != 0) {
        parent = parentOf(parent);
        heapify(parent);
    }
}

void MaxHeap::deletemax() {
    if (m_size >  0) {
        m_array[0] = m_array[m_size-1];
        m_size--;
        heapify(0);
    }
}

void MaxHeap::deletemin() {
    int minIndex = findminindex();
    if (m_size > 0) {
        m_array[minIndex] = m_array[m_size-1];
        m_array[m_size-1] = -1;
        m_size--;
    }
}


int MaxHeap::findminindex() {
    int min = m_size-1;
    int i = -1;
    if (m_size >  0) {
        for (i=m_size-1; 0<i; i--) {
            if (isLeaf(i)) {
                if ((m_array[i] != -1) && (m_array[i] < m_array[min])) {
                    min = i;
                }
            } else {
                break;
            }
        }
    }
    return min;
}

int MaxHeap::findmin() {
    int minVal = -1;
    if (m_size > 0) {
        minVal = m_array[findminindex()];
    } else {
        std::cout << "\nHeap is empty.\n";
    }
    return minVal;
}

int MaxHeap::findmax() {
    int maxVal = -1;
    if (m_size > 0) {
        maxVal = m_array[0];
    }
    return maxVal;
}

void MaxHeap::levelorder() {
    int levels = 1;
    int newLevel = 0;
    
    std::cout << "\n";
    for (int i=0; i<m_size; i++) {
        if(m_array[i] != -1) {
            std::cout << m_array[i] << " ";
            if ((newLevel == i) && ((i%M_K == 0) || (i == M_K))) {
                std::cout << "\n";
                newLevel += pow(M_K, levels);
                levels++;
            } else if ((i%M_K == 0) && (m_array[i+1] != -1)) {
                std::cout << "- ";
            }
        }
    }
}
