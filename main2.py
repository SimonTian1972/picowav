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

import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file
#data = pd.read_csv('Wave100.csv')
data = pd.read_csv('Wave167.csv')

# Extract the 'Seconds' and 'Volts' columns
#seconds = data['Seconds']

volts = data['Volts']
seconds = [i for i in range(len(volts))]

# Plot the data
plt.plot(seconds, volts)
plt.xlabel('Time (Seconds)')
plt.ylabel('Volts')
plt.title('Voltage vs Time')
plt.grid(True)
plt.show()
