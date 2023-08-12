import matplotlib
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import sys
from subprocess import run, call, Popen, PIPE
import os
from time import time, sleep
from tqdm import tqdm
from helpers import *



UpperLimit = int(sys.argv[1])


# Compile the chat module first

result = run(['g++', os.path.join(os.path.split(os.getcwd())[0], 'Source.cpp'), '-o', os.path.join(os.getcwd(), 'out.exe')], capture_output=True, text=True)
print(result.stdout)


sampleMessage = 'Hello0This0is0a0test0message0just0built0to0mess0with0your0code0muahahahaha'

timeCounter = []
keyLength = []

# enter an upper limit number here
primesList = constructPrimeList(UpperLimit)

#just remove the last prime, if the primes are not pairs
if len(primesList)%2 != 0: primesList = primesList[:-1]




for i in tqdm(range(0, len(primesList), 2), desc='Encrypting using different n'):
    p = primesList[i]
    q = primesList[i+1]
    n = p*q
    keyLength.append(len(bin(n)[2:]))

    with open ('receiver_input.txt', 'w') as l:
        l.write(' '.join([str(p),str(q)]))
    

    startTime = time()*1000
    #call the chat module
    result = run(['out.exe', sampleMessage], capture_output=True, text=True)
    endTime = time()*1000

    timeCounter.append(endTime - startTime)



#print(keyLength)
#print(timeCounter)




#this is just to take the average time of numbers having the same key length

graph_data = {}

for i,j in zip(keyLength, timeCounter):
    if i in graph_data.keys():
        graph_data[i] = (graph_data[i] + j) / 2
    else:
        graph_data[i] = j



plt.plot(graph_data.keys(), graph_data.values())
plt.xlabel("Key length in bits")
plt.ylabel("Encryption time in ms")
plt.title('Encryption Time vs Key length')
plt.legend()
plt.savefig('encTime.png')
plt.show()