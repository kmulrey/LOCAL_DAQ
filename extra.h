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

class DEVICE
{
    private:

        char message[650] ;
        char keyword[50] ;
        char value1[50] ;
        char value2[50] ;
        char value3[50] ;
        char value4[50] ;
        char value5[50] ;
        char value6[50] ;
        char value7[50] ;
        char value8[50] ;
        char value9[50] ;
        char value10[50] ;
        char value11[50] ;
        char value12[50] ;
        char value13[50] ;
        char value14[50] ;
        char value15[50] ;
        char value16[50] ;
        char value17[50] ;
        char value18[50] ;
        char value19[50] ;
        char value20[50] ;

        char defn[100] ;
        char value[50] ;
    


        struct SEND_MESSAGES
        {
            char SYS_NAME[4][50] ;
            char UNIT_STATE[4][50] ;
            char UNIT_SERIAL_NO[4][50] ;
            unsigned short PORT_NO_WRITE[4];
            unsigned short PORT_NO_READ[4] ;
            unsigned short TRIGGER_ENABLE_1;
            unsigned short TRIGGER_ENABLE_2;
            unsigned short TRIGGER_ENABLE_3;
            unsigned short TRIGGER_ENABLE_4;
            unsigned short TRIGGER_ENABLE_CAL;
            unsigned short TRIGGER_ENABLE_TEN_SEC;
            unsigned short TRIGGER_ENABLE_EXT;
            unsigned short READOUT_TIME;
            unsigned short TRIGGER_RATE_DIVIDER;
            unsigned short CHANNEL_READOUT_1;
            unsigned short CHANNEL_READOUT_2;
            unsigned short CHANNEL_READOUT_3;
            unsigned short CHANNEL_READOUT_4;
            unsigned short FULL_SCALE_ENABLE;
            unsigned short PPS_ENABLE;
            unsigned short DAQ_ENABLE;
            
            unsigned short CHANNEL_HV[4];
            unsigned short TRIGG_CONDITION[4];
            unsigned short PRE_COIN_TIME[4];
            unsigned short POST_COIN_TIME[4];
            unsigned short GAIN_CORRECTION[4];
            unsigned short OFFSET_CORRECTION[4];
            unsigned short INTEGRATION_TIME[4];
            unsigned short BASE_MAX[4];
            unsigned short BASE_MIN[4];
            unsigned short SIG_T1[4];
            unsigned short SIG_T2[4];
            unsigned short TPREV[4];
            unsigned short TPER[4];
            unsigned short TCMAX[4];
            unsigned short NCMAX[4];
            unsigned short NCMIN[4];
            unsigned short QMAX[4];
            unsigned short QMIN[4];

            
            
            
            unsigned short Control_Parameters[100] ;
            unsigned short Mode_Parameters[100];
        } messages ;
        unsigned short VALUE ;

    public:
        void Read_Message_File(char*,int) ;
        void Read_Parameter_Mode_File(char*) ;
        void Build_Messages(int) ;
        void Build_Mode_Messages() ;
        char Control_Messages[4][200] ;
        char Control_Mode_Messages[200] ;
        char Finish_Message[3];
        void Build_Finish_Messages();
};
