// pico.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>  // For fopen_s

// Define DataPoint struct
struct DataPoint {
    double seconds;
    double volts;
};

// Function to read CSV file
std::vector<DataPoint> readCSV(const std::string& filename) {
    std::vector<DataPoint> dataPoints;
    FILE* file;
    if (fopen_s(&file, filename.c_str(), "r") != 0) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return dataPoints;
    }

    char buffer[256];
    // Skip header line
    if (fgets(buffer, sizeof(buffer), file) == nullptr) {
        std::cerr << "Failed to read header from file: " << filename << std::endl;
        fclose(file);
        return dataPoints;
    }

    while (fgets(buffer, sizeof(buffer), file) != nullptr) {
        std::istringstream iss(buffer);
        std::string token;
        DataPoint point;

        // Read seconds
        if (!std::getline(iss, token, ',')) {
            std::cerr << "Failed to read seconds from file: " << filename << std::endl;
            fclose(file);
            return dataPoints;
        }
        point.seconds = std::stod(token);

        // Read volts
        if (!std::getline(iss, token, ',')) {
            std::cerr << "Failed to read volts from file: " << filename << std::endl;
            fclose(file);
            return dataPoints;
        }
        point.volts = std::stod(token);

        dataPoints.push_back(point);
    }

    fclose(file);
    return dataPoints;
}

// Function to list CSV files in current directory
std::vector<std::string> listCSVFiles() {
    std::vector<std::string> csvFiles;
    FILE* pipe;
    if (fopen_s(&pipe, "ls *.csv", "r") != 0 || pipe == nullptr) return csvFiles;

    char buffer[128];
    while (!feof(pipe)) {
        if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            csvFiles.push_back(buffer);
        }
    }
    fclose(pipe);

    return csvFiles;
}

// Main function
int main() {
    std::vector<std::string> csvFiles = listCSVFiles();

    // Iterate over CSV files
    for (const auto& filename : csvFiles) {
        // Remove newline character from filename
        std::string trimmedFilename = filename.substr(0, filename.size() - 1);

        // Read data from CSV file
        std::vector<DataPoint> data = readCSV(trimmedFilename);

        // Print data
        std::cout << "File: " << trimmedFilename << std::endl;
        for (const auto& point : data) {
            std::cout << "Seconds: " << point.seconds << ", Volts: " << point.volts << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}

