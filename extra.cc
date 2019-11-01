#include <sstream>
#include <stdio.h>
#include <signal.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <time.h>
#include "extra.h"
//#include "socket_functions.h"

void DEVICE:: Read_Message_File(char* filename,int col)
{
    printf("reading input\n");
    FILE *fp=fopen(filename,"r") ;


    while(fgets(message,400,fp)!=NULL)
    {
        if(strncmp(message,"//",strlen("//"))==0){
            continue ;}
        std::istringstream M (message) ;
        //printf("%s\n",message);
        M>>keyword>>value1>>value2>>value3>>value4>>value5>>value6>>value7>>value8>>value9>>value10>>value11>>value12>>value13>>value14>>value15>>value16>>value17>>value18>>value19>>value20>>defn ;
        //printf("%s\n",keyword);

        if(col==1) strcpy(value,value1) ;
        if(col==2) strcpy(value,value2) ;
        if(col==3) strcpy(value,value3) ;
        if(col==4) strcpy(value,value4) ;
        if(col==5) strcpy(value,value5) ;
        if(col==6) strcpy(value,value6) ;
        if(col==7) strcpy(value,value7) ;
        if(col==8) strcpy(value,value8) ;
        if(col==9) strcpy(value,value9) ;
        if(col==10) strcpy(value,value10) ;
        if(col==11) strcpy(value,value11) ;
        if(col==12) strcpy(value,value12) ;
        if(col==13) strcpy(value,value13) ;
        if(col==14) strcpy(value,value14) ;
        if(col==15) strcpy(value,value15) ;
        if(col==16) strcpy(value,value16) ;
        if(col==17) strcpy(value,value17) ;
        if(col==18) strcpy(value,value18) ;
        if(col==19) strcpy(value,value19) ;
        if(col==20) strcpy(value,value20) ;
        if(strncmp(keyword,"SYS_NAME",strlen("SYS_NAME"))==0)
        {
            strcpy(messages.SYS_NAME[col-1],value) ;
           // printf("* %s\n",messages.SYS_NAME) ;
        }
        if(strncmp(keyword,"UNIT_SERIAL_NO",strlen("UNIT_SERIAL_NO"))==0)
        {
            strcpy(messages.UNIT_SERIAL_NO[col-1],value) ;
            //printf("* %s\n",messages.UNIT_SERIAL_NO) ;
        }
        if(strncmp(keyword,"PORT_NO_WRITE",strlen("PORT_NO_WRITE"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.PORT_NO_WRITE[col-1]=VALUE ;
            //printf("* PORT_NO_WRITE=%d\n",messages.PORT_NO_WRITE) ;
        }
        if(strncmp(keyword,"PORT_NO_READ",strlen("PORT_NO_READ"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.PORT_NO_READ[col-1]=VALUE ;
            //printf("* PORT_NO_READ=%d\n",messages.PORT_NO_READ) ;
        }
        
        // include all parameters we need 

        if(strncmp(keyword,"CHANNEL_HV",strlen("CHANNEL_HV"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.CHANNEL_HV[col-1]=VALUE ;
            printf("CHANNEL_HV=%d\n",messages.CHANNEL_HV[col-1]) ;
        }
        
        
        
        if(strncmp(keyword,"TRIGG_CONDITION",strlen("TRIGG_CONDITION"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.TRIGG_CONDITION[col-1]=VALUE ;
            //printf("TRIGG_CONDITION=%d\n",messages.TRIGG_CONDITION[col-1]) ;
        }
        
        if(strncmp(keyword,"PRE_COIN_TIME",strlen("PRE_COIN_TIME"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.PRE_COIN_TIME[col-1]=VALUE ;
            //printf("PRE_COIN_TIME=%d\n",messages.Control_Parameters[3]) ;
        }
        
        if(strncmp(keyword,"POST_COIN_TIME",strlen("POST_COIN_TIME"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.POST_COIN_TIME[col-1]=VALUE ;
            //printf("POST_COIN_TIME=%d\n",messages.Control_Parameters[5]) ;
        }
        
        if(strncmp(keyword,"GAIN_CORRECTION",strlen("GAIN_CORRECTION"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.GAIN_CORRECTION[col-1]=VALUE ;
        }
        
        if(strncmp(keyword,"OFFSET_CORRECTION",strlen("OFFSET_CORRECTION"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.OFFSET_CORRECTION[col-1]=VALUE ;
            printf("OFFSET=%d\n",messages.OFFSET_CORRECTION[col-1]) ;

        }

        if(strncmp(keyword,"INTEGRATION_TIME",strlen("INTEGRATION_TIME"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.INTEGRATION_TIME[col-1]=VALUE ;
        }
        
        if(strncmp(keyword,"BASE_MAX",strlen("BASE_MAX"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.BASE_MAX[col-1]=VALUE ;
        }
        
        if(strncmp(keyword,"BASE_MIN",strlen("BASE_MIN"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.BASE_MIN[col-1]=VALUE ;
        }
        
        if(strncmp(keyword,"SIG_T1",strlen("SIG_T1"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.SIG_T1[col-1]=VALUE ;
        }
        
        if(strncmp(keyword,"SIG_T2",strlen("SIG_T2"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.SIG_T2[col-1]=VALUE ;
        }
        
        if(strncmp(keyword,"TPREV",strlen("TPREV"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.TPREV[col-1]=VALUE ;
        }
        if(strncmp(keyword,"TPER",strlen("TPER"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.TPER[col-1]=VALUE ;
        }
        
        if(strncmp(keyword,"TCMAX",strlen("TCMAX"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.TCMAX[col-1]=VALUE ;
        }
        if(strncmp(keyword,"NCMAX",strlen("NCMAX"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.NCMAX[col-1]=VALUE ;
        }
        
        if(strncmp(keyword,"NCMIN",strlen("NCMIN"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.NCMIN[col-1]=VALUE ;
        }
        
        if(strncmp(keyword,"QMAX",strlen("QMAX"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.QMAX[col-1]=VALUE ;
        }
        
        if(strncmp(keyword,"QMIN",strlen("QMIN"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.QMIN[col-1]=VALUE ;
        }
        
        
    }
    
    
    
    fclose(fp) ;

}

/*
unsigned short ctrllist[9]={0x0199,0x0012,0x0003,0x0010,0x000f,0x0320,0x0000,0x0000,0x6666};
*/

void DEVICE:: Read_Parameter_Mode_File(char* filename)
{
    printf("reading input\n");
    FILE *fp=fopen(filename,"r") ;
    

    
    

    while(fgets(message,400,fp)!=NULL)
    {
        if(strncmp(message,"//",strlen("//"))==0){
            continue ;}
        std::istringstream M (message) ;
        //printf("%s\n",message);
        M>>keyword>>value;
        
        if(strncmp(keyword,"TRIGGER_ENABLE_1",strlen("TRIGGER_ENABLE_1"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.TRIGGER_ENABLE_1=VALUE;
            //printf("TRIGGER_ENABLE_1=%d\n",messages.TRIGGER_ENABLE_1) ;
        }
        if(strncmp(keyword,"TRIGGER_ENABLE_2",strlen("TRIGGER_ENABLE_2"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.TRIGGER_ENABLE_2=VALUE;
            //printf("TRIGGER_ENABLE_1=%d\n",messages.TRIGGER_ENABLE_1) ;
        }
        if(strncmp(keyword,"TRIGGER_ENABLE_3",strlen("TRIGGER_ENABLE_3"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.TRIGGER_ENABLE_3=VALUE;
            //printf("TRIGGER_ENABLE_1=%d\n",messages.TRIGGER_ENABLE_1) ;
        }
        if(strncmp(keyword,"TRIGGER_ENABLE_4",strlen("TRIGGER_ENABLE_4"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.TRIGGER_ENABLE_4=VALUE;
            //printf("TRIGGER_ENABLE_1=%d\n",messages.TRIGGER_ENABLE_1) ;
        }
        if(strncmp(keyword,"TRIGGER_ENABLE_CAL",strlen("TRIGGER_ENABLE_CAL"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.TRIGGER_ENABLE_CAL=VALUE;
            //printf("TRIGGER_ENABLE_1=%d\n",messages.TRIGGER_ENABLE_1) ;
        }
        if(strncmp(keyword,"TRIGGER_ENABLE_TEN_SEC",strlen("TRIGGER_ENABLE_TEN_SEC"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.TRIGGER_ENABLE_TEN_SEC=VALUE;
            //printf("TRIGGER_ENABLE_1=%d\n",messages.TRIGGER_ENABLE_1) ;
        }
        if(strncmp(keyword,"TRIGGER_ENABLE_EXT",strlen("TRIGGER_ENABLE_EXT"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.TRIGGER_ENABLE_EXT=VALUE;
            //printf("TRIGGER_ENABLE_1=%d\n",messages.TRIGGER_ENABLE_1) ;
        }
        if(strncmp(keyword,"FULL_SCALE_ENABLE",strlen("FULL_SCALE_ENABLE"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.FULL_SCALE_ENABLE=VALUE;
            //printf("TRIGGER_ENABLE_1=%d\n",messages.TRIGGER_ENABLE_1) ;
        }
        if(strncmp(keyword,"PPS_ENABLE",strlen("PPS_ENABLE"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.PPS_ENABLE=VALUE;
            //printf("TRIGGER_ENABLE_1=%d\n",messages.TRIGGER_ENABLE_1) ;
        }
        if(strncmp(keyword,"DAQ_ENABLE",strlen("DAQ_ENABLE"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.DAQ_ENABLE=VALUE;
            //printf("TRIGGER_ENABLE_1=%d\n",messages.TRIGGER_ENABLE_1) ;
        }
        if(strncmp(keyword,"CHANNEL_READOUT_1",strlen("CHANNEL_READOUT_1"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.CHANNEL_READOUT_1=VALUE;
        }
        if(strncmp(keyword,"CHANNEL_READOUT_2",strlen("CHANNEL_READOUT_2"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.CHANNEL_READOUT_2=VALUE;
        }
        if(strncmp(keyword,"CHANNEL_READOUT_3",strlen("CHANNEL_READOUT_3"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.CHANNEL_READOUT_3=VALUE;
            //printf("TRIGGER_ENABLE_1=%d\n",messages.TRIGGER_ENABLE_1) ;
        }
        if(strncmp(keyword,"CHANNEL_READOUT_4",strlen("CHANNEL_READOUT_4"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.CHANNEL_READOUT_4=VALUE;
            //printf("TRIGGER_ENABLE_1=%d\n",messages.TRIGGER_ENABLE_1) ;
        }
        
        
        if(strncmp(keyword,"TRIGGER_RATE_DIVIDER",strlen("TRIGGER_RATE_DIVIDER"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.TRIGGER_RATE_DIVIDER=VALUE;
            //printf("TRIGGER_ENABLE_1=%d\n",messages.TRIGGER_ENABLE_1) ;
        }
        if(strncmp(keyword,"READOUT_TIME",strlen("READOUT_TIME"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.READOUT_TIME=VALUE;
            //printf("TRIGGER_ENABLE_1=%d\n",messages.TRIGGER_ENABLE_1) ;
        }
        
        
        
        
        
      
    }
    
    fclose(fp) ;
    
}





void DEVICE:: Build_Messages(int col)
{
    Control_Messages[col-1][0]=((unsigned short)0x99);
    Control_Messages[col-1][1]=((unsigned short) 0x20) ;
    //channel
    Control_Messages[col-1][2]=((unsigned short) col) ;
    //if(col==2){Control_Messages[col-1][2]=((unsigned short) 7) ;}
        
    
    //HV
    //printf("HV: %d",messages.CHANNEL_HV[col-1]);
    Control_Messages[col-1][3]=((unsigned short)(messages.CHANNEL_HV[col-1]) & 0xff00)>>8 ;
    Control_Messages[col-1][4]=((unsigned short)(messages.CHANNEL_HV[col-1]) & 0x00ff) ;
    //trig_cond
    Control_Messages[col-1][5]=((unsigned short)(messages.TRIGG_CONDITION[col-1]));
    
    //pre-coincidence time
    Control_Messages[col-1][6]=((unsigned short)(messages.PRE_COIN_TIME[col-1]/5) & 0xff00)>>8 ;
    Control_Messages[col-1][7]=((unsigned short)(messages.PRE_COIN_TIME[col-1]/5) & 0x00ff) ;

    //post-coincidence time
    Control_Messages[col-1][8]=((unsigned short)(messages.POST_COIN_TIME[col-1]/5) & 0xff00)>>8 ;
    Control_Messages[col-1][9]=((unsigned short)(messages.POST_COIN_TIME[col-1]/5) & 0x00ff) ;
    
    //gain correction
    Control_Messages[col-1][10]=((unsigned short)(messages.GAIN_CORRECTION[col-1] ) & 0xff00)>>8 ;
    Control_Messages[col-1][11]=((unsigned short)(messages.GAIN_CORRECTION[col-1] ) & 0x00ff) ;
    
    //offset correction
    Control_Messages[col-1][12]=((unsigned short)(messages.OFFSET_CORRECTION[col-1]));
    Control_Messages[col-1][13]=((unsigned short)(messages.INTEGRATION_TIME[col-1] ));
    
    //base max
    Control_Messages[col-1][14]=((unsigned short)(messages.BASE_MAX[col-1] ) & 0xff00)>>8 ;
    Control_Messages[col-1][15]=((unsigned short)(messages.BASE_MAX[col-1] ) & 0x00ff) ;
    
    //base min
    Control_Messages[col-1][16]=((unsigned short)(messages.BASE_MIN[col-1] ) & 0xff00)>>8 ;
    Control_Messages[col-1][17]=((unsigned short)(messages.BASE_MIN[col-1] ) & 0x00ff) ;
    
    //signal T1
    Control_Messages[col-1][18]=((unsigned short)(messages.SIG_T1[col-1] ) & 0xff00)>>8 ;
    Control_Messages[col-1][19]=((unsigned short)(messages.SIG_T1[col-1] ) & 0x00ff) ;
    
    //signal T2
    Control_Messages[col-1][20]=((unsigned short)(messages.SIG_T2[col-1]) & 0xff00)>>8 ;
    Control_Messages[col-1][21]=((unsigned short)(messages.SIG_T2[col-1] ) & 0x00ff) ;
    
    //t prev
    Control_Messages[col-1][22]=((unsigned short)(messages.TPREV[col-1] )) ;
    
    //t per
    Control_Messages[col-1][23]=((unsigned short)(messages.TPER[col-1] )) ;
    
    //tcmax
    Control_Messages[col-1][24]=((unsigned short)(messages.TCMAX[col-1]))  ;
    
    //ncmax
    Control_Messages[col-1][25]=((unsigned short)(messages.NCMAX[col-1] ))  ;
    
    //ncmin
    Control_Messages[col-1][26]=((unsigned short)(messages.NCMIN[col-1] ))  ;
    
    //qmax
    Control_Messages[col-1][27]=((unsigned short)(messages.QMAX[col-1] ));
    
    //qmin
    Control_Messages[col-1][28]=((unsigned short)(messages.QMIN[col-1] ));
                                                

    
    
    Control_Messages[col-1][199]=((unsigned short)0x66);
    

}


void DEVICE:: Build_Mode_Messages()
{
    
    printf("building mode messages\n");
    Control_Mode_Messages[0]=((unsigned short)0x99);
    Control_Mode_Messages[1]=((unsigned short) 0x21) ;  // identifier for parammode message

    //CONTROL REGISTER -> 2 bits
    unsigned short control=0;
    control= (messages.FULL_SCALE_ENABLE<<2) | (messages.PPS_ENABLE<<1)| (messages.DAQ_ENABLE<<0);
    //printf("%x\n",control);
    Control_Mode_Messages[3]=((unsigned short)(control) & 0xff00)>>8 ;
    Control_Mode_Messages[4]=((unsigned short)(control) & 0x00ff) ;
  
    
    
    //TRIGGER ENABLE MASK-> 2 bits
    unsigned short trigger=0;
    trigger= (messages.TRIGGER_ENABLE_4<<11) | (messages.TRIGGER_ENABLE_3<<10)| (messages.TRIGGER_ENABLE_2<<9)|(messages.TRIGGER_ENABLE_1<<8)|(messages.TRIGGER_ENABLE_CAL<<6)|(messages.TRIGGER_ENABLE_TEN_SEC<<5)|(messages.TRIGGER_ENABLE_EXT<<4);
    //printf("%x\n",trigger);
    Control_Mode_Messages[5]=((unsigned short)(trigger) & 0xff00)>>8 ;
    Control_Mode_Messages[6]=((unsigned short)(trigger) & 0x00ff) ;


    //CHANNEL READOUT -> 1 bits, TRIGGER RATE DIVIDER
    unsigned short chan=0;
    unsigned short rate=0;

    chan= (messages.CHANNEL_READOUT_4<<3) | (messages.CHANNEL_READOUT_3<<2)| (messages.CHANNEL_READOUT_2<<1)|(messages.CHANNEL_READOUT_1<<0);
    //printf("%x\n",chan);
    rate=messages.TRIGGER_RATE_DIVIDER;

    
    Control_Mode_Messages[7]=rate;
    Control_Mode_Messages[8]=chan;

    
    //COMMON COIN READOUT TIME -> 2 bits
    unsigned short coin=0;
    coin=messages.READOUT_TIME/5;
    Control_Mode_Messages[9]=((unsigned short)(coin) & 0xff00)>>8 ;
    Control_Mode_Messages[10]=((unsigned short)(coin) &  0x00ff);   
    Control_Mode_Messages[199]=((unsigned short)0x66);

}

void DEVICE:: Build_Finish_Messages(){
    Finish_Message[0]=((unsigned short)0x99);
    Finish_Message[1]=((unsigned short)0x25);
    Finish_Message[2]=((unsigned short)0x66);

}
