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
    string city, state, county;
    USCity() : city(""), state(""), county("") {}
    USCity(const string& c, const string& s, const string& cn) : city(c), state(s), county(cn) {}
};

inline void parseCSV(const string& filename, avl_map<int, USCity>& avlTree, map<int, USCity>& stdMap, list<int>& zipList) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header line

    while (getline(file, line)) {
        stringstream ss(line);
        string zipStr, lat, lng, city, state, stateFull, county;

        getline(ss, zipStr, ',');    // ZIP code (as string)
        getline(ss, lat, ',');       // Latitude (ignored)
        getline(ss, lng, ',');       // Longitude (ignored)
        getline(ss, city, ',');      // City name
        getline(ss, state, ',');     // State abbreviation
        getline(ss, stateFull, ','); // Full state name
        getline(ss, county, ',');    // County name

        // **Remove double quotes from ZIP code and other fields**
        zipStr.erase(remove(zipStr.begin(), zipStr.end(), '"'), zipStr.end());
        city.erase(remove(city.begin(), city.end(), '"'), city.end());
        state.erase(remove(state.begin(), state.end(), '"'), state.end());
        county.erase(remove(county.begin(), county.end(), '"'), county.end());

        // **Ensure ZIP code is valid**
        zipStr.erase(0, zipStr.find_first_not_of(" \t\r\n"));  // Trim leading whitespace
        zipStr.erase(zipStr.find_last_not_of(" \t\r\n") + 1);  // Trim trailing whitespace

        if (zipStr.empty() || city.empty() || state.empty() || county.empty()) {
            cerr << "Warning: Skipping invalid ZIP code entry -> " << zipStr << endl;
            continue;
        }

        // **Convert ZIP code safely**
        try {
            if (all_of(zipStr.begin(), zipStr.end(), ::isdigit)) { // Ensure numeric
                int zip = stoi(zipStr);
                USCity usCity(city, state, county);

                avlTree.insert(zip, usCity);
                stdMap.insert({zip, usCity});
                zipList.push_back(zip);
            } else {
                throw invalid_argument("Non-numeric ZIP code");
            }
        } catch (const exception& e) {
            cerr << "Warning: Skipping invalid ZIP code entry -> " << zipStr << " (Conversion error)\n";
        }
    }

    file.close();
}