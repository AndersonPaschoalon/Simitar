import numpy as np
import csv

class Csv(object):
    @staticmethod
    def load_csv(datafile=''):
        """
        Load float CSV file into a matrix.
        mtr_float = load_csv(datafile='file.csv')
        :param datafile: CSV file to be loaded
        :return: matrix with the CSV file data
        """
        with open(datafile) as f:
            lines = (line for line in f if not line.startswith('#'))
            csv_matrix = np.loadtxt(lines, delimiter=',')
        return csv_matrix

    @staticmethod
    def load_csv_str(datafile=''):
        """
        Load a String CSV file into a matrix
        :param datafile:
        :return: string matrix with CSV data
        mtr_str = load_csv_str(datafile='file.csv')
        """
        ifile = open(datafile, "rU")
        reader = csv.reader(ifile, delimiter=",")
        rownum = 0
        a = []
        for row in reader:
            if(len(row)==0 or row[0][0]=='#'):
                continue
            for index in range(0, len(row)-1):
                row[index] = row[index].strip()
            a.append(row)
            rownum += 1
        ifile.close()
        return a


