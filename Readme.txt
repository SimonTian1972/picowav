Pico.cpp is the solution to the requirement. (C++17 or higher compiler is needed) 
The main idea is to calculate the autocorrelation values (ACV) for different lags.
The lag of the first peak in ACV after lag == 0 is regarded as the period of the highest amplitude wave in a file. (FFT can be used to double check it)

Usage:  put pico.exe file in the same directory as the directory of Wave*.csv files, type "pico.exe" to run it.
The name of output file is : fileFreq.csv 