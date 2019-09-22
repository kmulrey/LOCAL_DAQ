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
            char SYS_NAME[50] ;
            char UNIT_STATE[50] ;
            char UNIT_SERIAL_NO[50] ;
            unsigned short PORT_NO_WRITE ;
            unsigned short PORT_NO_READ ;

            unsigned short Control_Parameters[100] ;
        } messages ;
        unsigned short VALUE ;
        unsigned char Control_Messages[200] ;

    public:
        void Read_Message_File(char*,int) ;
        void Build_Messages() ;

};
