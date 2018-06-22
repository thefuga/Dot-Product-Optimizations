import numpy as np
import pandas as pd
import os
import csv

def analyze_results(path):

    directory = os.fsencode(path)
    results_table = open(path + "results.csv", "w")
    results_table.write("Version,Samples,Mean,Standard Deviation\n")
    for file in os.listdir(directory):
        filename = os.fsdecode(file)
        if filename.endswith(".csv") and not (filename=="results.csv") :
            data = pd.read_csv(path + filename)
            data = data.as_matrix()
            data = np.array(data)
            results_table.write(filename + "," + str(len(data)) + "," + str(np.mean(data[:,1])) + "," + str(np.std(data[:,1])) + "\n")

    results_table.close()

analyze_results('D:/Git Repositories/Dot-Product-Optimizations/')
