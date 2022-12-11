/**
 * @file utilities.cpp
 * 
 * Implementation of utilities.h
 * 
 * @author Marcel Hoang
 * @author Adriana Shuaipaj
 * @author Anna Polski
 * @author Michelle Zhang
 * 
 * @date Fall 2022
*/
#include "utilities.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

vector<string> utilities::GetSubstrs(const string& str,
                                               char delimiter, char escape) {
  size_t last = 0;
  std::vector<string> substrs;
  bool esc = false;
  for (size_t i = 0; i != str.length(); ++i) {
    if (str.at(i) == escape && !esc) {
      esc = true;
    } else if (str.at(i) == escape && esc) {
      esc = false;
    }
    if (str.at(i) == delimiter && !esc) {
      string substr = str.substr(last, i - last);
      last = i + 1;
      substrs.push_back(substr);
    }
  }
  string substr = str.substr(last, str.length() - last);
  substrs.push_back(substr);

  return substrs;
}

void utilities::datasetCleaning(string filename) {
    std::ofstream cleaned("cleaned_dataset.csv");
    cleaned << "incidentID,totDeadMissing,totalMigrants,xCoord,yCoord" << std::endl;
    std::ifstream ifs{filename};
    for (string line; getline(ifs, line); line = "") {
        vector<string> vec = utilities::GetSubstrs(line, ',', '"');
        if (vec[0] != "\"Main ID\"") {
            int dead_missing;
            int survivors;
            vector<string> coords = utilities::GetSubstrs(vec[16], ',', '!');
            string xcord = coords[0].substr(1, coords[0].size() - 1);
            string ycord = coords[1].substr(1, coords[1].size() - 2);
            if (vec[8] == "") {
                dead_missing = 0;
            } else  dead_missing = stoi(vec[8]);
            if (vec[9] == "") {
                survivors = 0;
            }   else survivors = stoi(vec[9]);

            cleaned << vec[1] << "," << dead_missing << "," << (dead_missing + survivors) << "," << xcord << "," << ycord << std::endl;
        }
    }
    cleaned.close();
}