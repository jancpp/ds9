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
//    clock_t start = 0;
//    int randomNumber = 0;
    srand(seed);
//    start = clock();
//    for (int i=0; i<size; i++) {
//        randomNumber = rand()%(5*m) + 1;
        ds->buildheap(m, size, seed);
//    }
    std::cout << "Heap size in build/no time:" << ds->getSize() << "\n";
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
    std::cout << "BST size in build/no time:" << ds->getSize() << "\n";
}

// Measure time that take to build @size random numbers into a heap
template <class T>
void buildTimeHeaps (int m, int size, int seed, T *ds, double &time) {
    clock_t start = 0;
//    int randomNumber = 0;
    srand(seed);
    start = clock();
//    for (int i=0; i<size; i++) {
//        randomNumber = rand()%(5*m) + 1;
        ds->buildheap(m, size, seed);
//    }
    time = (clock()-start)/(double)(CLOCKS_PER_SEC/1000);
    
    std::cout << "Heap size in build:" << ds->getSize() << ", time: "<< time << "\n";
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
    std::cout << "BST size in build:" << ds->getSize() << ", time: "<< time << "\n";
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
    std::cout << "DS size in min:" << ds->getSize() << ", time: "<< timeDeleteMin << "\n";
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
    std::cout << "DS size in max:" << ds->getSize() << ", time: "<< timeDeleteMax << "\n";
}

int main(int argc, char **argv) {

    BST *dsBST = nullptr;
    MinHeap *dsMinHeap = nullptr;
    MaxHeap *dsMaxHeap = nullptr;

    int m = 1000;  // 1mil
//    int array_size = 10000000; // 10mil

    int size = 0;
    int seed = 0;
    std::cout << "... takes a while to genetate results\n\n";

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

//    // timeRunAll5times[0-buildTime, 1-deleteMinTime, 2-deleteMaxTime][sizeMultiplier]
//    double acc5timesBST[3][5] = {};
//    double acc5timesMin[3][5] = {};
//    double acc5timesMax[3][5] = {};
//
//    // timeAverageUsingDifferentDataSizes[0-buildTime, 1-deleteMinTime, 2-deleteMaxTime][sizeMultiplier]
//    double aveSeedBST[3][5] = {};
//    double aveSeedMin[3][5] = {};
//    double aveSeedMax[3][5] = {};

//    int times;
//    for (times=0; times<5; times++) {  // run 5 tests

        double m_mult[] = {0.1, 0.2, 0.3, 0.4, 0.5}; // size multipliers
        int mult = 0;

       for (mult=0; mult<5; mult++) { // run diffrent data sizes

           std::cout << "\n ===== MULT: " << mult+1 << "=====\n";
           for (seed=0; seed<5; seed++) { // use diffrent seeds
               std::cout << "\n == SEED: " << seed+1 << "==\n";
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

//                size = 0.01 * m;
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
               timeDeleteMax(m, size, seed, dsBST, timesBST[seed][1][mult]);
               // Min Heap
               timeDeleteMax(m, size, seed, dsMinHeap, timesMin[seed][1][mult]);
               // Max Heap
               timeDeleteMax(m, size, seed, dsMaxHeap, timesMax[seed][1][mult]);
               
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

//            // Accumulate data for 5 times
//            acc5timesBST[0][mult] += aveSeedsBST[0][mult];
//            acc5timesBST[1][mult] += aveSeedsBST[1][mult];
//            acc5timesBST[2][mult] += aveSeedsBST[2][mult];
//
//            acc5timesMin[0][mult] += aveSeedsMin[0][mult];
//            acc5timesMin[1][mult] += aveSeedsMin[1][mult];
//            acc5timesMin[2][mult] += aveSeedsMin[2][mult];
//
//            acc5timesMax[0][mult] += aveSeedsMax[0][mult];
//            acc5timesMax[1][mult] += aveSeedsMax[1][mult];
//            acc5timesMax[2][mult] += aveSeedsMax[2][mult];
//       }

//        // Average times for 5 times
//        for (int mult2=0; mult2<5; mult2++) {
//            aveSeedBST[0][mult2] = acc5timesBST[0][mult2] / 5.0;
//            aveSeedBST[1][mult2] = acc5timesBST[1][mult2] / 5.0;
//            aveSeedBST[2][mult2] = acc5timesBST[2][mult2] / 5.0;
//
//            aveSeedMin[0][mult2] = acc5timesMin[0][mult2] / 5.0;
//            aveSeedMin[1][mult2] = acc5timesMin[1][mult2] / 5.0;
//            aveSeedMin[2][mult2] = acc5timesMin[2][mult2] / 5.0;
//
//            aveSeedMax[0][mult2] = acc5timesMax[0][mult2] / 5.0;
//            aveSeedMax[1][mult2] = acc5timesMax[1][mult2] / 5.0;
//            aveSeedMax[2][mult2] = acc5timesMax[2][mult2] / 5.0;
//        }

    }

    // Print preformance dss
    std::cout << "\n\nPerformance (BST) in milliseconds:\n";
    std::cout << "         " << std::setw(12) << "1,000,000" << std::setw(12) <<  "2,000,000" << std::setw(12)
    <<  "3,000,000" << std::setw(12) <<  "4,000,000" << std::setw(12) <<  "5,000,000";
    std::cout << "\nBuild    ";
    for (int size=0; size<5; size++) { std::cout  << std::fixed << std::setw(12) << std::setprecision(2) << aveSeedsBST[0][size]; }
    std::cout << "\nDeletemin";
    for (int size=0; size<5; size++) { std::cout  << std::fixed << std::setw(12) << std::setprecision(2) << aveSeedsBST[1][size]; }
    std::cout << "\nDeletemax";
    for (int size=0; size<5; size++) { std::cout  << std::fixed << std::setw(12) << std::setprecision(2) << aveSeedsBST[2][size]; }
    std::cout << "\n";

    std::cout << "\nPerformance (Min 5-Heap) in milliseconds::\n";
    std::cout << "         " << std::setw(12) << "1,000,000" << std::setw(12) <<  "2,000,000" << std::setw(12)
    <<  "3,000,000" << std::setw(12) <<  "4,000,000" << std::setw(12) <<  "5,000,000";
    std::cout << "\nBuild    ";
    for (int size=0; size<5; size++) { std::cout << std::setw(12) << std::setprecision(2) << aveSeedsMin[0][size]; }
    std::cout << "\nDeletemin";
    for (int size=0; size<5; size++) { std::cout << std::setw(12) << std::setprecision(2) << aveSeedsMin[1][size]; }
    std::cout << "\nDeletemax";
    for (int size=0; size<5; size++) { std::cout << std::setw(12) << std::setprecision(2) << aveSeedsMin[2][size]; }
    std::cout << "\n";

    std::cout << "\nPerformance (Max 5-Heap) in milliseconds::\n";
    std::cout << "         " << std::setw(12) << "1,000,000" << std::setw(12) <<  "2,000,000" << std::setw(12)
    <<  "3,000,000" << std::setw(12) <<  "4,000,000" << std::setw(12) <<  "5,000,000";
    std::cout << "\nBuild    ";
    for (int size=0; size<5; size++) { std::cout << std::setw(12) << std::setprecision(2) << aveSeedsMax[0][size]; }
    std::cout << "\nDeletemin";
    for (int size=0; size<5; size++) { std::cout << std::setw(12) << std::setprecision(2) << aveSeedsMax[1][size]; }
    std::cout << "\nDeletemax";
    for (int size=0; size<5; size++) { std::cout << std::setw(12) << std::setprecision(2) << aveSeedsMax[2][size]; }
    std::cout << "\n\n";

    delete dsBST;
    delete dsMaxHeap;
    delete dsMinHeap;
    return (0);
}
