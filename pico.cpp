
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;


//from  https://cse.usf.edu/~kchriste/tools/autoc.c
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

#include <cmath>
#ifndef M_PI
#define M_PI (3.14159265358979323846) // Define M_PI if not already defined
#endif
// Function to calculate the Discrete Fourier Transform (DFT) of a signal X
void DFT(const double X[], int N, double frequencies[], double amplitudes[]) {
    for (int k = 0; k < N; ++k) {
        double re = 0.0;
        double im = 0.0;
        for (int n = 0; n < N; ++n) {
            double angle = 2.0 * M_PI * k * n / N;
            re += X[n] * cos(angle);
            im -= X[n] * sin(angle); // negative sign for forward transform
        }
        frequencies[k] = k;
        amplitudes[k] = sqrt(re * re + im * im);
    }
}

// Function to find the index of the maximum amplitude in an array
int findMaxAmplitudeIndex(const double amplitudes[], int N) {
    int maxIndex = 1;
    double maxAmplitude = amplitudes[1];
    for (int i = 2; i < N/2; ++i) {
        if (amplitudes[i] > maxAmplitude) {
            maxAmplitude = amplitudes[i];
            maxIndex = i;
        }
    }
    return maxIndex;
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
        double firstPeakAcv = 0;
        int firstPeaklag = 0;
        autocvs.clear();
        autocvs.push_back(0); //  zero lag
        for (int lag = 1; lag < N*3/4; lag++) {
            double autocv = compute_autoc(lag, volts.data(), N, mean, var);
            if (autocv > maxAutocv) {
                lagSave = lag;
                maxAutocv = autocv;
            }
            autocvs.push_back(autocv);
        }

        for (int lag = 2; lag < N * 3 / 4-1; lag++) {
            if (autocvs[lag] > maxAutocv * 0.8) {
                if (autocvs[lag] > autocvs[lag - 1] && autocvs[lag] > autocvs[lag + 1]) {
                    firstPeaklag = lag;
                    firstPeakAcv = autocvs[lag];
                    break;
                }
            }
        }


        //std::cout << file << " lag = " << lagSave << "first = " << firstPeaklag  <<  std::endl;
        double diff = abs(firstPeakAcv - maxAutocv) / ((firstPeakAcv + maxAutocv) / 2);
        //std::cout << "diff in percentage" << diff << std::endl;
        if (diff > 0.1) {
            std::cout << file << " possible error 1 " << std::endl; // Wave223.csv
        }

        std::vector<double> frequencies(N, 0);
        std::vector<double> amplitudes(N, 0);

        // Calculate the DFT of the signal
        DFT(volts.data(), N, frequencies.data(), amplitudes.data());

        // Find the index of the maximum amplitude
        int maxAmplitudeIndex = findMaxAmplitudeIndex(amplitudes.data(), N);
        int period = N / frequencies[maxAmplitudeIndex];
        std::cout << "period= " << period << " firstPeaklag= " << firstPeaklag << std::endl;
        if (abs(period - firstPeaklag) > 4) {
            std::cout << file <<  " possible error 2" << std::endl; // Wave223.csv
        }

    }
    return 0;
}
