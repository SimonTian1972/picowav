
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;



//===========================================================================
//=  Function to compute mean for a series X                                =
//===========================================================================
double compute_mean(const double X[], int N)
{
    double   mean;        // Computed mean value to be returned
    int      i;           // Loop counter

    // Loop to compute mean
    mean = 0.0;
    for (i = 0; i < N; i++)
        mean = mean + (X[i] / N);

    return(mean);
}

//===========================================================================
//=  Function to compute variance for a series X                            =
//===========================================================================
double compute_variance(const double X[], int N, double Mean)
{
    double   var;         // Computed variance value to be returned
    int      i;           // Loop counter

    // Loop to compute variance
    var = 0.0;
    for (i = 0; i < N; i++)
        var = var + (pow((X[i] - Mean), 2.0) / N);

    return(var);
}

//===========================================================================
//=  Function to compute autocorrelation for a series X                     =
//=   - Corrected divide by N to divide (N - lag) from Tobias Mueller       =
//===========================================================================
double compute_autoc(int lag, const double X[], int N, double Mean, double Variance)
{
    double   autocv;      // Autocovariance value
    double   ac_value;    // Computed autocorrelation value to be returned
    int      i;           // Loop counter

    // Loop to compute autovariance
    autocv = 0.0;
    for (i = 0; i < (N - lag); i++)
        autocv = autocv + ((X[i] - Mean) * (X[i + lag] - Mean));
    autocv = (1.0 / (N - lag)) * autocv;

    // Autocorrelation is autocovariance divided by variance
    ac_value = autocv / Variance;

    return(ac_value);
}

// Define a function to read data from a CSV file
void readCsvFile(const std::string& filePath, std::vector<double>& seconds, std::vector<double>& volts) {
    std::ifstream file(filePath);
    std::string line;

    std::getline(file, line); // Skip first line
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        double s, v;
        iss >> s;
        iss.ignore(1, ',');
        iss >> v;
        seconds.push_back(s);
        volts.push_back(v);
    }
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
    std::vector<double> seconds;
    std::vector<double> volts;
    std::vector<double> autocvs;
    for (const auto& file : csvFiles) {
        seconds.clear();
        volts.clear();
        readCsvFile(file, seconds, volts);
        int N = volts.size();
        double mean = compute_mean(volts.data(), N);
        double var = compute_variance(volts.data(), N, mean);
        double maxAutocv = 0;
        int lagSave = 0;
        autocvs.clear();
        for (int lag = 1; lag < N; lag++) {
            double autocv = compute_autoc(lag, volts.data(), N, mean, var);
            if (autocv > maxAutocv) {
                lagSave = lag;
                maxAutocv = autocv;
            }
            autocvs.push_back(autocv);
        }
        std::cout << file << " lag = " << lagSave << std::endl;
    }
    return 0;
}
