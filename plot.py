import numpy as np
import os
import matplotlib.pyplot as plt
from optparse import OptionParser
import sys
import glob
plt.ion()
parser = OptionParser()

data_dir='field_data/'


max_plot=100


parser.add_option('-r', '--runnr', type='string', default='002')
options, arguments = parser.parse_args()


runnr=options.runnr#'001'
filecount=0


txtfiles = []
for file in glob.glob(data_dir+'*.dat'):
    #num=int(file.split('/')[1].split('.')[0])
    #if num>start and num<stop:
    if runnr+'_' in file and filecount<max_plot:
        txtfiles.append(file)
        filecount=filecount+1

nData= len(txtfiles)



for i in np.arange(nData):
    filename=txtfiles[i]

    ch1=[]
    ch2=[]
    ch3=[]
    ch4=[]

    ch1_T=[]
    ch2_T=[]
    ch3_T=[]
    ch4_T=[]
    
    trigg_pattern=0



    with open(filename) as fp:
        line = fp.readline()
        print filename
        cnt = 1
        while line:
            line = fp.readline().strip()
            
            if 'Trigger Source Pattern:' in line:
                hold= line.split(':')[1].split(' ')
                hold = filter(None, hold) # fastest
                hold=map(int, hold)
                trigg_pattern=hold[0]
        
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
                ch2=map(int, hold)

            if 'Channel 3:' in line:
                hold= line.split(':')[1].split(' ')
                hold = filter(None, hold) # fastest
                ch3=map(int, hold)

            if 'Channel 4:' in line:
                hold= line.split(':')[1].split(' ')
                hold = filter(None, hold) # fastest
                ch4=map(int, hold)



    trig1=trigg_pattern>>8&0001
    trig2=trigg_pattern>>9&0001
    trig3=trigg_pattern>>10&0001
    trig4=trigg_pattern>>11&0001


    Pmax_ind=np.argmin(ch1)

    nData=len(ch1)
    time=np.arange(0,nData*5,5)


    Tpr=50*5
    Tper=8*25
    '''
    def trigger(ch):
        l=len(ch)
        print l
        T1_cross=[]
        T2_cross=[]
        trigg=0
        t1_flag=0
        t2_flag=0
        t_trigg=-1
        for e in np.arange(l):
            
            if -1*ch[e]>ch1_T[0] and t1_flag==0 and trigg==0:
                t1_flag=1
                T1_cross.append(e)
                if trigg==0:
                    trigg=1
                    t_trigg=time[e]
            if -1*ch[e]<ch1_T[0] and t1_flag==1:
                t1_flag=0
                    
            if trigg==1:
                if -1*ch[e]>ch2_T[0] and e not in T1_cross and t2_flag==0:
                    t2_flag=1
                    T2_cross.append(e)

                if -1*ch[e]<ch2_T[0] and t2_flag==1:
                    t2_flag=0
            if trigg==1 and (time[2]-t_trigg)>Tper:
                trigg=0

        return T1_cross,T2_cross


    t1_cross, t2_cross=trigger(ch4)

    print t1_cross, t2_cross
    '''

    fig = plt.figure()
    ax1 = fig.add_subplot(1,1,1)
    #ax1.title.set_text('trigger: {:01b} {:01b} {:01b} {:01b}'.format(trig1,trig2,trig3,trig4))

    #ax1.axhline(y=ch1_T[0], color='red', linestyle=':',label='T1')
    #ax1.axhline(y=ch1_T[1], color='orange', linestyle='-.',label='T2')
    preT=500
    coinT=100
    postT=500
    #ax1.axvline(x=preT, color='black', linestyle=':')
    #ax1.axvline(x=preT+coinT, color='black', linestyle=':')

    #ax1.axvline(x=preT+coinT+postT, color='black', linestyle=':')



    ax1.axhline(y=0, color='grey')
    #ax1.axhline(y=1*ch1_T[0], color='red', linestyle=':',label='T1')

    #ax1.axhline(y=-1*ch1_T[0], color='red', linestyle=':',label='T1')
    #ax1.axhline(y=-1*ch1_T[1], color='orange', linestyle='-.',label='T2')
    #ax1.axvline(x=time[Pmax_ind], color='blue', linestyle=':',)
    #ax1.axvline(x=time[Pmax_ind]-Tpr, color='blue', linestyle=':',label='Tpr')
    #ax1.axvline(x=time[Pmax_ind]+Tper, color='blue', linestyle='-.',label='Tper')

    #ax1.plot(time,ch1,color='black')
    #ax1.plot(time[Pmax_ind],ch1[Pmax_ind],'o',color='green')
    #ax1.plot(time[t1_cross[0]],ch1[t1_cross[0]],'o',color='red')
    
    #for t in np.arange(len(t2_cross)):
    #    ax1.plot(time[t2_cross[t]],ch1[t2_cross[t]],'o',color='orange')
    
    ax1.plot(time,-1*np.asarray(ch1),label='ch1',color='red')

    ax1.plot(time,-1*np.asarray(ch2),label='ch2',color='orange')
    ax1.plot(time,-1*np.asarray(ch3),label='ch3',color='green')
    ax1.plot(time,-1*np.asarray(ch4),label='ch4',color='blue')

    #ax1.set_xlim([time[0],time[nData-1]])
#ax1.set_xlim([1600,2500])

    ax1.set_ylim([-100,1500])
    ax1.set_ylabel('ADC counts')
    ax1.set_xlabel('time (ns)')

    ax1.set_title('CS013 event')
    fig.tight_layout()
    ax1.legend(numpoints=1,loc='upper right')
    plt.show()
    raw_input()
    plt.close()

