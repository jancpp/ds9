/*
Author: Jan Polzer
File:   MinHeap.h
Date:   3/12/2018
Updated: 4/2/2018
*/

#include "MinHeap.h"
#include <iostream>
#include <fstream>
#include <climits>

MinHeap::MinHeap() {
    m_size = 0;
    for (int i=0; i<10000000; i++) {
        m_array[i] = -1;
    }
}

void MinHeap::buildheap(int m, int size, int seed) {
    //         Read data from a file into array
//    std::ifstream inputFile;
//    int number = -1;
//    m_size = 0;
//    inputFile.open("data.txt");
//    if (!inputFile) {
//        inputFile.close();
//        std::cout << "Error reading the input file.\n";
//    } else {
//        std::cout << "Data.txt elements:";
//        while(inputFile >> number) {
//            std::cout << " " << number;
//            m_array[m_size] = number;
//            m_size++;
//        }
//        inputFile.close();
//        std::cout << "\n";
//        for (int i=m_size-1; 0<=i; i--) {
//            if (!isLeaf(i)) {
//                heapify(i);
//            }
//        }
//    }
    int randomNumber = 0;
    srand(seed);
    //    start = clock();
    for (int i=0; i<size; i++) {
        randomNumber = rand()%(5*m) + 1;
        m_array[m_size] = randomNumber;
        m_size++;
    }
    std::cout << "\n";
    for (int i=m_size-1; 0<=i; i--) {
        if (!isLeaf(i)) {
            heapify(i);
        }
    }
    levelorder();
}

void MinHeap::heapify(int index) {
    int min = minChild(index);
    if ((m_array[index] != -1) && (m_array[index] > m_array[min])) {
        swap(index, min);
        heapify(min);
    }
}

int MinHeap::minChild(int parent) {
    int min = parent;
    for (int childPos = M_K; 0<childPos; childPos--) {
        int child = childOf(parent, childPos);
        if ((m_array[child] != -1) && (m_array[child] < m_array[min])) {
            min = child;
        }
    }
    return min;
}

int MinHeap::childOf(int ofIndex, int atPosition) {
    // The jth child of A[i] is at A[M_Ki+j], 1<= j <=M_K, if it exists.
    return (M_K * ofIndex + atPosition);
}

int MinHeap::parentOf(int index) {
    // The parent of A[i] is at A[floor((i-1)/M_K)], if it exists.
    return (floor((index-1) / M_K));

}

void MinHeap::swap(int index1, int index2) {
    int temp = m_array[index1];
    m_array[index1] = m_array[index2];
    m_array[index2] = temp;
}

bool MinHeap::isLeaf(int index) {
    // The jth child of A[i] is at A[M_Ki+j], 1<= j <=M_K, if it exists.
    bool leaf = false;
    int firstchild = m_array[M_K*index+1];
    if (firstchild == -1) {
        leaf = true;
    }
    return leaf;
}

void MinHeap::insert(int key) {
    m_size++;
    m_array[m_size-1] = key;
    int parent = parentOf(m_size-1);
    heapify(parent);
    while (parent != 0) {
        parent = parentOf(parent);
        heapify(parent);
    }
}

void MinHeap::deletemin() {
    if (m_size >  0) {
        m_array[0] = m_array[m_size-1];
        m_size--;
        heapify(0);
    }
}

void MinHeap::deletemax() {
    int maxIndex = findmaxindex();
    if (m_size > 0) {
        m_array[maxIndex] = m_array[m_size-1];
        m_array[m_size-1] = -1;
        m_size--;
    }
}


int MinHeap::findmaxindex() {
    int max = m_size-1;
    int i = -1;
    if (m_size >  0) {
        for (i=m_size-1; 0<i; i--) {
            if (isLeaf(i)) {
                if ((m_array[i] != -1) && (m_array[i] > m_array[max])) {
                    max = i;
                }
            } else {
                break;
            }
        }
    }
    return max;
}

int MinHeap::findmax() {
    int maxVal = -1;
    if (m_size > 0) {
        maxVal = m_array[findmaxindex()];
    } else {
        std::cout << "\nHeap is empty.\n";
    }
    return maxVal;
}

int MinHeap::findmin() {
    int minVal = -1;
    if (m_size > 0) {
        minVal = m_array[0];
    }
    return minVal;
}

void MinHeap::levelorder() {
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
