#!/usr/bin/python3
"""
calcCostFunctin.py: This script calcs the cost function for each stochatic model.
Take as input the place were the files `Correlation.dat`, `Hurst Exponent.dat`,
and `Mean.dat` are located
"""

#import matplotlib.pyplot as plt
import numpy as np
#import plotly.plotly as py
import sys
import numpy as np
import csv
import re
import tkinter

__author__ = 'Anderson Paschoalon'
__copyright__ = ""
__credits__ = ["Anderson Paschoalon", "Christian Esteve Rothenberg"]
__license__ = "MIT"
__version__ = ""
__maintainer__ = "Anderson Paschoalon"
__email__ = "anderson.paschoalon@gmail.com"
__status__ = "Production"


# command line argument: to de dir data
PATH_DIR = str(sys.argv[1])

class CsvList:
    def load(self, fileName):
        result = []
        reader = csv.reader(open(fileName))
        comment = re.compile('^#.*')  # ignore commentaties
        for row in reader:
            key = row[0].strip()
            res = comment.match(key)
            if res != None:
                continue
            else:
                value = row[1]
                error = row[2]
                listTuple = (key, value, error)
                result.append(listTuple)
        return (result)

# return the position of a key in a tuple
def list_truple_index(tuple_list, key, position):
    retVal = [x for x, y in enumerate(tuple_list) if y[position] == key]
    # return first match found
    return(retVal[0])


CsvL = CsvList()
corr = CsvL.load(PATH_DIR + 'Correlation.dat')
hurst = CsvL.load(PATH_DIR + 'Hurst Exponent.dat')
mean = CsvL.load(PATH_DIR + 'Mean.dat')
hurst_diff = []
mean_diff = []
corr_float = []
costFunction  = []
hurst_original = 0
mean_original = 0

i = 0
# select the original value
for i in range(0, len(hurst)):
    if hurst[i][0] == 'Original':
        hurst_original =  float(hurst[i][1])
    if mean[i][0] == 'Original':
        mean_original = float(mean[i][1])

# Evaluate the difference between the Original and simulated Hust and Mean 
for i in range(0, len(hurst)):
    diffval = 0
    if hurst[i][0] != 'Original':
        hurst_diff.append((hurst[i][0], abs(float(hurst[i][1]) - hurst_original)))
    if mean[i][0] != 'Original':
        mean_diff.append((mean[i][0], abs(float(mean[i][1]) - mean_original)))

# correlation
for i in range(0, len(corr)):
    corr_float.append((corr[i][0], float(corr[i][1])))

# ordered costs, from best to worst (correlation higher to lower, diffs from lower to higher)
corr_float.sort(key=lambda tup: tup[1], reverse=True)
mean_diff.sort(key=lambda tup: tup[1])
hurst_diff.sort(key=lambda tup: tup[1])

print("corr_float=", corr_float)
print("mean_diff=", mean_diff)
print("hurst_diff=", hurst_diff)

# calc the cost function of each model
for i in range(0, len(corr_float)):
    stochasticFunction = corr_float[i][0]
    posCorr = list_truple_index(corr_float, stochasticFunction, 0)
    posMean = list_truple_index(mean_diff, stochasticFunction, 0)
    posHust = list_truple_index(hurst_diff, stochasticFunction, 0)
    costFunction.append((stochasticFunction, posCorr + posMean + posHust))

# save the cost function values into a costFunction.dat file
costFunction.sort(key=lambda tup: tup[1])
np.savetxt(PATH_DIR + 'costFunction.dat', costFunction, delimiter=", ", fmt='%s', header='Metrics cost function')
print("costFunction=", costFunction)

