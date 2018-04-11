/*
Author: Jan Polzer
File:   main.cpp
Date:   4/4/2018
*/

#include "BST.h"
#include "MinHeap.h"
#include "MaxHeap.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>

// Build heap @size with random numbers
template <class T>
void buildHeaps (int m, int size, int seed, T *ds) {
    srand(seed);
    ds->buildheap(m, size, seed);
}

// Build BST @size with random
template <class T>
void buildBST (int m, int size, int seed, T *ds) {
    clock_t start = 0;
    int randomNumber = 0;
    srand(seed);
    start = clock();
    for (int i=0; i<size; i++) {
        randomNumber = rand()%(5*m) + 1;
        ds->insert(randomNumber);
    }
}

// Measure time that take to build @size random numbers into a heap
template <class T>
void buildTimeHeaps (int m, int size, int seed, T *ds, double &time) {
    clock_t start = 0;
    srand(seed);
    start = clock();
    ds->buildheap(m, size, seed);
    time = (clock()-start)/(double)(CLOCKS_PER_SEC/1000);
}

// Measure time that take to build @size random numbers into a bst
template <class T>
void buildTimeBST (int m, int size, int seed, T *ds, double &time) {
    clock_t start = 0;
    int randomNumber = 0;
    srand(seed);
    start = clock();
    for (int i=0; i<size; i++) {
        randomNumber = rand()%(5*m) + 1;
        ds->insert(randomNumber);
    }
    time = (clock()-start)/(double)(CLOCKS_PER_SEC/1000);
}

// Measure time that takes to perform delete min in a date structure
template <class T>
void timeDeleteMin (int m, int size, int seed, T *ds, double &timeDeleteMin) {
    clock_t start = 0;
    srand(seed);
    start = clock();
    for (int i=0; i<size; i++) {
        ds->deletemin();
    }
    timeDeleteMin = (clock()-start)/(double)(CLOCKS_PER_SEC/1000);
}

// Measure time that takes to perform delete max in a date structure
template <class T>
void timeDeleteMax (int m, int size, int seed, T *ds, double &timeDeleteMax) {
    clock_t start = 0;
    srand(seed);
    start = clock();
    for (int i=0; i<size; i++) {
        ds->deletemax();
    }
    timeDeleteMax = (clock()-start)/(double)(CLOCKS_PER_SEC/1000);
}

int main(int argc, char **argv) {

    int m = 1000000;  // 1 mil take over 1 hr
    BST *dsBST = nullptr;
    MinHeap *dsMinHeap = nullptr;
    MaxHeap *dsMaxHeap = nullptr;

    int size = 0;
    int seed = 0;
    std::cout << "\n... takes a while to genetate results\n";

    dsBST = new BST();
    dsMinHeap = new MinHeap();
    dsMaxHeap = new MaxHeap();

    // timeForHashds[seed][0-buildTime, 1-deleteMinTime, 2-deleteMaxTime][mult]
    double timesBST[5][3][5] = {};
    double timesMin[5][3][5] = {};
    double timesMax[5][3][5] = {};


    // timeAccumulatedUsingDifferentSeeds[0-buildTime, 1-deleteMinTime, 2-deleteMaxTime][mult]
    double accSeedsBST[3][5] = {};
    double accSeedsMin[3][5] = {};
    double accSeedsMax[3][5] = {};

    // timeAverageUsingDifferentSeeds[0-buildTime, 1-deleteMinTime, 2-deleteMaxTime][mult]
    double aveSeedsBST[3][5] = {};
    double aveSeedsMin[3][5] = {};
    double aveSeedsMax[3][5] = {};

    double m_mult[] = {1, 2, 3, 4, 5}; // size multipliers
    int mult = 0;

    for (mult=0; mult<5; mult++) { // run diffrent data sizes
    std::cout << "\n... still working (size " << m_mult[mult]*m << ")";

        for (seed=0; seed<5; seed++) { // use diffrent seeds
        std::cout << "*";
            // Measure build time
            size = (int)(m * m_mult[mult]);
            // BST
            buildTimeBST(m, size, seed, dsBST, timesBST[seed][0][mult]);
            // Min Heap
            buildTimeHeaps(m, size, seed, dsMinHeap, timesMin[seed][0][mult]);
            // Max Heap
            buildTimeHeaps(m, size, seed, dsMaxHeap, timesMax[seed][0][mult]);

            // Accumulate times for diffrent seeds
            accSeedsBST[0][mult] += timesBST[seed][0][mult];
            accSeedsMin[0][mult] += timesMin[seed][0][mult];
            accSeedsMax[0][mult] += timesMax[seed][0][mult];

            // Measure Deletemin time
            // BST
            timeDeleteMin(m, size, seed, dsBST, timesBST[seed][1][mult]);
            // Min Heap
            timeDeleteMin(m, size, seed, dsMinHeap, timesMin[seed][1][mult]);
            // Max Heap
            timeDeleteMin(m, size, seed, dsMaxHeap, timesMax[seed][1][mult]);

            // Accumulate times for diffrent seeds
            accSeedsBST[1][mult] += timesBST[seed][1][mult];
            accSeedsMin[1][mult] += timesMin[seed][1][mult];
            accSeedsMax[1][mult] += timesMax[seed][1][mult];

            // Build everything back for deletemax
            // BST
            buildBST(m, size, seed, dsBST);
            // Min Heap
            buildHeaps(m, size, seed, dsMinHeap);
            // Max Heap
            buildHeaps(m, size, seed, dsMaxHeap);

            // Measure Deletemax time
            // BST
            timeDeleteMax(m, size, seed, dsBST, timesBST[seed][2][mult]);
            // Min Heap
            timeDeleteMax(m, size, seed, dsMinHeap, timesMin[seed][2][mult]);
            // Max Heap
            timeDeleteMax(m, size, seed, dsMaxHeap, timesMax[seed][2][mult]);

            // Accumulate times for diffrent seeds
            accSeedsBST[2][mult] += timesBST[seed][2][mult];
            accSeedsMin[2][mult] += timesMin[seed][2][mult];
            accSeedsMax[2][mult] += timesMax[seed][2][mult];
        }

        // Averages for diffrent seeds
        aveSeedsBST[0][mult] = accSeedsBST[0][mult] / 5.0;
        aveSeedsMin[0][mult] = accSeedsMin[0][mult] / 5.0;
        aveSeedsMax[0][mult] = accSeedsMax[0][mult] / 5.0;

        aveSeedsBST[1][mult] = accSeedsBST[1][mult] / 5.0;
        aveSeedsMin[1][mult] = accSeedsMin[1][mult] / 5.0;
        aveSeedsMax[1][mult] = accSeedsMax[1][mult] / 5.0;

        aveSeedsBST[2][mult] = accSeedsBST[2][mult] / 5.0;
        aveSeedsMin[2][mult] = accSeedsMin[2][mult] / 5.0;
        aveSeedsMax[2][mult] = accSeedsMax[2][mult] / 5.0;
    }

    // Print preformance dss
    std::cout << "\n\nPerformance (BST) in seconds:\n";
    std::cout << "         " << std::setw(12) << "1,000,000" << std::setw(12) <<  "2,000,000" << std::setw(12)
    <<  "3,000,000" << std::setw(12) <<  "4,000,000" << std::setw(12) <<  "5,000,000";
    std::cout << "\nBuild    ";
    for (int size=0; size<5; size++) { std::cout  << std::fixed << std::setw(12) << std::setprecision(2) << aveSeedsBST[0][size] / 1000; }
    std::cout << "\nDeletemin";
    for (int size=0; size<5; size++) { std::cout  << std::fixed << std::setw(12) << std::setprecision(2) << aveSeedsBST[1][size] / 1000; }
    std::cout << "\nDeletemax";
    for (int size=0; size<5; size++) { std::cout  << std::fixed << std::setw(12) << std::setprecision(2) << aveSeedsBST[2][size] / 1000; }
    std::cout << "\n";

    std::cout << "\nPerformance (Min 5-Heap) in seconds:\n";
    std::cout << "         " << std::setw(12) << "1,000,000" << std::setw(12) <<  "2,000,000" << std::setw(12)
    <<  "3,000,000" << std::setw(12) <<  "4,000,000" << std::setw(12) <<  "5,000,000";
    std::cout << "\nBuild    ";
    for (int size=0; size<5; size++) { std::cout << std::setw(12) << std::setprecision(2) << aveSeedsMin[0][size] / 1000; }
    std::cout << "\nDeletemin";
    for (int size=0; size<5; size++) { std::cout << std::setw(12) << std::setprecision(2) << aveSeedsMin[1][size] / 1000; }
    std::cout << "\nDeletemax";
    for (int size=0; size<5; size++) { std::cout << std::setw(12) << std::setprecision(2) << aveSeedsMin[2][size] / 1000; }
    std::cout << "\n";

    std::cout << "\nPerformance (Max 5-Heap) in seconds:\n";
    std::cout << "         " << std::setw(12) << "1,000,000" << std::setw(12) <<  "2,000,000" << std::setw(12)
    <<  "3,000,000" << std::setw(12) <<  "4,000,000" << std::setw(12) <<  "5,000,000";
    std::cout << "\nBuild    ";
    for (int size=0; size<5; size++) { std::cout << std::setw(12) << std::setprecision(2) << aveSeedsMax[0][size] / 1000; }
    std::cout << "\nDeletemin";
    for (int size=0; size<5; size++) { std::cout << std::setw(12) << std::setprecision(2) << aveSeedsMax[1][size] / 1000; }
    std::cout << "\nDeletemax";
    for (int size=0; size<5; size++) { std::cout << std::setw(12) << std::setprecision(2) << aveSeedsMax[2][size] / 1000; }
    std::cout << "\n\n";

    delete dsBST;
    delete dsMaxHeap;
    delete dsMinHeap;
    return (0);
}
