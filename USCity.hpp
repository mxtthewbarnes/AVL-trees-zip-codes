#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <list>
#include "avl_map.hpp"

using namespace std;

class USCity {
public:
    string city;
    string state;
    string county;

//          Default Constructor
//------------------------------------------------
    USCity() : city(""), state(""), county("") {}

//          Parameterized Constructor
//-------------------------------------------------
    USCity(const string& c, const string& s, const string& cn) 
    : city(c), state(s), county(cn) {}
};





//parseCSV() parses uszips.csv and populates both the avl_map and the std::map
//1) opens the csv, reads line by line, extracts zip codes and state/city/county info
//2) removes quotes and checks for valid zip
//3) converts zip to int and skips invalid entries 
inline void parseCSV(const string& filename, avl_map<int, USCity>& avlTree, map<int, USCity>& stdMap, list<int>& zipList) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << "file could not be opened" << endl;
        return;
    }

    //skipping the header line as its invalid info 
    string line;
    getline(file, line); 

    while (getline(file, line)) {
        stringstream ss(line);
        string stringZip, latitude, longitude, city, state, stateName, county;

        getline(ss, stringZip, ',');
        getline(ss, latitude, ',');
        getline(ss, longitude, ',');
        getline(ss, city, ',');
        getline(ss, state, ',');
        getline(ss, stateName, ',');
        getline(ss, county, ',');

        for (int i = 0; i < stringZip.size(); i++) {
            if (stringZip[i] == '"') {
                stringZip.erase(i, 1);
                i--;
            }
        }
        for (int i = 0; i < city.size(); i++) {
            if (city[i] == '"') {
                city.erase(i, 1);
                i--;
            }
        }
        for (int i = 0; i < state.size(); i++) {
            if (state[i] == '"') {
                state.erase(i, 1);
                i--;
            }
        }
        for (int i = 0; i < county.size(); i++) {
            if (county[i] == '"') {
                county.erase(i, 1);
                i--;
            }
        }

        //checks if stringZip is empty
        if (stringZip == "") {
            cout << "zip code missing." << endl;
            continue;
        }
        if (city == "") {
            cout << "zip code missing." << endl;
            continue;
        }
        if (state == "") {
            cout << "zip code missing." << endl;
            continue;
        }
        if (county == "") {
            cout << "zip code missing." << endl;
            continue;
        }

        
        bool validZip = true;
        for (int i = 0; i < stringZip.length(); i++) {
            if (stringZip[i] < '0' || stringZip[i] > '9') {
                validZip = false;
                break;
            }
        }

        if (!validZip) {
            cout << "skipping invalid zipcode: " << stringZip << endl;
            continue;
        }

        //stoi() converts zip into int
        int zip = 0;
        try {
            zip = stoi(stringZip);
        } catch (exception& e) {
            cout << "zip conversion failed for: " << stringZip << endl;
            continue;
        }

        //inserts into data structure
        USCity usCity(city, state, county);
        avlTree.insert(zip, usCity);
        stdMap[zip] = usCity;
        zipList.push_back(zip);
    }

    file.close();
}