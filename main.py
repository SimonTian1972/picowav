# This is a sample Python script.
from typing import Optional

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.


# numpy to torch with .from_numpy(x)
import numpy as np



import torch

# !/bin/python3

import math
import os
import random
import re
import sys


#
# Complete the 'largestRectangle' function below.
#
# The function is expected to return a LONG_INTEGER.
# The function accepts INTEGER_ARRAY h as parameter.
import tracemalloc


# code or function for which memory
# has to be monitored

# importing libraries
import os
import psutil

import pandas as pd
import os
import matplotlib.pyplot as plt

import pandas as pd
import os



import numpy as np
import matplotlib.pyplot as plt


import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# Load data from CSV (assuming 'my.csv' contains 'Seconds' and 'Volts' columns)
data = pd.read_csv('Wave410.csv')
seconds = data['Seconds']
volts = data['Volts']

# Compute the autocorrelation of the signal
def estimated_autocorrelation(x):
    n = len(x)
    variance = x.var()
    x = x - x.mean()
    r = np.correlate(x, x, mode='full')[-n:]
    result = r / (variance * (np.arange(n, 0, -1)))
    return result

# Compute the FFT of the signal for PSD
fs = 1 / (seconds[1] - seconds[0])  # Sampling frequency
X = np.fft.fftshift(np.fft.fft(volts))
freq = np.fft.fftshift(np.fft.fftfreq(len(volts), d=1/fs))

# Plot the results
plt.figure(figsize=(10, 6))

# Autocorrelation
plt.subplot(3, 1, 1)
plt.plot(seconds, estimated_autocorrelation(volts), 'b')
plt.title('Estimated Autocorrelation')
plt.xlabel('Time Lag (s)')
plt.ylabel('Autocorrelation')
plt.grid(True)

plt.subplot(3, 1, 3)
plt.plot(seconds, volts, 'b')
plt.title('input')
plt.xlabel('Time Lag (s)')
plt.ylabel('input')

# Power Spectral Density (PSD)
plt.subplot(3, 1, 2)
plt.psd(volts, NFFT=len(volts), Fs=fs, pad_to=len(volts))
plt.title('Power Spectral Density (PSD)')
plt.xlabel('Frequency (Hz)')
plt.ylabel('Power/Frequency (dB/Hz)')

plt.tight_layout()
plt.show()
