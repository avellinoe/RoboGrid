#include "utilities.h"

#include <math.h>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

using namespace std;

bool debug = false;

std::vector<std::tuple<int, std::string, int, int>> read_simulation_csv(const string path) {
    
    std::ifstream file (path);

    int row_iterator = 0, col_iterator = 0;

    if (!fileExists(path)) {
        throw std::runtime_error("File does not exist.");
    }
    if (path.empty()) {  /* no argument given, error show usage */
        throw std::runtime_error("error: insufficient input. <filename> required.\n");
    }

    /********************************************************/
    std::string row_line, value;

    /* First run thru file to get rows and columns */
    if (file.is_open()) {
        while (file.good()) {
            while (std::getline (file, row_line)) {
                std::stringstream line;
                line.str(row_line);
                col_iterator = 0;
                while (std::getline (line, value, ',')) {
                    col_iterator++;
                }
                row_iterator++;
            }
        //End of file
        }
        file.close();
    }

    /* Create placeholder variables to store data from csv */
    int entry; std::string command; int xcoord; int ycoord;

    /* Create a tuple to store data from csv (entry, command, x, y) */
    std::vector<std::tuple<int, std::string, int, int>> data;
    
    /* Run thru the file once more to read values */
    row_iterator = 0; // Reset row_iterator
    std::ifstream fileRead (path);
    if (fileRead.is_open()) {
        while (fileRead.good()) {
            while (std::getline (fileRead, row_line)) {
                std::stringstream line;
                line.str(row_line);
                col_iterator = 0;
                std::tuple<int, std::string, int, int> data_tuple;
                while (std::getline (line, value, ',')) {
                    try {
                        switch (col_iterator) {
                            case 0: entry = (std::stoi(value)); break;
                            case 1: command = value; break;
                            case 2: xcoord = (std::stoi(value)); break;
                            case 3: ycoord = (std::stoi(value)); break;
                        }
                        col_iterator++;
                    } catch (const std::exception& e) { // caught by reference to base
                        std::cout << "Incorrect format of csv data in row " << row_iterator
                                << ", column " << col_iterator << " with message: " 
                                << e.what() << "'\n";
                    }
                }
                get<0>(data_tuple) = entry;
                get<1>(data_tuple) = command;
                get<2>(data_tuple) = xcoord;
                get<3>(data_tuple) = ycoord;
                data.push_back(data_tuple);
                row_iterator++;
            }
        // End of file
        }
        file.close();
    }
    
    // Quick check by printing commands
    if (debug) {
        for (int i = 0; i < data.size(); i++) {
                std::cout << "Entry: " << get<0>(data[i])
                        << "Command: " << get<1>(data[i])
                        << "X-Coord: " << get<2>(data[i])
                        << "Y-Coord: " << get<3>(data[i]) << "\n";
        }
    }
    
    return data;
}

bool fileExists(const std::string &str) {
    if (FILE *file = fopen(str.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}