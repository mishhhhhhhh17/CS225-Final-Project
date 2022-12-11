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