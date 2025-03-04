#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <random>
#include <chrono>
#include "avl_map.hpp"
#include "USCity.hpp"

using namespace std;
using namespace chrono;

int main() {
    avl_map<int, USCity> avlTree;
    map<int, USCity> stdMap;
    list<int> zipList;

    parseCSV("uszips.csv", avlTree, stdMap, zipList);

    cout << "\n===============================" << endl;
    cout << "|| Finished parsing uszips.csv" << endl;
    cout << "|| Inserted: " << zipList.size() << " entries" << endl;
    cout << "===============================\n" << endl;

    // Convert zipList to vector for random selection
    vector<int> zipVector(zipList.begin(), zipList.end());

    // Shuffle ZIP codes
    random_device rd;
    mt19937 gen(rd());
    shuffle(zipVector.begin(), zipVector.end(), gen);

    // Select first 1000 shuffled ZIP codes
    vector<int> testZips(zipVector.begin(), zipVector.begin() + min(1000, (int)zipVector.size()));

    // Benchmark Lookup Performance
    auto start = high_resolution_clock::now();
    for (int zip : testZips) {
        avlTree.find(zip);
    }
    auto end = high_resolution_clock::now();
    auto avlTime = duration_cast<microseconds>(end - start).count();

    start = high_resolution_clock::now();
    for (int zip : testZips) {
        stdMap.find(zip);
    }
    end = high_resolution_clock::now();
    auto stdMapTime = duration_cast<microseconds>(end - start).count();

    cout << "\nLookup Benchmark Results:\n";
    cout << "AVL Tree Lookup Time: " << avlTime << " microseconds\n";
    cout << "std::map Lookup Time: " << stdMapTime << " microseconds\n";

    return 0;
}