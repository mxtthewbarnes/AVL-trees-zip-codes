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
    //necessary data structuers 
    avl_map<int, USCity> avl;
    map<int, USCity> std;
    list<int> zList;

   
    parseCSV("uszips.csv", avl, std, zList);

    // Print summary of parsed data
    cout << "\n=======================================" << endl;
    cout << "  Parsed uszips.csv" << endl;
    cout << "  Inserted " << zList.size() << " total entries" << endl;
    cout << "=======================================\n" << endl;

    //converting list into vector 
    vector<int> zipVec;
    for (int zip : zList) {
        zipVec.push_back(zip);
    }





    //          Benchmark Lookup performance
    //-----------------------------------------------

    //shuffle zip codes using marsenne twister 19937 algorithm 
    //mt19937 is faster than using rand()
    random_device rd;
    mt19937 gen(rd());
    shuffle(zipVec.begin(), zipVec.end(), gen);

    //selecting first 1000 shuffled zips 
    vector<int> testZips;
    int count = 0;
    for (int zip : zipVec) {
        if (count < 1000) {
            testZips.push_back(zip);
            count++;
        } else {
            break;
        }
    }

    //performance for avl_map
    auto start = high_resolution_clock::now();
    for (int zip : testZips) {
        avl.find(zip);
    }
    auto end = high_resolution_clock::now();
    auto avlTime = duration_cast<microseconds>(end - start).count();

    //performance for std::map
    start = high_resolution_clock::now();
    for (int zip : testZips) {
        std.find(zip);
    }
    end = high_resolution_clock::now();
    auto stdTime = duration_cast<microseconds>(end - start).count();


    int difference; 
    if (avlTime < stdTime)
    {
        difference = (stdTime - avlTime); 
    }
    else{
        difference = (avlTime - stdTime); 
    }
    cout << "\nBenchmark lookup performance results:\n";
    cout << "-------------------------------------" << endl; 
    cout << "avl_map:" << avlTime << " ms\n";
    cout << "std::map:" << stdTime << " ms\n" << endl; 
    if (avlTime < stdTime)
    {
        cout << "avl_map was faster than std::map by : " << difference << "ms" << endl; 
    }
    else{
        cout << "std::map was faster than avl_map by: " << difference << "ms" << endl; 
    }

    return 0;
}