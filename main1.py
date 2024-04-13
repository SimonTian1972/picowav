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

# Parameters
fs = 1000               # Sampling frequency
T = 0.2                 # Width of the rectangular pulse in seconds
gap_duration = 0.1      # Gap duration between pulses
num_pulses = 10          # Number of rectangular pulses
duration = num_pulses * (T + gap_duration)

# Generate the time series with rectangular pulses and gaps
t = np.linspace(0, duration, int(fs * duration), endpoint=False)
x = np.zeros_like(t)
for i in range(num_pulses):
    x[np.logical_and(t >= i * (T + gap_duration), t < i * (T + gap_duration)+T)] = 1

# Compute the FFT of the rectangular pulse signal
X = np.fft.fftshift(np.fft.fft(x))
freq = np.fft.fftshift(np.fft.fftfreq(len(x), d=1/fs))

# Plot the rectangular pulse signal and its FFT
plt.figure(figsize=(10, 6))

plt.subplot(2, 1, 1)
plt.plot(t, x, 'k')
plt.title('Repeating Rectangular Pulses with Gap')
plt.xlabel('Time (s)')
plt.ylabel('Amplitude')

plt.subplot(2, 1, 2)
plt.plot(freq, np.abs(X) / len(x), 'r')
plt.title('Magnitude of FFT')
plt.xlabel('Frequency (Hz)')
plt.ylabel('Magnitude |X(f)|')

plt.tight_layout()
plt.show()



# Compute the autocorrelation of the rectangular pulse signal
def estimated_autocorrelation(x):
    n = len(x)
    variance = x.var()
    x = x - x.mean()
    r = np.correlate(x, x, mode='full')[-n:]
    result = r / (variance * (np.arange(n, 0, -1)))
    return result

# Plot the autocorrelation
plt.figure(figsize=(10, 4))
plt.plot(t, estimated_autocorrelation(x), 'b')
plt.title('Estimated Autocorrelation of Rectangular Pulse Signal')
plt.xlabel('Time Lag (s)')
plt.ylabel('Autocorrelation')
plt.grid(True)
plt.show()


