#ifndef MYUTILS
#define MYUTILS

#include <iostream>
#include <stdexcept>
#include <map>
#include <vector>

using namespace std;

std::vector<std::tuple<int, std::string, int, int>> read_simulation_csv(const string path);

// helpers
bool fileExists(const std::string &str);

#endif // MYUTILS