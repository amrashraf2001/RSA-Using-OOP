import matplotlib
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import sys
from subprocess import run, call, Popen, PIPE
import os
from tqdm import tqdm
from time import time, sleep
from helpers import *


FirstPrimes_limit = int(sys.argv[1])





primesList = pd.read_csv('1m.csv').iloc[:, 1]
print(primesList.head())

primesList = primesList.iloc[:-1]


Keys_dict = []


for i in range(0, len(primesList), 2):
    p = primesList.iloc[i]
    q = primesList.iloc[i+1]
    n = p*q
    length = len(bin(n)[2:])

    e = Calc_e(p, q)
   
    Keys_dict.append((p,q,e,n,length))


BreakTimes = []
KeyLengths = []


for key_to_be_broken in tqdm(Keys_dict[:FirstPrimes_limit], desc='Brute Forcing different Key Lengths'):


    initial_n = key_to_be_broken[3]
    initial_length = key_to_be_broken[4]
    KeyLengths.append(initial_length)

    startTime = time()*1000

    

    #Generate prime list till the max number 2^(number of bits of n)
    primesList = constructPrimeList(initial_n)

    found = False
    for i in range(0, len(primesList)):
        for j in range(0, len(primesList)):
            if primesList[i] * primesList[j] == initial_n:
                found = True
                p = primesList[i]
                q = primesList[j]
                break
        
        if(found):
            break
    
    if(found):
        phi = (p-1) * (q-1)
        d = modInverse(e, phi)
    endTime = time()*1000

    BreakTimes.append(endTime-startTime)



#this is just to take the average time of numbers having the same key length

graph_data = {}

for i,j in zip(KeyLengths, BreakTimes):
    if i in graph_data.keys():
        graph_data[i] = (graph_data[i] + j) / 2
    else:
        graph_data[i] = j



plt.plot(graph_data.keys(), graph_data.values())
plt.xlabel("Key length in bits")
plt.ylabel("Brute Force time in ms")
plt.title('Brute Force Time vs Key length')
plt.legend()
plt.savefig('BFTime.png')
plt.show()