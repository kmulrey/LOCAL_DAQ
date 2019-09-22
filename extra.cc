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
        printf("%s\n",keyword);

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
            strcpy(messages.SYS_NAME,value) ;
            printf("* %s\n",messages.SYS_NAME) ;
        }
        if(strncmp(keyword,"UNIT_SERIAL_NO",strlen("UNIT_SERIAL_NO"))==0)
        {
            strcpy(messages.UNIT_SERIAL_NO,value) ;
            printf("* %s\n",messages.UNIT_SERIAL_NO) ;
        }
        if(strncmp(keyword,"PORT_NO_WRITE",strlen("PORT_NO_WRITE"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.PORT_NO_WRITE=VALUE ;
            printf("* PORT_NO_WRITE=%d\n",messages.PORT_NO_WRITE) ;
        }
        if(strncmp(keyword,"PORT_NO_READ",strlen("PORT_NO_READ"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.PORT_NO_READ=VALUE ;
            printf("* PORT_NO_READ=%d\n",messages.PORT_NO_READ) ;
        }
        
        // include all parameters we need 
        
        if(strncmp(keyword,"CHANNEL_1_THRES_LOW",strlen("CHANNEL_1_THRES_LOW"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.Control_Parameters[0]=VALUE ;
            printf("CHANNEL_1_THRES_LOW=%d\n",messages.Control_Parameters[0]) ;
        }
        
        if(strncmp(keyword,"CHANNEL_HV",strlen("CHANNEL_HV"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.Control_Parameters[1]=VALUE ;
            printf("CHANNEL_HV=%d\n",messages.Control_Parameters[1]) ;
        }
        
        if(strncmp(keyword,"TRIGG_CONDITION",strlen("TRIGG_CONDITION"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.Control_Parameters[2]=VALUE ;
            printf("TRIGG_CONDITION=%d\n",messages.Control_Parameters[2]) ;
        }
        
        if(strncmp(keyword,"PRE_COIN_TIME",strlen("PRE_COIN_TIME"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.Control_Parameters[3]=VALUE ;
            printf("PRE_COIN_TIME=%d\n",messages.Control_Parameters[3]) ;
        }
        
        if(strncmp(keyword,"COIN_TIME",strlen("COIN_TIME"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.Control_Parameters[4]=VALUE ;
            printf("COIN_TIME=%d\n",messages.Control_Parameters[4]) ;
        }
        
        if(strncmp(keyword,"POST_COIN_TIME",strlen("POST_COIN_TIME"))==0)
        {
            std::istringstream V(value) ;
            V>>VALUE ;
            messages.Control_Parameters[5]=VALUE ;
            printf("POST_COIN_TIME=%d\n",messages.Control_Parameters[5]) ;
        }

        
        
        
    }
    
    
    
    fclose(fp) ;

}


void DEVICE:: Build_Messages()
{
    Control_Messages[0]=(messages.Control_Parameters[0]) & 0x00ff ;
    Control_Messages[1]=(messages.Control_Parameters[1]) & 0x00ff ;
    Control_Messages[2]=(messages.Control_Parameters[2]) & 0x00ff ;
    Control_Messages[3]=(messages.Control_Parameters[3]) & 0x00ff ;
    Control_Messages[4]=(messages.Control_Parameters[4]) & 0x00ff ;
    Control_Messages[5]=(messages.Control_Parameters[5]) & 0x00ff ;
 /*
    Control_Messages[6]=(messages.Control_Parameters[6]) & 0x00ff ;
    Control_Messages[7]=(messages.Control_Parameters[7]) & 0x00ff ;
    Control_Messages[8]=(messages.Control_Parameters[8]) & 0x00ff ;
    Control_Messages[9]=(messages.Control_Parameters[9]) & 0x00ff ;
    Control_Messages[10]=(messages.Control_Parameters[10]) & 0x00ff ;
    Control_Messages[11]=(messages.Control_Parameters[11]) & 0x00ff ;
    Control_Messages[12]=(messages.Control_Parameters[12]) & 0x00ff ;
    Control_Messages[13]=(messages.Control_Parameters[13]) & 0x00ff ;
    Control_Messages[14]=(unsigned short)((messages.Control_Parameters[14]+34.0714)/7.93155) & 0x00ff ;
    Control_Messages[15]=(unsigned short)((messages.Control_Parameters[15]+34.0714)/7.93155) & 0x00ff ;
    Control_Messages[16]=((unsigned short)(messages.Control_Parameters[16]/0.4883) & 0xff00)>>8 ;
    Control_Messages[17]=((unsigned short)(messages.Control_Parameters[16]/0.4883) & 0x00ff) ;
    Control_Messages[18]=((unsigned short)(messages.Control_Parameters[17]/0.4883) & 0xff00)>>8 ;
    Control_Messages[19]=((unsigned short)(messages.Control_Parameters[17]/0.4883) & 0x00ff) ;
    Control_Messages[20]=((unsigned short)(messages.Control_Parameters[18]/0.4883) & 0xff00)>>8 ;
    Control_Messages[21]=((unsigned short)(messages.Control_Parameters[18]/0.4883) & 0x00ff) ;
    Control_Messages[22]=((unsigned short)(messages.Control_Parameters[19]/0.4883) & 0xff00)>>8 ;
    Control_Messages[23]=((unsigned short)(messages.Control_Parameters[19]/0.4883) & 0x00ff) ;
    Control_Messages[24]=Trigger_Condition(messages.Control_Parameters[20]) ;
 
    unsigned short Pre_Coin_Time=(unsigned short)(messages.Control_Parameters[21]/5) ;    //no. of 5ns steps
    Control_Messages[25]=(Pre_Coin_Time & 0xff00)>>8 ;
    Control_Messages[26]=(Pre_Coin_Time & 0x00ff) ;
    
    unsigned short Coin_Time=(unsigned short)(messages.Control_Parameters[22]/5) ;        //no. of 5ns steps
    Control_Messages[27]=(Coin_Time & 0xff00)>>8 ;
    Control_Messages[28]=(Coin_Time & 0x00ff) ;
    
    unsigned short Post_Coin_Time=(unsigned short)(messages.Control_Parameters[23]/5) ;    //no. of 5ns steps
    Control_Messages[29]=(Post_Coin_Time & 0xff00)>>8 ;
    Control_Messages[30]=(Post_Coin_Time & 0x00ff) ;
    
    Control_Messages[31]=((unsigned short)(messages.Control_Parameters[24]) & 0xff00)>>8 ;
    Control_Messages[32]=((unsigned short)(messages.Control_Parameters[24]) & 0x00ff) ;
     */
}

