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

// Measure time that take to insert @size random numbers into hash tables
template <class T>
void insertTime (int m, int size, int seed, T *table, double &time) {
    clock_t start = 0;
    int randomNumber = 0;
    srand(seed);
    for (int i=0; i<size; i++) {
        randomNumber = rand()%(5*m) + 1;
        start = clock();
        table->insert(randomNumber);
        time += (clock()-start)/(double)(CLOCKS_PER_SEC/1000);
    }
}

// Measure time that take to find or not find @size random numbers into hash tables
template <class T>
void timeFoundNotFound (int m, int size, int seed, T *table, double &timeFound, double &timeNotFound) {
    clock_t start = 0;
    int randomNumber = 0;
    srand(seed);
    for (int i=0; i<size; i++) {
        randomNumber = rand()%(5*m) + 1;
        start = clock();
        table->deletemin();
        timeFound += (clock()-start)/(double)(CLOCKS_PER_SEC/1000);
//        if (table->deletemin() == true) {
//            timeFound += (clock()-start)/(double)(CLOCKS_PER_SEC/1000);
////            std::cout << "\n " << timeFound;
//        } else {
//            timeNotFound += (clock()-start)/(double)(CLOCKS_PER_SEC/1000);
//            std::cout << "\n " << timeNotFound;
//        }
    }
}
int main(int argc, char **argv) {

    BST *tableBST = nullptr;
    MinHeap *tableMin = nullptr;
    MaxHeap *tableMax = nullptr;

    int m = 11; // table size
    int k = 4;
    int p = 5;
    int key = -1;

    // User interacation
    int BSToice = -1;

    while (BSToice != 3) {
        std::cout << "\n............................................\n\n";
        std::cout << "Please BSToose one of the following commands:\n\n";
        std::cout << "1- Test Hash Tables\n\n";
        std::cout << "2- Peformance Comparison\n\n";
        std::cout << "3- Exit\n\n";

        std::cout << "> ";
        std::cin >> BSToice;

        switch (BSToice) {
            case 1:
            {
                std::cout << "File for testing your hash table correctness:\n";
                std::cout << "data.txt elements: 16 17 29 11 88 14 25\n";

                BST *tableBST = new BST();
                MinHeap *tableMin = new MinHeap();
                MaxHeap *tableMax = new MaxHeap();;

                std::ifstream inputFile;
                inputFile.open(argv[1]);
                if (!inputFile) {
                    std::cout << "Error reading the input file.\n";
                    inputFile.close();
                } else {
                    BST *tableBST = new BST();
                    MinHeap *tableMin = new MinHeap();
                    MaxHeap *tableMax = new MaxHeap();;
                    while(inputFile >> key) {
                        tableBST->insert(key);
                        tableMin->insert(key);
                        tableMax->insert(key);
                    }
                }
                inputFile.close();

                // tableBST->print();
                // tableMin->print();
                // tableMax->print();

                delete tableBST;
                delete tableMax;
                delete tableMin;

            }
            break;
            case 2:
            {

                // int m = 1000003; // table size
                // int k = 20;
                // int p = 997;

                int size = 0;
                int seed = 0;
                std::cout << "Peformance Comparison: (takes a while to genetate results)\n\n";

                // tableBST  = new BST();
                // tableMin = new MinHeap();
                // tableMax = new MinHeap();

                // timeForHashTable[seed][0-buildTime, 1-foundTime, 2-notFoundTime][mult][run5times]
                double timesBST[5][3][5][5] = {};
                double timesMin[5][3][5][5] = {};
                double timesMax[5][3][5][5] = {};

                // timeAccumulatedUsingDifferentSeeds[0-buildTime, 1-foundTime, 2-notFoundTime][mult][run5times]
                double accSeedsBST[3][5][5] = {};
                double accSeedsMin[3][5][5] = {};
                double accSeedsMax[3][5][5] = {};

                // timeAverageUsingDifferentSeeds[0-buildTime, 1-foundTime, 2-notFoundTime][mult][5times]
                double aveSeedsBST[3][5][5] = {};
                double aveSeedsMin[3][5][5] = {};
                double aveSeedsMax[3][5][5] = {};

                // timeRunAll5times[0-buildTime, 1-foundTime, 2-notFoundTime][sizeMultiplier]
                double acc5timesBST[3][5] = {};
                double acc5timesMin[3][5] = {};
                double acc5timesMax[3][5] = {};

                // timeAverageUsingDifferentDataSizes[0-buildTime, 1-foundTime, 2-notFoundTime][sizeMultiplier]
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
                            // HT with BSTaining
                            insertTime(m, size, seed, tableBST, timesBST[seed][0][mult][times]);
                            // HT with quadratic probing
                            insertTime(m, size, seed, tableMin, timesMin[seed][0][mult][times]);
                            // HT with double hashing
                            insertTime(m, size, seed, tableMax, timesMax[seed][0][mult][times]);

                            // Accumulate times for diffrent seeds
                            accSeedsBST[0][mult][times] += timesBST[seed][0][mult][times];
                            accSeedsMin[0][mult][times] += timesMin[seed][0][mult][times];
                            accSeedsMax[0][mult][times] += timesMax[seed][0][mult][times];

                            size = 0.01 * m;
                            // Measure found time and not found time
                            // HT with BSTaining
                            timeFoundNotFound(m, size, seed, tableBST, timesBST[seed][1][mult][times], timesBST[seed][2][mult][times]);
                            // HT with quadratic probing
                            timeFoundNotFound(m, size, seed, tableMin, timesMin[seed][1][mult][times], timesMin[seed][2][mult][times]);
                            // HT with double hashing
                            timeFoundNotFound(m, size, seed, tableMax, timesMax[seed][1][mult][times], timesMax[seed][2][mult][times]);

                            // Accumulate times for diffrent seeds
                            accSeedsBST[1][mult][times] += timesBST[seed][1][mult][times];
                            accSeedsMin[1][mult][times] += timesMin[seed][1][mult][times];
                            accSeedsMax[1][mult][times] += timesMax[seed][1][mult][times];

                            accSeedsBST[2][mult][times] += timesBST[seed][2][mult][times];
                            accSeedsMin[2][mult][times] += timesMin[seed][2][mult][times];
                            accSeedsMax[2][mult][times] += timesMax[seed][2][mult][times];
                        }

                        // Averages for diffrent seeds
                        aveSeedsBST[0][mult][times] = accSeedsBST[0][mult][times] / 5.0;
                        aveSeedsMin[0][mult][times] = accSeedsMin[0][mult][times] / 5.0;
                        aveSeedsMax[0][mult][times] = accSeedsMax[0][mult][times] / 5.0;

                        aveSeedsBST[1][mult][times] = accSeedsBST[1][mult][times] / 5.0;
                        aveSeedsMin[1][mult][times] = accSeedsMin[1][mult][times] / 5.0;
                        aveSeedsMax[1][mult][times] = accSeedsMax[1][mult][times] / 5.0;

                        aveSeedsBST[2][mult][times] = accSeedsBST[2][mult][times] / 5.0;
                        aveSeedsMin[2][mult][times] = accSeedsMin[2][mult][times] / 5.0;
                        aveSeedsMax[2][mult][times] = accSeedsMax[2][mult][times] / 5.0;

                        // Accumulate data for 5 times
                        acc5timesBST[0][mult] += aveSeedsBST[0][mult][times];
                        acc5timesBST[1][mult] += aveSeedsBST[1][mult][times];
                        acc5timesBST[2][mult] += aveSeedsBST[2][mult][times];

                        acc5timesMin[0][mult] += aveSeedsMin[0][mult][times];
                        acc5timesMin[1][mult] += aveSeedsMin[1][mult][times];
                        acc5timesMin[2][mult] += aveSeedsMin[2][mult][times];

                        acc5timesMax[0][mult] += aveSeedsMax[0][mult][times];
                        acc5timesMax[1][mult] += aveSeedsMax[1][mult][times];
                        acc5timesMax[2][mult] += aveSeedsMax[2][mult][times];
                    }

                    // Average times for 5 times
                    for (int mult2=0; mult2<5; mult2++) {
                        ave5timesBST[0][mult2] = acc5timesBST[0][mult2] / 5.0;
                        ave5timesBST[1][mult2] = acc5timesBST[1][mult2] / 5.0;
                        ave5timesBST[2][mult2] = acc5timesBST[2][mult2] / 5.0;

                        ave5timesMin[0][mult2] = acc5timesMin[0][mult2] / 5.0;
                        ave5timesMin[1][mult2] = acc5timesMin[1][mult2] / 5.0;
                        ave5timesMin[2][mult2] = acc5timesMin[2][mult2] / 5.0;

                        ave5timesMax[0][mult2] = acc5timesMax[0][mult2] / 5.0;
                        ave5timesMax[1][mult2] = acc5timesMax[1][mult2] / 5.0;
                        ave5timesMax[2][mult2] = acc5timesMax[2][mult2] / 5.0;
                    }

                }
                // Print preformance tables
                std::cout << "\n\nPerformance (Open Hashing) in milliseconds:\n";
                std::cout << "         " << std::setw(9) << "100,000" << std::setw(9) <<  "200,000" << std::setw(9)
                <<  "300,000" << std::setw(9) <<  "400,000" << std::setw(9) <<  "500,000\n";
                std::cout << "Build    ";
                for (int size=0; size<5; size++) { std::cout  << std::fixed << std::setw(9) << std::setprecision(2) << ave5timesBST[0][size]; }
                std::cout << "\n";
                std::cout << "Found    ";
                for (int size=0; size<5; size++) { std::cout  << std::fixed << std::setw(9) << std::setprecision(2) << ave5timesBST[1][size]; }
                std::cout << "\n";
                std::cout << "Not Found";
                for (int size=0; size<5; size++) { std::cout  << std::fixed << std::setw(9) << std::setprecision(2) << ave5timesBST[2][size]; }
                std::cout << "\n";

                std::cout << "\nPerformance (Quadratic Probing) in milliseconds::\n";
                std::cout << "         " << std::setw(9) << "100,000" << std::setw(9) <<  "200,000" << std::setw(9)
                <<  "300,000" << std::setw(9) <<  "400,000" << std::setw(9) <<  "500,000\n";
                std::cout << "Build    ";
                for (int size=0; size<5; size++) { std::cout << std::setw(9) << std::setprecision(2) << ave5timesMin[0][size]; }
                std::cout << "\n";
                std::cout << "Found    ";
                for (int size=0; size<5; size++) { std::cout << std::setw(9) << std::setprecision(2) << ave5timesMin[1][size]; }
                std::cout << "\n";
                std::cout << "Not Found";
                for (int size=0; size<5; size++) { std::cout << std::setw(9) << std::setprecision(2) << ave5timesMin[2][size]; }
                std::cout << "\n";

                std::cout << "\nPerformance (Double Hashing) in milliseconds::\n";
                std::cout << "         " << std::setw(9) << "100,000" << std::setw(9) <<  "200,000" << std::setw(9)
                <<  "300,000" << std::setw(9) <<  "400,000" << std::setw(9) <<  "500,000\n";
                std::cout << "Build    ";
                for (int size=0; size<5; size++) { std::cout << std::setw(9) << std::setprecision(2) << ave5timesMax[0][size]; }
                std::cout << "\n";
                std::cout << "Found    ";
                for (int size=0; size<5; size++) { std::cout << std::setw(9) << std::setprecision(2) << ave5timesMax[1][size]; }
                std::cout << "\n";
                std::cout << "Not Found";
                for (int size=0; size<5; size++) { std::cout << std::setw(9) << std::setprecision(2) << ave5timesMax[2][size]; }
                std::cout << "\n";
            }

            break;
            case 3:
            std::cout << "Bye bye!\n";
            break;
            default:
            std::cout << "\nError: Wrong input.\n\n";
        }
    }
    
    // delete tableBST;
    // delete tableMax;
    // delete tableMin;
    return (0);
}
