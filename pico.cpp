// pico.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

// Define a function to read data from a CSV file
std::vector<std::vector<double>> readCsvFile(const std::string& filePath) {
    std::vector<std::vector<double>> data;
    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line)) {
        std::vector<double> row;
        std::istringstream iss(line);
        double value;

        while (iss >> value) {
            row.push_back(value);
            if (iss.peek() == ',') {
                iss.ignore();
            }
        }

        data.push_back(row);
    }

    return data;
}

// Get a list of all CSV files in the current directory
std::vector<std::string> getCsvFiles() {
    std::vector<std::string> csvFiles;
    for (const auto& entry : fs::directory_iterator(".")) {
        if (entry.path().extension() == ".csv") {
            csvFiles.push_back(entry.path().string());
        }
    }
    return csvFiles;
}

int main() {
    std::vector<std::string> csvFiles = getCsvFiles();

    for (const auto& file : csvFiles) {
        std::vector<std::vector<double>> fileData = readCsvFile(file);
        std::cout << "Data from " << file << ":\n";
        for (const auto& row : fileData) {
            for (const auto& value : row) {
                std::cout << value << "\t";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    return 0;
}
