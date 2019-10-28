import numpy as np
import os
import matplotlib.pyplot as plt
import sys

data_dir='data/'

filename=data_dir+'1561216225.dat'
'''
Ch 1 T1,T2: 16297 32612
Ch 2 T1,T2: 32612 0
Ch 3 T1,T2: 0 0
Ch 4 T1,T2: 0 0
'''

ch1=[]
ch2=[]
ch3=[]
ch4=[]

ch1_T=[]
ch2_T=[]
ch3_T=[]
ch4_T=[]



with open(filename) as fp:
    line = fp.readline()
    cnt = 1
    while line:
        line = fp.readline().strip()
        
        if 'Ch 1 T1,T2:' in line:
            hold= line.split(':')[1].split(' ')
            hold = filter(None, hold) # fastest
            hold=map(int, hold)
            ch1_T=hold
        
        if 'Ch 2 T1,T2:' in line:
            hold= line.split(':')[1].split(' ')
            hold = filter(None, hold) # fastest
            hold=map(int, hold)
            ch2_T=hold
        if 'Ch 3 T1,T2:' in line:
            hold= line.split(':')[1].split(' ')
            hold = filter(None, hold) # fastest
            hold=map(int, hold)
            ch3_T=hold
        if 'Ch 4 T1,T2:' in line:
            hold= line.split(':')[1].split(' ')
            hold = filter(None, hold) # fastest
            hold=map(int, hold)
            ch4_T=hold
        
        if 'Channel 1:' in line:
            hold= line.split(':')[1].split(' ')
            hold = filter(None, hold) # fastest
            ch1=map(int, hold)
        if 'Channel 2:' in line:
            hold= line.split(':')[1].split(' ')
            hold = filter(None, hold) # fastest
            ch3=map(int, hold)

        if 'Channel 3:' in line:
            hold= line.split(':')[1].split(' ')
            hold = filter(None, hold) # fastest
            ch2=map(int, hold)

        if 'Channel 4:' in line:
            hold= line.split(':')[1].split(' ')
            hold = filter(None, hold) # fastest
            ch4=map(int, hold)

nData=len(ch1)
time=np.arange(0,nData*5,5)

plt.ion()


fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)
ax1.plot(time,ch1,label='ch1')
ax1.plot(time,ch2,label='ch2')
ax1.plot(time,ch3,label='ch3')
ax1.plot(time,ch4,label='ch4')

ax1.set_xlim([time[0],time[nData-1]])
ax1.set_ylim([-100,100])

ax1.legend(numpoints=1,loc='upper right')
plt.show()
raw_input()
plt.close()
