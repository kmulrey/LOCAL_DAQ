#include <stdio.h>
#include <stdlib.h>
//#include "add.h"
//#include <iostream>
#include <sys/wait.h>
//#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>
#include "time.h"
#include "event.h"


extern char runnr[80];

void read_fake_file(char *name, uint8_t *fake_event){
    
    printf("opening file:   %s\n",name);
    
    FILE *fptr;
    fptr=fopen(name,"r");
    
    if(fptr == NULL) {
        printf("Unable to open file!");
    }
    
    
    char buffer[255];
    
    int len=0;
    uint8_t one;
    uint8_t two;
    uint8_t three;
    int end=0;
    
    int k=0;
    while(fgets(buffer, 255, (FILE*) fptr)&& k<MAX_READOUT) {
        fake_event[k]=0;
        len = strlen(buffer);
        if( buffer[len-1] == '\n' ){
            buffer[len-1] = 0;}
        
        int x;
        
        sscanf(buffer, "%x", &x);
        fake_event[k]=x;
        if(k==0){one=x;}
        if(k==1){two=x;}
        if(k==2){three=x;}
        
        if(x==102){
           // printf("-->%x\n", fake_event[k]);
            end=k;
        }
        k++;
    }
    
    fake_event[0]=one;
    fake_event[1]=two;
    fake_event[2]=three;
    
    fclose(fptr);
    

}

void handle_event(uint8_t *buf1, int l){
    //printf("parsing event buffer\n");
    //printf("base 8:   %x %x %x %x %x %x %x %x\n",buf1[0],buf1[1],buf1[2],buf1[3],buf1[4],buf1[5],buf1[6],buf1[7]);

    int ch_hold[4][5000];

    int32_t i,istart,iend,iadc,len[4];
    //uint16_t sb[MAX];
    uint8_t buf[MAX];

    buf[0]=0x99;
    buf[1]=0xc0;
    buf[2]=0x16;
    buf[3]=0x00;

    for(i=1;i<MAX;i++){
        buf[i]=buf1[i-1];
    }
    
    
    write_event(buf);

    
    uint16_t *sb=(uint16_t *)buf;

    //printf("header/id:   %x\n",sb[0]);
    //printf("byte count:   %x\n",sb[1]);
    //printf("trigg pattern:   %x\n",sb[2]);
    
    printf("\n\n\n");

    printf("Event record: 0x%x 0x%x Trigger Mask 0x%04x\n",sb[0],sb[1],sb[2]);
    sb = (unsigned short *)&buf[EVENT_GPS];
    printf("  GPS: %02d-%02d-%d %02d:%02d:%02d ",buf[EVENT_GPS+3],buf[EVENT_GPS+2],*sb,
           buf[EVENT_GPS+4],buf[EVENT_GPS+5],buf[EVENT_GPS+6]);
    printf("Status 0x%02x CTD %d\n",buf[EVENT_STATUS],*(int *)&buf[EVENT_CTD]);
    printf("Readout length: ");
    for(i=0;i<4;i++) {
        printf("%d ",*(short *)&buf[EVENT_LENCH1+2*i]);
        len[i] = *(short *)&buf[EVENT_LENCH1+2*i];
    }
    
    
    printf("\n");
    printf("Trigger Levels: ");
    for(i=0;i<4;i++) printf("(%d,%d) ",*(short *)&buf[EVENT_THRES1CH1+2*i],
                            *(short *)&buf[EVENT_THRES2CH1+2*i]);
    printf("\n");
    
//    printf("List01: ");
    //for(i=EVENT_CTRL;i<EVENT_WINDOWS;i++) printf(" 0x%02x",buf[i]);
    //printf("\n");
    //printf("List02: ");
    //for(i=EVENT_WINDOWS;i<EVENT_ADC;i++) printf(" 0x%02x",buf[i]);
    //printf("\n");
    
    istart = EVENT_ADC;
    int ch_count=0;
    for(i=0;i<4;i++){
        ch_count=0;
        iend = istart+2*len[i];
        //printf("Channel %d:",i+1);
        for(iadc=istart;iadc<iend;iadc+=2) {
            //if((iadc-istart)==(16*((iadc-istart)/16))) printf("\n");
            //printf("%6d ",*(short *)&buf[iadc]);
            ch_hold[i][ch_count]=*(short *)&buf[iadc];
            ch_count++;
        }
        //printf("\n");
        istart = iend;
    }
    //printf("End Marker 0x%4x (last adc 0x%04x)\n",
      //     *(unsigned short *)&buf[iend], *(unsigned short *)&buf[iend-2]);
    
    
    // readout lengths len[4]
    // ch data ch_hold[4][]
    float baselines[4]={0};
    int min_values[4]={10000,10000,10000,10000};

    int j;
    int c=0;
    for(j=0; j<N_BASELINE; j++){
        for(c=0; c<4; c++){baselines[c]=baselines[c]+ch_hold[c][j];}
    }
    for(c=0; c<4; c++){    baselines[c]=baselines[c]/N_BASELINE;}

    for(j=0; j<len[0]; j++){
        for(c=0; c<4; c++){
            if(ch_hold[c][j]<min_values[c]){min_values[c]=ch_hold[c][j];}
        }
    }

    for(c=0; c<4; c++){
        printf("baseline, min %d: %f  %d\n",c+1,baselines[c],min_values[c]);
    }
     
     
}


// write event to file

void write_event(uint8_t *buf){

    int32_t i,c,istart,iend,iadc,len[4],trigger_T1[4],trigger_T2[4],event_ctd;
    uint16_t *sb=(uint16_t *)buf;
    int ch_hold[4][5000];

    //printf("Event record: 0x%x 0x%x Trigger Mask 0x%04x\n",sb[0],sb[1],sb[2]);
    sb = (unsigned short *)&buf[EVENT_GPS];
    event_ctd=*(int *)&buf[EVENT_CTD];
    

    for(i=0;i<4;i++) {
        len[i] = *(short *)&buf[EVENT_LENCH1+2*i];
        trigger_T1[i]=*(short *)&buf[EVENT_THRES1CH1+2*i];
        trigger_T2[i]=*(short *)&buf[EVENT_THRES2CH1+2*i];
    }
    
    istart = EVENT_ADC;
    int ch_count=0;
    for(i=0;i<4;i++){
        ch_count=0;
        iend = istart+2*len[i];
        //printf("Channel %d:",i+1);
        for(iadc=istart;iadc<iend;iadc+=2) {
            ch_hold[i][ch_count]=*(short *)&buf[iadc];
            ch_count++;
        }
        istart = iend;
    }
    
    srand(time(NULL));   // Initialization, should only be called once.
    int r = rand();      // Returns a pseudo-random integer between 0 and RAND_MAX.
    char str[100];
    sprintf(str, "%d", r);
    
    char filename[80];
    strcpy(filename, "data/");
    strcat(filename, runnr);
    strcat(filename, "_");

    strcat(filename,str);
    strcat(filename, ".dat");
    
    FILE *fptr;
    fptr=fopen(filename,"w");
    
    fprintf(fptr,"event: %d\n",r);
    fprintf(fptr,"Ch 1 T1,T2: %d %d \n",trigger_T1[0],trigger_T2[0]);
    fprintf(fptr,"Ch 2 T1,T2: %d %d \n",trigger_T1[1],trigger_T2[1]);
    fprintf(fptr,"Ch 3 T1,T2: %d %d \n",trigger_T1[2],trigger_T2[2]);
    fprintf(fptr,"Ch 4 T1,T2: %d %d \n",trigger_T1[3],trigger_T2[3]);
    fprintf(fptr,"GPS: %02d-%02d-%d %02d:%02d:%02d ",buf[EVENT_GPS+3],buf[EVENT_GPS+2],*sb,
           buf[EVENT_GPS+4],buf[EVENT_GPS+5],buf[EVENT_GPS+6]);
    fprintf(fptr,"CTD: %d\n",event_ctd);
    

    for(c=0; c<4; c++){
    fprintf(fptr,"Channel %d: ",c+1);
    for(i=0; i<len[c]; i++){fprintf(fptr,"%d ",ch_hold[c][i]);}
    fprintf(fptr,"\n");
    }
    

    fclose(fptr);
 
    
    
    
    
    
    
    
    
}

