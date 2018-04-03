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

// Measure time that take to insert @size random numbers into a data structure
template <class T>
void insertTime (int m, int size, int seed, T *ds, double &time) {
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
    int randomNumber = 0;
    srand(seed);
    start = clock();
    for (int i=0; i<size; i++) {
        randomNumber = rand()%(5*m) + 1;
        ds->deletemin();
    }
    timeDeleteMin = (clock()-start)/(double)(CLOCKS_PER_SEC/1000);
}

// Measure time that takes to perform delete max in a date structure
template <class T>
void timeDeleteMax (int m, int size, int seed, T *ds, double &timeDeleteMax) {
    clock_t start = 0;
    int randomNumber = 0;
    srand(seed);
    start = clock();
    for (int i=0; i<size; i++) {
        randomNumber = rand()%(5*m) + 1;
        ds->deletemin();
    }
    timeDeleteMax = (clock()-start)/(double)(CLOCKS_PER_SEC/1000);
}

int main(int argc, char **argv) {

    BST *dsBST = nullptr;
    MinHeap *dsMinHeap = nullptr;
    MaxHeap *dsMaxHeap = nullptr;

    int m = 1000;  // 10mil
    int array_size = 100; // 1mil

    int size = 0;
    int seed = 0;
    std::cout << "... takes a while to genetate results\n\n";

     dsBST = new BST();
     dsMinHeap = new MinHeap();
     dsMaxHeap = new MaxHeap();

    // timeForHashds[seed][0-buildTime, 1-deleteMinTime, 2-deleteMaxTime][mult][run5times]
    double timesBST[5][3][5][5] = {};
    double timesMin[5][3][5][5] = {};
    double timesMax[5][3][5][5] = {};

    // timeAccumulatedUsingDifferentSeeds[0-buildTime, 1-deleteMinTime, 2-deleteMaxTime][mult][run5times]
    double accSeedsBST[3][5][5] = {};
    double accSeedsMin[3][5][5] = {};
    double accSeedsMax[3][5][5] = {};

    // timeAverageUsingDifferentSeeds[0-buildTime, 1-deleteMinTime, 2-deleteMaxTime][mult][5times]
    double aveSeedsBST[3][5][5] = {};
    double aveSeedsMin[3][5][5] = {};
    double aveSeedsMax[3][5][5] = {};

    // timeRunAll5times[0-buildTime, 1-deleteMinTime, 2-deleteMaxTime][sizeMultiplier]
    double acc5timesBST[3][5] = {};
    double acc5timesMin[3][5] = {};
    double acc5timesMax[3][5] = {};

    // timeAverageUsingDifferentDataSizes[0-buildTime, 1-deleteMinTime, 2-deleteMaxTime][sizeMultiplier]
    double ave5timesBST[3][5] = {};
    double ave5timesMin[3][5] = {};
    double ave5timesMax[3][5] = {};

    int times;
    for (times=0; times<5; times++) {  // run 5 tests

        double m_mult[] = {0.1, 0.2, 0.3, 0.4, 0.6}; // size multipliers
        int mult = 0;

       for (mult=0; mult<5; mult++) { // run diffrent data sizes

           for (seed=0; seed<1; seed++) { // use diffrent seeds

                size = (int)(m * m_mult[mult]);

                // Measure insert time
                size = m_mult[mult] * m;
                // BST
                insertTime(m, size, seed, dsBST, timesBST[seed][0][mult][times]);
                // Min Heap
                insertTime(m, size, seed, dsMinHeap, timesMin[seed][0][mult][times]);
                // Max Heap
                insertTime(m, size, seed, dsMaxHeap, timesMax[seed][0][mult][times]);
//
//                // Accumulate times for diffrent seeds
//                accSeedsBST[0][mult][times] += timesBST[seed][0][mult][times];
//                accSeedsMin[0][mult][times] += timesMin[seed][0][mult][times];
//                accSeedsMax[0][mult][times] += timesMax[seed][0][mult][times];
//
//                size = 0.01 * m;
//                // Measure Deletemin time and Deletemax time
//                // BST
//                timeDeleteMin(m, size, seed, dsBST, timesBST[seed][1][mult][times], timesBST[seed][2][mult][times]);
//                // Min Heap
//                timeDeleteMin(m, size, seed, dsMinHeap, timesMin[seed][1][mult][times], timesMin[seed][2][mult][times]);
//                // Max Heap
//                timeDeleteMin(m, size, seed, dsMaxHeap, timesMax[seed][1][mult][times], timesMax[seed][2][mult][times]);
//
//                // Accumulate times for diffrent seeds
//                accSeedsBST[1][mult][times] += timesBST[seed][1][mult][times];
//                accSeedsMin[1][mult][times] += timesMin[seed][1][mult][times];
//                accSeedsMax[1][mult][times] += timesMax[seed][1][mult][times];
//
//                accSeedsBST[2][mult][times] += timesBST[seed][2][mult][times];
//                accSeedsMin[2][mult][times] += timesMin[seed][2][mult][times];
//                accSeedsMax[2][mult][times] += timesMax[seed][2][mult][times];
           }

//            // Averages for diffrent seeds
//            aveSeedsBST[0][mult][times] = accSeedsBST[0][mult][times] / 5.0;
//            aveSeedsMin[0][mult][times] = accSeedsMin[0][mult][times] / 5.0;
//            aveSeedsMax[0][mult][times] = accSeedsMax[0][mult][times] / 5.0;
//
//            aveSeedsBST[1][mult][times] = accSeedsBST[1][mult][times] / 5.0;
//            aveSeedsMin[1][mult][times] = accSeedsMin[1][mult][times] / 5.0;
//            aveSeedsMax[1][mult][times] = accSeedsMax[1][mult][times] / 5.0;
//
//            aveSeedsBST[2][mult][times] = accSeedsBST[2][mult][times] / 5.0;
//            aveSeedsMin[2][mult][times] = accSeedsMin[2][mult][times] / 5.0;
//            aveSeedsMax[2][mult][times] = accSeedsMax[2][mult][times] / 5.0;
//
//            // Accumulate data for 5 times
//            acc5timesBST[0][mult] += aveSeedsBST[0][mult][times];
//            acc5timesBST[1][mult] += aveSeedsBST[1][mult][times];
//            acc5timesBST[2][mult] += aveSeedsBST[2][mult][times];
//
//            acc5timesMin[0][mult] += aveSeedsMin[0][mult][times];
//            acc5timesMin[1][mult] += aveSeedsMin[1][mult][times];
//            acc5timesMin[2][mult] += aveSeedsMin[2][mult][times];
//
//            acc5timesMax[0][mult] += aveSeedsMax[0][mult][times];
//            acc5timesMax[1][mult] += aveSeedsMax[1][mult][times];
//            acc5timesMax[2][mult] += aveSeedsMax[2][mult][times];
       }

//        // Average times for 5 times
//        for (int mult2=0; mult2<5; mult2++) {
//            ave5timesBST[0][mult2] = acc5timesBST[0][mult2] / 5.0;
//            ave5timesBST[1][mult2] = acc5timesBST[1][mult2] / 5.0;
//            ave5timesBST[2][mult2] = acc5timesBST[2][mult2] / 5.0;
//
//            ave5timesMin[0][mult2] = acc5timesMin[0][mult2] / 5.0;
//            ave5timesMin[1][mult2] = acc5timesMin[1][mult2] / 5.0;
//            ave5timesMin[2][mult2] = acc5timesMin[2][mult2] / 5.0;
//
//            ave5timesMax[0][mult2] = acc5timesMax[0][mult2] / 5.0;
//            ave5timesMax[1][mult2] = acc5timesMax[1][mult2] / 5.0;
//            ave5timesMax[2][mult2] = acc5timesMax[2][mult2] / 5.0;
//        }

    }

    // Print preformance dss
    std::cout << "\n\nPerformance (BST) in milliseconds:\n";
    std::cout << "         " << std::setw(12) << "1,000,000" << std::setw(12) <<  "2,000,000" << std::setw(12)
    <<  "3,000,000" << std::setw(12) <<  "4,000,000" << std::setw(12) <<  "5,000,000";
    std::cout << "\nBuild    ";
    for (int size=0; size<5; size++) { std::cout  << std::fixed << std::setw(12) << std::setprecision(2) << ave5timesBST[0][size]; }
    std::cout << "\nDeletemin";
    for (int size=0; size<5; size++) { std::cout  << std::fixed << std::setw(12) << std::setprecision(2) << ave5timesBST[1][size]; }
    std::cout << "\nDeletemax";
    for (int size=0; size<5; size++) { std::cout  << std::fixed << std::setw(12) << std::setprecision(2) << ave5timesBST[2][size]; }
    std::cout << "\n";

    std::cout << "\nPerformance (Min 5-Heap) in milliseconds::\n";
    std::cout << "         " << std::setw(12) << "1,000,000" << std::setw(12) <<  "2,000,000" << std::setw(12)
    <<  "3,000,000" << std::setw(12) <<  "4,000,000" << std::setw(12) <<  "5,000,000";
    std::cout << "\nBuild    ";
    for (int size=0; size<5; size++) { std::cout << std::setw(12) << std::setprecision(2) << ave5timesMin[0][size]; }
    std::cout << "\nDeletemin";
    for (int size=0; size<5; size++) { std::cout << std::setw(12) << std::setprecision(2) << ave5timesMin[1][size]; }
    std::cout << "\nDeletemax";
    for (int size=0; size<5; size++) { std::cout << std::setw(12) << std::setprecision(2) << ave5timesMin[2][size]; }
    std::cout << "\n";

    std::cout << "\nPerformance (Max 5-Heap) in milliseconds::\n";
    std::cout << "         " << std::setw(12) << "1,000,000" << std::setw(12) <<  "2,000,000" << std::setw(12)
    <<  "3,000,000" << std::setw(12) <<  "4,000,000" << std::setw(12) <<  "5,000,000";
    std::cout << "\nBuild    ";
    for (int size=0; size<5; size++) { std::cout << std::setw(12) << std::setprecision(2) << ave5timesMax[0][size]; }
    std::cout << "\nDeletemin";
    for (int size=0; size<5; size++) { std::cout << std::setw(12) << std::setprecision(2) << ave5timesMax[1][size]; }
    std::cout << "\nDeletemax";
    for (int size=0; size<5; size++) { std::cout << std::setw(12) << std::setprecision(2) << ave5timesMax[2][size]; }
    std::cout << "\n\n";

    delete dsBST;
    delete dsMaxHeap;
    delete dsMinHeap;
    return (0);
}
