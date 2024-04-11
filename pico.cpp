
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

// Define a struct to store data
struct CsvData {
    double seconds;
    double volts;
};

// Define a function to read data from a CSV file
std::vector<CsvData> readCsvFile(const std::string& filePath) {
    std::vector<CsvData> data;
    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        CsvData row;
        iss >> row.seconds >> row.volts;
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
            std::cout << entry.path().string() << std::endl;
        }
    }
    return csvFiles;
}

int main() {
    std::vector<std::string> csvFiles = getCsvFiles();

    for (const auto& file : csvFiles) {
        std::vector<CsvData> fileData = readCsvFile(file);
        std::cout << "Data from " << file << ":\n";
        for (const auto& row : fileData) {
            std::cout << "Seconds: " << row.seconds << ", Volts: " << row.volts << "\n";
        }
        std::cout << "\n";
    }

    return 0;
}
