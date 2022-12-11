#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace utilities {
  vector<string> GetSubstrs(const string& str, char delimiter, char escape);
}