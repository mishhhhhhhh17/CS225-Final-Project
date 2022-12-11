/**
 * @file utilities.h
 * 
 * Non-Graph class helper functions for handling the dataset
 * 
 * @author Marcel Hoang
 * @author Adriana Shuaipaj
 * @author Anna Polski
 * @author Michelle Zhang
 * 
 * @date Fall 2022
*/
#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace utilities {
  vector<string> GetSubstrs(const string& str, char delimiter, char escape);
  void datasetCleaning(string filename);
}